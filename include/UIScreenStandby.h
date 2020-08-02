/**
    This is the standby screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENSTANDBY_H
#define __UISCREENSTANDBY_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class UIScreenStandby: public UIScreen{
    GUI*        _gui;
    TFT_eSPI*   _tft;
    char*       _label;
    time_t      _currentTime;
    struct tm   _timeInfo;
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;

    void _fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
    public:
        UIScreenStandby();
        void    draw(bool init = false);
        uint8_t getIconSizeX(){return _iconSizeX;};
        uint8_t getIconSizeY(){return _iconSizeY;};
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
};

#endif /*__UISCREENSTANDBY_H */