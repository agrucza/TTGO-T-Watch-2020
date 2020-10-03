/**
    This is the standby app class
    @file AppStandby.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPSTANDBY_H
#define __APPSTANDBY_H

#include <Arduino.h>
#include "App.h"

#include "lvgl/src/lv_core/lv_obj.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;
typedef _lv_obj_t lv_obj_t;

class AppStandby : public App{
    lv_obj_t*           _timeLabel;
    lv_style_t          _timeLabelStyle;
    
    lv_obj_t*           _dateLabel;
    lv_style_t          _dateLabelStyle;

    lv_obj_t*           _iconContainer;
    lv_style_t          _iconContainerStyle;

    lv_obj_t*           _touchNotifyLabel;

    lv_obj_t*           _touchLabel;
    bool                _touched;

    public:
        AppStandby();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
        void    updateIcons();
};

#endif /*__APPSTANDBY_H */
