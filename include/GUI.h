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

typedef enum {
    ICON_BAT_EMPTY,
    ICON_BAT_1,
    ICON_BAT_2,
    ICON_BAT_3,
    ICON_BAT_FULL,
    ICON_CHARGE,
    ICON_CALCULATION
} icon_battery_t;

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
    uint8_t             cbElement;
    screen_callback_t   command;
    screens_t           target;
    
    public:
        ScreenCallback(UIScreen* origin, uint8_t cbElement, screen_callback_t command, screens_t target = SCREEN_STANDBY)
        {
            this->origin    = origin;
            this->cbElement = cbElement;
            this->command   = command;
            this->target    = target;
        };
        UIScreen*           getOrigin(){return origin;};
        uint8_t             getCbElement(){return cbElement;};
        screen_callback_t   getCommand(){return command;};
        screens_t           getTarget(){return target;};
};

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
        static lv_style_t               borderlessStyle;
        static bool                     isPluggedIn;
        static bool                     isStillConnected;
        static std::vector<icon_t>      systemIcons;

        static void                     setTTGO(TTGOClass *ttgo);
        static TTGOClass*               getTTGO();
        static void                     init();
        static void                     screenEventCallback(lv_obj_t * obj, lv_event_t event);
        static void                     lvUpdateTask(struct _lv_task_t* data);
        static void                     updateTimeLabel(lv_obj_t* label, char* format);
        static void                     wifiConnectStatus(bool set);
        static void                     updateStepCounter();
        static uint32_t                 getStepCounter();
        static void                     updateBatteryLevel();
        static int                      getBatteryLevel(){return _batteryLevel;};
        static char*                    getBatteryIcon();
        static void                     wifiListAdd(const char *ssid);
        static void                     showScreen(screens_t screen);
        static screens_t                getLastScreen(){return _lastScreen;};
        static screens_t                getActiveScreen(){return _activeScreen;};
        static std::vector<screens_t>   getUIScreensForLauncher();
        static char*                    getUIScreenLabel(screens_t screen);
        static void                     setRTC(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
};

#endif /*__GUI_H */
