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
    GUI*                _gui;

    char*               _label;
    bool                _showInLauncher;
    
    lv_obj_t*           _container;
    lv_obj_t*           _closeBtn;
    ScreenCallback*     _callbackData;
    uint8_t             _callbackElement;
    lv_obj_t*           _calendar;
    lv_calendar_date_t* _highlightedDays;

    public:
        UIScreenCalendar();
        void    show(){if(_container != nullptr){lv_obj_set_hidden(_container,false);lv_obj_move_foreground(_container);}};
        void    hide(){if(_container != nullptr){lv_obj_set_hidden(_container,true);lv_obj_move_background(_container);}};
        bool    showInLauncher(){return _showInLauncher;};
        char*   getLabel(){return _label;};
        void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback);
        void    lvUpdateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENCALENDAR_H */