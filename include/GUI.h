/**
    This is the base GUI class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/

#ifndef __GUI_H
#define __GUI_H

<<<<<<< HEAD
#include "config.h"
#include "LilyGoWatch.h"

class UIScreen;

struct icon_t{
    lv_obj_t*   obj;
    char*       label;
    bool        show;
    bool        shownBefore;
};

enum screen_callback_t{
    CALLBACK_NONE,
    CALLBACK_SWITCH_SCREEN
};
=======
#include "TouchMetrics.h"
#include "App.h"
#include "UITypes.h"
>>>>>>> no_lvgl

typedef enum {
    ICON_BAT_EMPTY,
    ICON_BAT_1,
    ICON_BAT_2,
    ICON_BAT_3,
    ICON_BAT_FULL,
    ICON_CHARGE,
    ICON_CALCULATION
} icon_battery_t;

<<<<<<< HEAD
enum screens_t : uint8_t {
    SCREEN_STANDBY,
    SCREEN_MAIN,
    SCREEN_TESTING,
    SCREEN_CALENDAR,
    SCREEN_SETTINGS,
    SCREEN_COUNT
};

class ScreenCallback{
    UIScreen*           origin;
    screen_callback_t   command;
    screens_t           target;
    
    public:
        ScreenCallback(UIScreen* origin, screen_callback_t command, screens_t target = SCREEN_STANDBY)
        {
            this->origin    = origin;
            this->command   = command;
            this->target    = target;
        };
        UIScreen*           getOrigin(){return origin;};
        screen_callback_t   getCommand(){return command;};
        screens_t           getTarget(){return target;};
};

=======
>>>>>>> no_lvgl
class TTGOClass;
class TFT_eSPI;

class GUI {
    static TTGOClass*                   _ttgo;
    static uint32_t                     _stepCounter;
    static std::vector<UIScreen*>       _screens;
    static screens_t                    _lastScreen;
    static screens_t                    _activeScreen;
    static int                          _batteryLevel;

    public:
        static lv_task_t*               lvUpdateTask;
        static lv_style_t               borderlessStyle;
        static lv_style_t               modalStyle;
        static bool                     isPluggedIn;
        static bool                     isStillConnected;
        static std::vector<icon_t>      systemIcons;
        static std::vector<String>      wifiSSIDs;

<<<<<<< HEAD
        static int8_t                   timeZone;
        static char                     timeFormatHM[];
        static char                     timeFormatHMS[];
        static char                     dateFormat[];
        static char                     dateFormatLong[];

        static void                     setTTGO(TTGOClass *ttgo);
        static TTGOClass*               getTTGO();
        static void                     init();
        static void                     screenEventCallback(lv_obj_t* obj, lv_event_t event);
        static void                     modalEventCallback(lv_obj_t* obj, lv_event_t event);
        static void                     updateTask(struct _lv_task_t* data);
        static void                     lvUpdateTaskMethod(struct _lv_task_t* data){ lv_task_set_period(lvUpdateTask, lv_task_handler());};
        static void                     updateTimeLabel(lv_obj_t* label, char* format);
        static void                     wifiConnectStatus(bool set);
        static void                     updateStepCounter();
        static uint32_t                 getStepCounter();
        static void                     updateBatteryLevel();
        static int                      getBatteryLevel(){return _batteryLevel;};
        static char*                    getBatteryIcon();
        static void                     showScreen(screens_t screen);
        static screens_t                getLastScreen(){return _lastScreen;};
        static screens_t                getActiveScreen(){return _activeScreen;};
        static std::vector<screens_t>   getUIScreensForLauncher();
        static char*                    getUIScreenLabel(screens_t screen);
        static RTC_Date                 getDateTime();
        static const char*              getRTCHMS();
        static const char*              getRTCDDMMYYYY();
        static void                     setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
=======
    static TTGOClass*           _ttgo;
    static TFT_eSPI*            _tft;
    static uint32_t             _stepCounter;
    static TouchMetrics*        _touch;
    static debug_t              _debug;
    static unsigned long        _lastActionTime;
    static std::vector<App*>    _apps;
    static App*                 _lastApp;
    static App*                 _activeApp;
    static App*                 _standby;
    static App*                 _launcher;
    static icon_battery_t       _batteryIcon;
    static int                  _batteryLevel;

    public:
        static TaskHandle_t     taskHandle;
        static void             setTTGO(TTGOClass *ttgo);
        static TTGOClass        *getTTGO();
        static TFT_eSPI         *getTFT();
        static void             init();
        static void             touchAction(int16_t _lastX, int16_t _lasty, int16_t _deltaX, int16_t _deltaY, TouchMetrics::touch_t touchType);
        static unsigned long    getInactivityTime()
        {
            if(millis() < _lastActionTime)
            {
                _lastActionTime = millis();
            }
            return millis() - _lastActionTime;
        }
        static void             setLastActionTime(unsigned long millis){_lastActionTime = millis;}
        static void             wifiConnectStatus(bool set);
        static void             updateStepCounter();
        static uint32_t         getStepCounter();
        static void             updateBatteryLevel();
        static int              getBatteryLevel(){return _batteryLevel;};
        static void             updateBatteryIcon(icon_battery_t index);
        static icon_battery_t   getBatteryIcon(){return _batteryIcon;};
        static void             wifiListAdd(const String ssid);
        static void             checkTouchScreen();
        static void             debugOutput(const String str);

        static std::vector<App*> getApps(){return _apps;};
        static void             setStandbyApp(App* app){_standby = app;};
        static App*             getStandbyApp(){return _standby;};
        static void             showStandbyApp(bool init = false);
        static void             setLauncherApp(App* app){_launcher = app;};
        static App*             getLauncherApp(){return _launcher;};
        static void             showLauncherApp(bool init = false);
        static void             showApp(App* app, bool init = false, bool task = false);
        static App*             getLastApp(){return _lastApp;};
        static App*             getActiveApp(){return _activeApp;};
        static void             addApp(App* app){_apps.push_back(app);};
        
        static void             setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
        static void             taskHandler(void * parameters);
        static void             backgroundTaskHandler();
        static void             handleEventCallback(ui_event_data_t* eventData);
>>>>>>> no_lvgl
};

#endif /*__GUI_H */
