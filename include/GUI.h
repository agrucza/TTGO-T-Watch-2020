/**
    This is the base GUI class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/

#ifndef __GUI_H
#define __GUI_H

#include "App.h"

#include "TouchMetrics.h"
#include "UITypes.h"

typedef enum {
    ICON_BAT_EMPTY,
    ICON_BAT_1,
    ICON_BAT_2,
    ICON_BAT_3,
    ICON_BAT_FULL,
    ICON_CHARGE,
    ICON_CALCULATION
} icon_battery_t;

class TTGOClass;
class TFT_eSPI;

class GUI {
    struct touch_metrics_t {
        bool touching;
        int16_t x, y, lastX, lastY;
        uint8_t swipeTolerance = 10;
    };

    struct debug_t {
        bool visible;
        uint16_t *displayContent;
        int16_t top,left,width,height;
    };

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
};

#endif /*__GUI_H */