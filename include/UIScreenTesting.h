/**
    This is the testing screen class
    @file UIScreenTesting.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UISCREENTESTING_H
#define __UISCREENTESTING_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

enum screens_t : uint8_t;

class UIScreenTesting : public UIScreen{
    public:
        UIScreenTesting();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    sleepTaskHandler(){};
};

#endif /*__UISCREENTESTING_H */
