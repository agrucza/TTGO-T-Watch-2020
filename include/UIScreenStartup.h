/**
    This is the main screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENSTARTUP_H
#define __UISCREENSTARTUP_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class UIScreenStartup : public UIScreen{
    public:
        UIScreenStartup();
        void    draw(bool init = false, bool task = false);
        uint8_t getIconSizeX(){return _iconSizeX;};
        uint8_t getIconSizeY(){return _iconSizeY;};
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    sleepTaskHandler(){};
};

#endif /*__UISCREENSTARTUP_H */