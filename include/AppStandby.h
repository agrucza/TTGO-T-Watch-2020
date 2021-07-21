/**
    This is the standby app class
    @file AppStandby.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPSTANDBY_H
#define __APPSTANDBY_H

#include <Arduino.h>

#include "App.h"

class AppStandby: public App{
    time_t      _currentTime;
    struct tm   _timeInfo;
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;
    uint8_t     _lastMinute;
    uint8_t     _lastMonth;
    public:
        AppStandby();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__APPSTANDBY_H */