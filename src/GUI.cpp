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

#include "UIScreenStandby.h"
#include "UIScreenMain.h"
#include "UIScreenTesting.h"
#include "UIScreenCalendar.h"
#include "UIScreenSettings.h"

TTGOClass*              GUI::_ttgo              = nullptr;
uint32_t                GUI::_stepCounter       = 0;
std::vector<UIScreen*>  GUI::_screens;
screens_t               GUI::_lastScreen        = SCREEN_STANDBY;
screens_t               GUI::_activeScreen      = SCREEN_STANDBY;
int                     GUI::_batteryLevel      = 0;
lv_style_t              GUI::borderlessStyle;
lv_style_t              GUI::modalStyle;
std::vector<icon_t>     GUI::systemIcons;
bool                    GUI::isPluggedIn;
bool                    GUI::isStillConnected;
int8_t                  GUI::timeZone           = 1;
char                    GUI::timeFormatHM[]     = "%H:%M";
char                    GUI::timeFormatHMS[]    = "%H:%M:%S";
char                    GUI::dateFormat[]       = "%d.%m.%Y";
char                    GUI::dateFormatLong[]   = "%a %d %B";

/**
 * @brief  Sets the TTGOClass object to the GUI class
 * @note   
 * @param  *ttgo: ttgo watch reference
 * @retval None
 */
void GUI::setTTGO(TTGOClass *ttgo)
{
    _ttgo = ttgo;
}

/**
 * @brief  Returns the TTGOClass watch reference
 * @note   
 * @retval TTGOClass watch reference
 */
TTGOClass* GUI::getTTGO()
{
    return _ttgo;
}

/**
 * @brief  Inits the GUI
 * @note   
 * @retval None
 */
void GUI::init()
{
    _ttgo->motor_begin();

    lv_style_init(&borderlessStyle);
    lv_style_set_border_width(&borderlessStyle,LV_STATE_DEFAULT,0);

    lv_style_init(&modalStyle);
    lv_style_set_bg_color(&modalStyle, LV_OBJ_PART_MAIN, LV_COLOR_BLACK);
    lv_style_set_bg_opa(&modalStyle, LV_OBJ_PART_MAIN, LV_OPA_50);
    lv_style_set_border_width(&modalStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_radius(&modalStyle, LV_OBJ_PART_MAIN, 0);

    systemIcons.push_back({nullptr,LV_SYMBOL_BELL,false,false});
    systemIcons.push_back({nullptr,LV_SYMBOL_WIFI,false,false});
    systemIcons.push_back({nullptr,LV_SYMBOL_BLUETOOTH,false,false});
    systemIcons.push_back({nullptr,LV_SYMBOL_CHARGE,true,true});

    lv_task_create(lvUpdateTask, 1000, LV_TASK_PRIO_LOWEST, NULL);
    updateBatteryLevel();

    // creating screens
    _screens.push_back(new UIScreenStandby());
    _screens.push_back(new UIScreenMain());
    _screens.push_back(new UIScreenTesting());
    _screens.push_back(new UIScreenSettings());
    _screens.push_back(new UIScreenCalendar());

    // as we init the GUI here we want to start the standby screen
    _ttgo->openBL();
    showScreen(SCREEN_STANDBY);
}

void GUI::lvUpdateTask(struct _lv_task_t* data){
    //_ttgo->motor->onec();
    updateBatteryLevel();
    _screens[_activeScreen]->lvUpdateTask(data);
};

void GUI::screenEventCallback(lv_obj_t * obj, lv_event_t event)
{
    ScreenCallback* data = (ScreenCallback*)lv_obj_get_user_data(obj);
    switch(data->getCommand())
    {
        case CALLBACK_SWITCH_SCREEN:
            if(event == LV_EVENT_CLICKED){
                showScreen(data->getTarget());
            }
            break;
        default:
            data->getOrigin()->eventCallback(obj, event, data);
    }
}

void GUI::modalEventCallback(lv_obj_t * obj, lv_event_t event)
{
    UIModal* modal = (UIModal*)lv_obj_get_user_data(obj);
    modal->eventCallback(obj, event);
}

void GUI::updateTimeLabel(lv_obj_t* label, char* format)
{
    time_t now;
    struct tm  info;
    char buf[64];
    time(&now);
    localtime_r(&now, &info);
    strftime(buf, sizeof(buf), format, &info);
    lv_label_set_text(label, buf);
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

char* GUI::getBatteryIcon()
{
    updateBatteryLevel();

    if(isPluggedIn && isStillConnected){
        return LV_SYMBOL_USB;
    }
    else if(isPluggedIn)
    {
        return LV_SYMBOL_CHARGE;
    }
    else if(_batteryLevel > 75 && _batteryLevel <= 100)
    {
        return LV_SYMBOL_BATTERY_FULL;
    }
    else if(_batteryLevel > 50 && _batteryLevel <= 75)
    {
        return LV_SYMBOL_BATTERY_3;
    }
    else if(_batteryLevel > 25 && _batteryLevel <= 50)
    {
        return LV_SYMBOL_BATTERY_2;
    }
    else if(_batteryLevel > 5 && _batteryLevel <= 25)
    {
        return LV_SYMBOL_BATTERY_1;
    }
    else
    {
        return LV_SYMBOL_BATTERY_EMPTY;
    }
}

/**
 * @brief  Adds an SSID to the wifi list
 * @note   
 * @param  *ssid: name of ssid to add to the wifi list
 * @retval None
 */
void GUI::wifiListAdd(const char *ssid){

}

void GUI::showScreen(screens_t screen)
{
    _lastScreen = _activeScreen;
    _activeScreen = screen;
    _screens[_lastScreen]->hide();
    _screens[_activeScreen]->show();
}


std::vector<screens_t> GUI::getUIScreensForLauncher()
{
    std::vector<screens_t> screens;
    
    for(uint8_t i = 0; i < _screens.size(); i++)
    {
        bool launcher = _screens[i]->showInLauncher();
        
        if(launcher)
        {
            screens.push_back(static_cast<screens_t>(i));
        }
    }
    
    return screens;
}

char* GUI::getUIScreenLabel(screens_t screen)
{
    return _screens[screen]->getLabel();
}

RTC_Date GUI::getDateTime()
{
    return _ttgo->rtc->getDateTime();
}

const char* GUI::getRTCHMS()
{
    return _ttgo->rtc->formatDateTime(PCF_TIMEFORMAT_HMS);
}

const char* GUI::getRTCDDMMYYYY()
{
    return _ttgo->rtc->formatDateTime(PCF_TIMEFORMAT_DD_MM_YYYY);
}

void GUI::setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    _ttgo->rtc->setDateTime(year,month,day,hour,minute,second);
    //_ttgo->rtc->syncToRtc();
}