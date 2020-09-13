/**
    This is the settings screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __AppSETTINGS_H
#define __AppSETTINGS_H

#include <Arduino.h>

#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class AppSettings : public App{
    public:
        AppSettings();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__AppSETTINGS_H */