/**
    This is the calendar app class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPCALENDAR_H
#define __APPCALENDAR_H

#include <Arduino.h>

#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class AppCalendar : public App{
    uint16_t    _weekDayColor, _weekEndColor, _todayColor, _highlightDayColor;
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
    uint8_t     _todayLabelWidth;
    uint8_t     _todayLabelHeight;

    public:
        AppCalendar();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__APPCALENDAR_H */