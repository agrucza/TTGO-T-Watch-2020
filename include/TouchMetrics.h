/**
    This is the TouchMetrics class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/23/2020
*/

#ifndef __TOUCHMETRICS_H
#define __TOUCHMETRICS_H

#include <Arduino.h>

class TTGOClass;

class TouchMetrics {
    TTGOClass   *_ttgo;
    bool        _touch;
    int16_t     _x, _y, _lastX, _lastY;
    int16_t     _swipeTolerance;
    int16_t     _swipeEdgeDetection;
    public:
        typedef enum{
            TOUCH,
            SWIPE_TOP,
            SWIPE_TOP_EDGE,
            SWIPE_RIGHT,
            SWIPE_RIGHT_EDGE,
            SWIPE_BOTTOM,
            SWIPE_BOTTOM_EDGE,
            SWIPE_LEFT,
            SWIPE_LEFT_EDGE
        } touch_t;

        TouchMetrics();
        void checkTouch();
        bool getTouch(){return _touch;}
        int16_t getSwipeEdgeDetection(){return _swipeEdgeDetection;}
        void setTouch(bool touch){_touch = touch;}
        int16_t getX(){return _x;}
        void setX(int16_t x){_x = x;}
        int16_t getLastX(){return _lastX;}
        void setLastX(int16_t x){_lastX = x;}
        int16_t getY(){return _y;}
        void setY(int16_t y){_y = y;}
        int16_t getLastY(){return _lastY;}
        void setLastY(int16_t y){_lastY = y;}
};

#endif /*__TOUCHMETRICS_H */