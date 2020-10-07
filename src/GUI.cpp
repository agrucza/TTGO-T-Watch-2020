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

#include "AppStandby.h"
#include "AppLauncher.h"
#include "AppTesting.h"
#include "AppCalendar.h"
#include "AppSettings.h"

TTGOClass*              GUI::_ttgo              = nullptr;
uint32_t                GUI::_stepCounter       = 0;
std::vector<App*>       GUI::_apps;
App*                    GUI::_lastApp           = nullptr;
App*                    GUI::_activeApp         = nullptr;
int                     GUI::_batteryLevel      = 0;
lv_style_t              GUI::styleBorderless;
lv_style_t              GUI::styleModal;
std::vector<icon_t>     GUI::systemIcons;
std::vector<String>     GUI::wifiSSIDs;
bool                    GUI::isPluggedIn;
bool                    GUI::isStillConnected;
int8_t                  GUI::timeZone           = 1;
char                    GUI::timeFormatHM[]     = "%H:%M";
char                    GUI::timeFormatHMS[]    = "%H:%M:%S";
char                    GUI::dateFormat[]       = "%d.%m.%Y";
char                    GUI::dateFormatLong[]   = "%a %d %B";
lv_task_t*              GUI::lvUpdateTask;

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
    _lastApp = _activeApp = getApp("Standby");

    _ttgo->motor_begin();

    lv_style_init(&styleBorderless);
    lv_style_set_border_width(&styleBorderless,LV_STATE_DEFAULT,0);

    lv_style_init(&styleModal);
    lv_style_set_bg_color(&styleModal, LV_OBJ_PART_MAIN, LV_COLOR_BLACK);
    lv_style_set_bg_opa(&styleModal, LV_OBJ_PART_MAIN, LV_OPA_50);
    lv_style_set_border_width(&styleModal, LV_OBJ_PART_MAIN, 0);
    lv_style_set_radius(&styleModal, LV_OBJ_PART_MAIN, 0);

    systemIcons.push_back({nullptr,LV_SYMBOL_BELL,false,false});
    systemIcons.push_back({nullptr,LV_SYMBOL_WIFI,false,false});
    systemIcons.push_back({nullptr,LV_SYMBOL_BLUETOOTH,false,false});
    systemIcons.push_back({nullptr,LV_SYMBOL_CHARGE,true,true});

    lv_task_create(updateTask, 200, LV_TASK_PRIO_MID, NULL);
    lvUpdateTask = lv_task_create(lvUpdateTaskMethod, lv_task_handler(), LV_TASK_PRIO_HIGH, NULL);
    updateBatteryLevel();

    // creating apps
    _apps.push_back(new AppStandby());
    _apps.push_back(new AppTesting());
    _apps.push_back(new AppSettings());
    _apps.push_back(new AppCalendar());
    _apps.push_back(new AppLauncher());

    // as we init the GUI here we want to start the standby app
    _ttgo->openBL();
    showApp("Standby");
}

void GUI::updateTask(struct _lv_task_t* data){
    //_ttgo->motor->onec();
    updateBatteryLevel();
    _activeApp->updateTask(data);
};

void GUI::appEventCallback(lv_obj_t * obj, lv_event_t event)
{
    AppCallback* data = (AppCallback*)lv_obj_get_user_data(obj);
    switch(data->getCommand())
    {
        case CALLBACK_SWITCH_APP:
            if(event == LV_EVENT_SHORT_CLICKED)
            {
                _ttgo->motor->onec(100);
                showApp(getApp(data->getTarget()));
            }
            break;
        default:
            getApp(data->getOrigin())->eventCallback(obj, event, data);
    }
}

void GUI::modalEventCallback(lv_obj_t * obj, lv_event_t event)
{
    UIModal* modal = (UIModal*)lv_obj_get_user_data(obj);
    modal->eventCallback(obj, event);
}

void GUI::updateTimeLabel(lv_obj_t* label, String format)
{
    time_t now;
    struct tm  info;
    char buf[64];
    time(&now);
    localtime_r(&now, &info);
    strftime(buf, sizeof(buf), format.c_str(), &info);
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
    if(_ttgo->power->isChargeing())
    {
        isPluggedIn = true;
        isStillConnected = false;
    }
}

String GUI::getBatteryIcon()
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

App* GUI::getApp(String label)
{
    for(uint8_t i = 0; i<_apps.size(); i++)
    {
        if(_apps[i]->getLabel() == label)
        {
            return _apps[i];
        }
    }

    return nullptr;
}

void GUI::showApp(String label)
{
    showApp(getApp(label));
}

void GUI::showApp(App* app)
{
    _lastApp = _activeApp;
    _activeApp = app;
    if(_lastApp != nullptr)
    {
        _lastApp->hide();
    }
    _activeApp->show();
}


std::vector<App*> GUI::getAppsForLauncher()
{
    std::vector<App*> apps;
    
    for(uint8_t i = 0; i < _apps.size(); i++)
    {
        bool launcher = _apps[i]->showInLauncher();
        
        if(launcher)
        {
            apps.push_back(_apps[i]);
        }
    }
    
    return apps;
}

String GUI::getAppLabel(App* app)
{
    app->getLabel();
}

RTC_Date GUI::getDateTime()
{
    return _ttgo->rtc->getDateTime();
}

String GUI::getRTCHMS()
{
    return _ttgo->rtc->formatDateTime(PCF_TIMEFORMAT_HMS);
}

String GUI::getRTCDDMMYYYY()
{
    return _ttgo->rtc->formatDateTime(PCF_TIMEFORMAT_DD_MM_YYYY);
}

void GUI::setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
    _ttgo->rtc->setDateTime(year,month,day,hour,minute,second);
    //_ttgo->rtc->syncToRtc();
}