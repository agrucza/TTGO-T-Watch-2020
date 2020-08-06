/**
    This is the testing screen class
    @file UIScreenTesting.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UISCREENTESTING_H
#define __UISCREENTESTING_H

#include <Arduino.h>
#include "UITypes.h"
#include "UIScreen.h"
#include "UIContainer.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;

class UIScreenTesting : public UIScreen{
    GUI*            _gui;
    TFT_eSPI*       _tft;
    char*           _label;
    uint8_t         _padding;
    uint8_t         _iconSizeX;
    uint8_t         _iconSizeY;
    UIContainer*    _container;
    
    public:
        UIScreenTesting();
        void    draw(bool init = false, bool task = false);
        char*   getLabel(){return _label;};
        uint8_t getIconSizeX(){return _iconSizeX;};
        uint8_t getIconSizeY(){return _iconSizeY;};
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
};

#endif /*__UISCREENTESTING_H */