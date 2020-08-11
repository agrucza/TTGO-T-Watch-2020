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

class GUI;
class TFT_esPI;

class UIScreenCalendar : public UIScreen{
    lv_obj_t*           _calendar;
    lv_calendar_date_t* _highlightedDays;

    public:
        UIScreenCalendar();
        void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback);
        void    lvUpdateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENCALENDAR_H */