/**
    This is the base GUI class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/

#ifndef __GUI_H
#define __GUI_H

#include "config.h"
#include "LilyGoWatch.h"

class App;

struct icon_t{
    lv_obj_t*   obj;
    String      label;
    bool        show;
    bool        shownBefore;
};

enum app_callback_t{
    CALLBACK_NONE,
    CALLBACK_SWITCH_APP
};

typedef enum {
    ICON_BAT_EMPTY,
    ICON_BAT_1,
    ICON_BAT_2,
    ICON_BAT_3,
    ICON_BAT_FULL,
    ICON_CHARGE,
    ICON_CALCULATION
} icon_battery_t;

class AppCallback{
    App*            origin;
    app_callback_t  command;
    App*            target;
    
    public:
        AppCallback(App* origin, app_callback_t command, App* target = nullptr)
        {
            this->origin    = origin;
            this->command   = command;
            this->target    = target;
        };
        App*            getOrigin(){return origin;};
        app_callback_t  getCommand(){return command;};
        App*            getTarget(){return target;};
};

class TTGOClass;
class TFT_eSPI;

class GUI {
    static TTGOClass*                   _ttgo;
    static uint32_t                     _stepCounter;
    static std::vector<App*>            _apps;
    static App*                         _lastApp;
    static App*                         _activeApp;
    static int                          _batteryLevel;

    public:
        static lv_task_t*               lvUpdateTask;
        static lv_style_t               styleBorderless;
        static lv_style_t               modalStyle;
        static bool                     isPluggedIn;
        static bool                     isStillConnected;
        static std::vector<icon_t>      systemIcons;
        static std::vector<String>      wifiSSIDs;

        static int8_t                   timeZone;
        static char                     timeFormatHM[];
        static char                     timeFormatHMS[];
        static char                     dateFormat[];
        static char                     dateFormatLong[];

        static void                     setTTGO(TTGOClass *ttgo);
        static TTGOClass*               getTTGO();
        static void                     init();
        static void                     appEventCallback(lv_obj_t* obj, lv_event_t event);
        static void                     modalEventCallback(lv_obj_t* obj, lv_event_t event);
        static void                     updateTask(struct _lv_task_t* data);
        static void                     lvUpdateTaskMethod(struct _lv_task_t* data){ lv_task_set_period(lvUpdateTask, lv_task_handler());};
        static void                     updateTimeLabel(lv_obj_t* label, String format);
        static void                     wifiConnectStatus(bool set);
        static void                     updateStepCounter();
        static uint32_t                 getStepCounter();
        static void                     updateBatteryLevel();
        static int                      getBatteryLevel(){return _batteryLevel;};
        static String                   getBatteryIcon();
        static App*                     getApp(String label);
        static void                     showApp(String label);
        static void                     showApp(App* app);
        static App*                     getLastApp(){return _lastApp;};
        static App*                     getActiveApp(){return _activeApp;};
        static std::vector<App*>        getAppsForLauncher();
        static String                   getAppLabel(App* app);
        static RTC_Date                 getDateTime();
        static String                   getRTCHMS();
        static String                   getRTCDDMMYYYY();
        static void                     setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
};

#endif /*__GUI_H */
