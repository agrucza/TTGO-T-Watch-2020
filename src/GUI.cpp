/**
    This is the base GUI class
    @file gui.pp
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/
 
#include "config.h"
#include "LilyGoWatch.h"

#include "GUI.h"
#include "AppStartup.h"
#include "AppStandby.h"
#include "AppTesting.h"
#include "AppCalendar.h"
#include "AppSettings.h"
#include "AppLauncher.h"

TTGOClass*              GUI::_ttgo              = nullptr;
TFT_eSPI*               GUI::_tft               = nullptr;
uint32_t                GUI::_stepCounter       = 0;
TouchMetrics*           GUI::_touch;
GUI::debug_t            GUI::_debug;
unsigned long           GUI::_lastActionTime    = 0;
std::vector<App*>       GUI::_apps;
App*                    GUI::_lastApp           = nullptr;
App*                    GUI::_activeApp         = nullptr;
App*                    GUI::_standby           = nullptr;
App*                    GUI::_launcher          = nullptr;
icon_battery_t          GUI::_batteryIcon       = ICON_CALCULATION;
int                     GUI::_batteryLevel      = 0;

/**
 * @brief  Sets the TTGOClass object to the GUI class
 * @note   
 * @param  *ttgo: ttgo watch reference
 * @retval None
 */
void GUI::setTTGO(TTGOClass *ttgo)
{
    _ttgo = ttgo;
    _tft = _ttgo->tft;
}

/**
 * @brief  Returns the TTGOClass watch reference
 * @note   
 * @retval TTGOClass watch reference
 */
TTGOClass *GUI::getTTGO()
{
    return _ttgo;
}

/**
 * @brief  Returns the TFT_eSPI tft reference
 * @note   
 * @retval TFT_eSPI reference
 */
TFT_eSPI *GUI::getTFT()
{
    return _tft;
}

/**
 * @brief  Inits the GUI
 * @note   
 * @retval None
 */
void GUI::init()
{
    _tft->setTextDatum(MC_DATUM);
    _tft->fillScreen(TFT_BLACK);
    _touch = new TouchMetrics();
    _touch->setTouch(false);
    _lastActionTime = millis();
    updateBatteryLevel();

    addApp(new AppStandby());
    addApp(new AppCalendar());
    addApp(new AppSettings());
    addApp(new AppTesting());
    addApp(new AppLauncher());
    
    _ttgo->openBL();
    showStandbyApp(true);
    
    if(_ttgo->power->isChargeing())
    {
        _batteryIcon = ICON_CHARGE;
    }
    
    xTaskCreate(
        taskHandler,        // call GUI task hadler
        "GUI task handler", // Name of the task (for debugging)
        4096,               // Stack size (bytes)
        NULL,               // Parameter to pass
        5,                  // Task priority
        &taskHandle         // Task handle
    );
}

/**
 * @brief  Sets the wifi connect status
 * @note   
 * @param  set: if true wifi is connected
 * @retval None
 */
void GUI::wifiConnectStatus(bool set)
{

}

/**
 * @brief  Updated the stepcounter
 * @note   
 * @retval None
 */
void GUI::updateStepCounter()
{
    _stepCounter = _ttgo->bma->getCounter();
}

/**
 * @brief Returns the step counter
 * @note
 * @retval the steps taken this day
 */
uint32_t GUI::getStepCounter()
{
    return _stepCounter;
}

/**
 * @brief  
 * @note   
 * @retval None
 */
void GUI::updateBatteryLevel()
{
    _batteryLevel = _ttgo->power->getBattPercentage();
}

/**
 * @brief  Updates the battery icon with a new one
 * @note   
 * @param  index: icon
 * @retval None
 */
void GUI::updateBatteryIcon(icon_battery_t index)
{
    _batteryIcon = index;
}

/**
 * @brief  Adds an SSID to the wifi list
 * @note   
 * @param  *ssid: name of ssid to add to the wifi list
 * @retval None
 */
void GUI::wifiListAdd(const String ssid)
{

}

/**
 * @brief  Will check for touch gestures
 * @note   
 * @retval None
 */
void GUI::checkTouchScreen()
{
    _touch->checkTouch();
}

void GUI::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    _lastActionTime = millis();

    // check for global touch gestures
    if(_activeApp->acceptsGlobalTouch())
    {
        switch(touchType)
        {
            case TouchMetrics::SWIPE_BOTTOM_EDGE:
                showLauncherApp();
                break;
            default:
                // elevate touch action to child elements
                _activeApp->touchAction(lastX, lastY, deltaX, deltaY, touchType);
                break;
        }
    }
    else
    {
        // elevate touch action to child elements
        _activeApp->touchAction(lastX, lastY, deltaX, deltaY, touchType);
    }
}

void GUI::debugOutput(const String str)
{
    if(_debug.visible)
    {
        _tft->pushRect(_debug.left, _debug.top, _debug.width, _debug.height, _debug.displayContent);
        free(_debug.displayContent);
        _debug.visible = false;
    }
    
    if(str)
    {
        uint16_t textWidth  = _tft->textWidth(str);
        uint16_t textHeight = _tft->fontHeight(2);
        uint16_t boxHeight  = (textHeight * 2) + 7;
        uint16_t boxWidth   = textWidth + (2*8);
        uint16_t topStart   = (TFT_HEIGHT - boxHeight)/2;
        uint16_t leftStart  = (TFT_WIDTH - boxWidth)/2;

        _debug.top = topStart;
        _debug.left = leftStart;
        _debug.width = boxWidth;
        _debug.height = boxHeight;

        _debug.displayContent = ( uint16_t*) ps_calloc(boxWidth * boxHeight, sizeof(uint16_t));
        _tft->readRect(leftStart, topStart, boxWidth, boxHeight, _debug.displayContent);
        
        // background
        _tft->fillRect(leftStart, topStart, boxWidth, boxHeight, TFT_RED);
        _tft->drawRect(leftStart + 1, topStart + textHeight, boxWidth - 2, boxHeight - textHeight -2, TFT_WHITE);

        // element style
        _tft->setTextFont(2);
        _tft->setTextSize(1);
        _tft->setTextColor(TFT_WHITE, TFT_RED);

        _tft->drawString(" DEBUG: ", (TFT_WIDTH - _tft->textWidth(" DEBUG: "))/2, topStart);
        _tft->drawString(str, (TFT_WIDTH - _tft->textWidth(str))/2, topStart + textHeight + 2);
        _debug.visible = true;
    }
}

void GUI::showStandbyApp(bool init)
{
    for(uint8_t i = 0; i<_apps.size(); i++)
    {
        if(_standby == _apps[i])
        {
            showApp(_apps[i], init);
        }
    }
}

void GUI::showLauncherApp(bool init)
{
    for(uint8_t i = 0; i<_apps.size(); i++)
    {
        if(_launcher == _apps[i])
        {
            showApp(_apps[i], init);
        }
    }
}

void GUI::showApp(App* app, bool init, bool task)
{
    _lastApp = _activeApp;
    _activeApp = app;
    if(_lastApp != nullptr)
    {
        _lastApp->clean();
    }
    _activeApp->draw(init, task);
}

void GUI::setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    _ttgo->rtc->setDateTime(year,month,day,hour,minute,second);
    //_ttgo->rtc->syncToRtc();
}

void GUI::taskHandler(void* parameters)
{
    // infinite loop
    for(;;)
    {
        //Serial.println("GUI::taskHandler method");
        _activeApp->draw(false, true);
        yield();
        // Pause the task for 100ms
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void GUI::backgroundTaskHandler()
{
    // this will be the place where the GUI will handle tasks while in sleep mode
    // e.g. alarm or timer or other thingies
    for(uint8_t i = 0; i < _apps.size(); i++)
    {
        _apps[i]->backgroundTaskHandler();
        yield();
    }
}

void GUI::handleEventCallback(ui_event_data_t* eventData)
{
    if(eventData->app)
    {
        eventData->app->elementEventHandler(eventData);
    }
}
