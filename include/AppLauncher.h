/**
    This is the launcher app class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPLAUNCHER_H
#define __APPLAUNCHER_H

#include <Arduino.h>

#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

extern GUI* gui;

class AppLauncher : public App{
    uint8_t     _iconsMax;
    uint8_t     _iconAreaWidth;
    uint8_t     _iconAreaHeight;
    uint8_t     _iconW;
    uint8_t     _iconH;
    
    std::vector<std::vector<App*>> _displayIcons;
    
    void        _initDisplayIcons();
    void        _setAppIcon(App* app, uint8_t posX, uint8_t posY);

    public:
        AppLauncher();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__APPLAUNCHER_H */