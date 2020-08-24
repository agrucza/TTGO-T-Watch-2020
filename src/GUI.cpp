/**
    This is the base GUI class
    @file gui.pp
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/
 
// Please select the model you want to use in config.h
#include "config.h"
#include "LilyGoWatch.h"
#include "GUI.h"

#include "UIScreenStartup.h"
#include "UIScreenStandby.h"
#include "UIScreenMain.h"
#include "UIScreenTesting.h"
#include "UIScreenCalendar.h"
#include "UIScreenSettings.h"

TTGOClass*              GUI::_ttgo              = nullptr;
TFT_eSPI*               GUI::_tft               = nullptr;
uint32_t                GUI::_stepCounter       = 0;
TouchMetrics*           GUI::_touch;
GUI::debug_t            GUI::_debug;
unsigned long           GUI::_lastActionTime    = 0;
UIScreen*               GUI::_screens[SCREEN_COUNT];
screens_t               GUI::_lastScreen        = SCREEN_MAIN;
screens_t               GUI::_activeScreen      = SCREEN_STANDBY;
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
    _tft->fillScreen(TFT_BLACK);
    _touch = new TouchMetrics();
    _touch->setTouch(false);
    _lastActionTime = millis();
    updateBatteryLevel();

    // creating screens
    _screens[SCREEN_STARTUP]    = new UIScreenStartup();
    _screens[SCREEN_STANDBY]    = new UIScreenStandby();
    _screens[SCREEN_TESTING]    = new UIScreenTesting();
    _screens[SCREEN_CALENDAR]   = new UIScreenCalendar();
    _screens[SCREEN_SETTINGS]   = new UIScreenSettings();

    // by now main needs to be initialized after all other screens
    // otherwise there will be a fatal error when the launcher
    // tries to access other screens methods
    _screens[SCREEN_MAIN]       = new UIScreenMain();

    // as we init the GUI here we want to start the standby screen
    setScreen(SCREEN_STARTUP);
    //setScreen(SCREEN_TESTING);
    
    if(_ttgo->power->isChargeing())
    {
        _batteryIcon = ICON_CHARGE;
    }
    
    xTaskCreate(
        taskHandler,        // call GUI task hadler
        "GUI task handler", // Name of the task (for debugging)
        4096,               // Stack size (bytes)
        NULL,               // Parameter to pass
        1,                  // Task priority
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
void GUI::wifiListAdd(const char *ssid){

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
    // elevate touch action to child elements
    _screens[_activeScreen]->touchAction(lastX, lastY, deltaX, deltaY, touchType);
}

void GUI::debugOutput(const char *str)
{
    if(_debug.visible){
        _tft->pushRect(_debug.left, _debug.top, _debug.width, _debug.height, _debug.displayContent);
        free(_debug.displayContent);
        _debug.visible = false;
    }
    
    if(str != nullptr)
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

void GUI::setScreen(screens_t screen, bool init)
{
    _lastScreen = _activeScreen;
    _activeScreen = screen;
    _screens[screen]->draw(init);
}

void GUI::drawUIScreenIcon(screens_t screen, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    if(screen > SCREEN_MAIN)
    {
        _screens[screen]->drawIcon(x, y,  w, h);
    }
}

String GUI::getUIScreenLabel(screens_t screen)
{
    return _screens[screen]->getLabel();
}

void GUI::setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    _ttgo->rtc->setDateTime(year,month,day,hour,minute,second);
    //_ttgo->rtc->syncToRtc();
}

void GUI::taskHandler(void* parameters)
{
    for(;;){ // infinite loop
        // Pause the task for 1000ms
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        _screens[_activeScreen]->draw(false, true);
    }
}