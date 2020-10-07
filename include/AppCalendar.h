/**
    This is the calendar app class
    @file AppCalendar.h
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

class AppCalendar: public App{
    lv_style_t          _styleIconWeekDay;
    lv_style_t          _styleIconMonthDay;
    lv_obj_t*           _calendar;
    lv_calendar_date_t  _today;
    lv_calendar_date_t* _highlightedDays;
    void                _generateLauncherIcon();

    public:
        AppCalendar();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
};

#endif /*__APPCALENDAR_H */
