#include <Arduino.h>
#include <WiFi.h>
#include "GUI.h"
#include "Energy.h"
#include "Event.h"
#include "UIModal.h"

#define WATCH_FLAG_SLEEP_MODE       _BV(1)
#define WATCH_FLAG_SLEEP_EXIT       _BV(2)
#define WATCH_FLAG_BMA_IRQ          _BV(3)
#define WATCH_FLAG_AXP_IRQ          _BV(4)

#define G_EVENT_WIFI_SCAN_START     _BV(3)
#define G_EVENT_WIFI_SCAN_DONE      _BV(4)
#define G_EVENT_WIFI_CONNECTED      _BV(5)
#define G_EVENT_WIFI_BEGIN          _BV(6)
#define G_EVENT_WIFI_OFF            _BV(7)

enum {
    Q_EVENT_WIFI_SCAN_DONE,
    Q_EVENT_WIFI_CONNECT,
    Q_EVENT_BMA_INT,
    Q_EVENT_AXP_INT,
};

TTGOClass       *Energy::_ttgo      = nullptr;
GUI             *Energy::_gui       = nullptr;
bool            Energy::_lenergy    = false;

void Energy::setupAXPIRQ()
{
    _ttgo->power->adc1Enable(AXP202_BATT_VOL_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1, AXP202_ON);
    _ttgo->power->enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_FINISHED_IRQ, AXP202_ON);
    _ttgo->power->clearIRQ();
}

void Energy::disableUnusedPower()
{
    _ttgo->power->setPowerOutPut(AXP202_EXTEN, AXP202_OFF);
    _ttgo->power->setPowerOutPut(AXP202_DCDC2, AXP202_OFF);
    _ttgo->power->setPowerOutPut(AXP202_LDO3, AXP202_OFF);
    _ttgo->power->setPowerOutPut(AXP202_LDO4, AXP202_OFF);
}

void Energy::setupIRQ()
{
    // Enable BMA423 interrupt
    // The default interrupt configuration,
    // you need to set the acceleration parameters, please refer to the BMA423_Accel example
    _ttgo->bma->attachInterrupt();

    //Connection interrupted to the specified pin
    pinMode(BMA423_INT1, INPUT);
    attachInterrupt(BMA423_INT1, [] {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        EventBits_t  bits = xEventGroupGetBitsFromISR(Event::isrGroup);
        if (bits & WATCH_FLAG_SLEEP_MODE)
        {
            //! For quick wake up, use the group flag
            xEventGroupSetBitsFromISR(Event::isrGroup, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_BMA_IRQ, &xHigherPriorityTaskWoken);
        }
        else
        {
            uint8_t data = Q_EVENT_BMA_INT;
            xQueueSendFromISR(Event::queueHandle, &data, &xHigherPriorityTaskWoken);
        }

        if (xHigherPriorityTaskWoken)
        {
            portYIELD_FROM_ISR ();
        }
    }, RISING);

    // Connection interrupted to the specified pin
    pinMode(AXP202_INT, INPUT);
    attachInterrupt(AXP202_INT, [] {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        EventBits_t  bits = xEventGroupGetBitsFromISR(Event::isrGroup);
        if (bits & WATCH_FLAG_SLEEP_MODE)
        {
            //! For quick wake up, use the group flag
            xEventGroupSetBitsFromISR(Event::isrGroup, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_AXP_IRQ, &xHigherPriorityTaskWoken);
        }
        else
        {
            uint8_t data = Q_EVENT_AXP_INT;
            xQueueSendFromISR(Event::queueHandle, &data, &xHigherPriorityTaskWoken);
        }
        if (xHigherPriorityTaskWoken)
        {
            portYIELD_FROM_ISR ();
        }
    }, FALLING);
}

void Energy::network()
{
    WiFi.mode(WIFI_STA);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        xEventGroupClearBits(Event::groupHandle, G_EVENT_WIFI_CONNECTED);
    }, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        uint8_t data = Q_EVENT_WIFI_SCAN_DONE;
        xQueueSend(Event::queueHandle, &data, portMAX_DELAY);
    }, WiFiEvent_t::SYSTEM_EVENT_SCAN_DONE);

    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        xEventGroupSetBits(Event::groupHandle, G_EVENT_WIFI_CONNECTED);
    }, WiFiEvent_t::SYSTEM_EVENT_STA_CONNECTED);

    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        _gui->wifiConnectStatus(true);
    }, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
}

void Energy::lowEnergy()
{
    if (_ttgo->bl->isOn()) {
        xEventGroupSetBits(Event::isrGroup, WATCH_FLAG_SLEEP_MODE);
        _ttgo->closeBL();
        _ttgo->stopLvglTick();
        _ttgo->bma->enableStepCountInterrupt(false);
        _ttgo->displaySleep();
        if (!WiFi.isConnected()) {
            _lenergy = true;
            UIModal::hideAll();
            WiFi.mode(WIFI_OFF);
            // rtc_clk_cpu_freq_set(RTC_CPU_FREQ_2M);
            setCpuFrequencyMhz(20);

            Serial.println("ENTER IN LIGHT SLEEEP MODE");
            gpio_wakeup_enable ((gpio_num_t)AXP202_INT, GPIO_INTR_LOW_LEVEL);
            gpio_wakeup_enable ((gpio_num_t)BMA423_INT1, GPIO_INTR_HIGH_LEVEL);
            esp_sleep_enable_gpio_wakeup ();
            esp_light_sleep_start();
        }
    } else {
        _ttgo->startLvglTick();
        _ttgo->displayWakeup();
        _ttgo->rtc->syncToSystem();
        _gui->updateStepCounter();
        _gui->updateBatteryLevel();
        lv_disp_trig_activity(NULL);
        _ttgo->openBL();
        _ttgo->bma->enableStepCountInterrupt();

        // go to standby screen
        _gui->showScreen(SCREEN_STANDBY);
    }
}

void Energy::checkIRQ()
{
    bool  rlst;
    uint8_t data;
    //! Fast response wake-up interrupt
    EventBits_t  bits = xEventGroupGetBits(Event::isrGroup);
    if (bits & WATCH_FLAG_SLEEP_EXIT) {
        if (_lenergy) {
            _lenergy = false;
            // rtc_clk_cpu_freq_set(RTC_CPU_FREQ_160M);
            setCpuFrequencyMhz(160);
        }

        Energy::lowEnergy();

        if (bits & WATCH_FLAG_BMA_IRQ) {
            do {
                rlst =  _ttgo->bma->readInterrupt();
            } while (!rlst);
            xEventGroupClearBits(Event::isrGroup, WATCH_FLAG_BMA_IRQ);
        }
        if (bits & WATCH_FLAG_AXP_IRQ) {
            _ttgo->power->readIRQ();
            _ttgo->power->clearIRQ();
            //TODO: Only accept axp power pek key short press
            xEventGroupClearBits(Event::isrGroup, WATCH_FLAG_AXP_IRQ);
        }
        xEventGroupClearBits(Event::isrGroup, WATCH_FLAG_SLEEP_EXIT);
        xEventGroupClearBits(Event::isrGroup, WATCH_FLAG_SLEEP_MODE);
    }
    if ((bits & WATCH_FLAG_SLEEP_MODE)) {
        //! No event processing after entering the information screen
        return;
    }

    //! Normal polling
    if (xQueueReceive(Event::queueHandle, &data, 5 / portTICK_RATE_MS) == pdPASS) {
        switch (data) {
        case Q_EVENT_BMA_INT:
            do {
                rlst = _ttgo->bma->readInterrupt();
            } while (!rlst);

            //! setp counter
            if (_ttgo->bma->isStepCounter()) {
                _gui->updateStepCounter();
            }
            break;
        case Q_EVENT_AXP_INT:
            _ttgo->power->readIRQ();
            if (_ttgo->power->isVbusPlugInIRQ()) {
                _gui->isPluggedIn = true;
            }
            if (_ttgo->power->isVbusRemoveIRQ()) {
                _gui->isPluggedIn       = false;
                _gui->isStillConnected  = false;
            }
            if (_ttgo->power->isChargingDoneIRQ()) {
                _gui->isStillConnected = true;
            }
            if (_ttgo->power->isPEKShortPressIRQ()) {
                _ttgo->power->clearIRQ();
                lowEnergy();
                return;
            }
            _ttgo->power->clearIRQ();
            break;
        case Q_EVENT_WIFI_SCAN_DONE: {
            int16_t len =  WiFi.scanComplete();
            for (int i = 0; i < len; ++i) {
                _gui->wifiListAdd(WiFi.SSID(i).c_str());
            }
            break;
        }
        default:
            break;
        }
    }
}