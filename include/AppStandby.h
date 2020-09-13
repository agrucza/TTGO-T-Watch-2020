/**
    This is the standby screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __AppSTANDBY_H
#define __AppSTANDBY_H

#include <Arduino.h>

#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class AppStandby: public App{
    time_t      _currentTime;
    struct tm   _timeInfo;
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;
    uint8_t     _lastMinute;
    uint8_t     _lastMonth;

    void _fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
    public:
        AppStandby();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__AppSTANDBY_H */