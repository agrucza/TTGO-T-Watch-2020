/**
    This is the UI class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/24/2020
*/

#ifndef __UISCREEN_H
#define __UISCREEN_H

#include <Arduino.h>
#include "TouchMetrics.h"

class GUI;
class TFT_eSPI;

enum screens_t : uint8_t;

class UIScreen{
    GUI         *_gui;
    TFT_eSPI    *_tft;
    char*       _label;
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;

    public:
        virtual ~UIScreen(){};
        virtual void    draw(bool init = false, bool task = false) = 0;
        virtual uint8_t getIconSizeX() = 0;
        virtual uint8_t getIconSizeY() = 0;
        virtual void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h) = 0;
        virtual char*   getLabel(){return _label;};
        virtual void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType) = 0;
};

#endif /*__UISCREEN_H */