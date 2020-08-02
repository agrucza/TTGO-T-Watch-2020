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

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;

class UIScreenMain : public UIScreen{
    GUI*        _gui;
    TFT_eSPI*   _tft;
    char*       _label;
    uint8_t     _padding;
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;
    uint8_t     _iconsMax;
    uint8_t     _iconAreaWidth;
    uint8_t     _iconAreaHeight;
    uint8_t     _iconW;
    uint8_t     _iconH;
    
    std::vector<std::vector<screens_t>> _displayIcons;
    
    void        _initDisplayIcons();
    void        _setScreenIcon(screens_t screen, uint8_t posX, uint8_t posY);

    public:
        UIScreenMain();
        void    draw(bool init = false);
        //char*   getLabel(){return _label;};
        uint8_t getIconSizeX(){return _iconSizeX;};
        uint8_t getIconSizeY(){return _iconSizeY;};
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
};

#endif /*__UISCREENMAIN_H */