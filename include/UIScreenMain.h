/**
    This is the main screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENMAIN_H
#define __UISCREENMAIN_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

class UIScreenMain : public UIScreen{
    GUI*        _gui;
    TFT_eSPI*   _tft;
    uint8_t     _screensX;
    uint8_t     _screensY;
    uint8_t     _screensPerPage;
    uint8_t     _screenCount;
    uint8_t     _page;
    uint8_t     _pageMax;
    uint8_t     _pageAmount;
    uint8_t     _padding;
    uint8_t     _visibleScreen;
    uint8_t     _firstScreen;
    uint8_t     _lastScreen;
    uint8_t     _screenWidth;
    uint8_t     _screenHeight;

    public:
        UIScreenMain();
        void draw(bool init = false);
        void drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
};

#endif /*__UISCREENMAIN_H */