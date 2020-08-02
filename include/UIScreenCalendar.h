/**
    This is the calendar screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENCALENDAR_H
#define __UISCREENCALENDAR_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

class UIScreenCalendar : public UIScreen{
    GUI*        _gui;
    TFT_eSPI*   _tft;
    char*       _label;
    uint8_t     _padding;
    time_t      _currentTime, _displayTime;
    struct tm   _timeInfo, _displayTimeInfo;
    uint8_t     _getDayOfWeek(uint8_t d, uint8_t m, uint16_t y);
    uint8_t     _getDaysOfMonth(uint8_t month, uint16_t year);
    uint8_t     _getDaysOfPrevMonth(uint8_t month, uint16_t year);
    uint8_t     _getDaysOfNextMonth(uint8_t month, uint16_t year);
    void        _setDate(bool init = false);
    uint8_t     _day, _displayDay;
    uint8_t     _month, _displayMonth;
    uint8_t     _startDayOfMonth, _displayStartDayOfMonth;
    uint8_t     _endOfMonth, _displayEndOfMonth, _displayPrevEndOfMonth, _displayNextEndOfMonth;;
    uint16_t    _year, _displayYear;
    void        _drawCalendar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t padding, bool numbers);
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;

    public:
        UIScreenCalendar();
        void    draw(bool init = false);
        char*   getLabel(){return _label;};
        uint8_t getIconSizeX(){return _iconSizeX;};
        uint8_t getIconSizeY(){return _iconSizeY;};
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
};

#endif /*__UISCREENCALENDAR_H */