/**
    This is the testing app class
    @file AppTesting.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __APPTESTING_H
#define __APPTESTING_H

#include <Arduino.h>

#include "UITypes.h"
#include "App.h"
#include "TouchMetrics.h"

class AppTesting : public App{
    public:
        AppTesting();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData);
        void    backgroundTaskHandler(){};
};

#endif /*__APPTESTING_H */
