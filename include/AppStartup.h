/**
    This is the launcher app class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPSTARTUP_H
#define __APPSTARTUP_H

#include <Arduino.h>

#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class AppStartup : public App{
    public:
        AppStartup();
        void    draw(bool init = false, bool task = false);
        uint8_t getIconSizeX(){return _iconSizeX;};
        uint8_t getIconSizeY(){return _iconSizeY;};
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__APPSTARTUP_H */