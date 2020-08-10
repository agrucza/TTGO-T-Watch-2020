/**
    This is the standby screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENSTANDBY_H
#define __UISCREENSTANDBY_H

#include <Arduino.h>
#include "UIScreen.h"

#include "lvgl/src/lv_core/lv_obj.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;
typedef _lv_obj_t lv_obj_t;

class UIScreenStandby : public UIScreen{
    GUI*                _gui;
    ScreenCallback*     _callbackData;
    uint8_t             _callbackElement;

    char*               _label;
    bool                _showInLauncher;

    lv_obj_t*           _container;
    lv_style_t          _containerStyle;
    
    lv_obj_t*           _timeLabel;
    char*               _timeLabelFormat;
    lv_style_t          _timeLabelStyle;
    
    lv_obj_t*           _dateLabel;
    char*               _dateLabelFormat;
    lv_style_t          _dateLabelStyle;

    lv_obj_t*           _iconContainer;
    lv_style_t          _iconContainerStyle;

    lv_obj_t*           _touchNotifyLabel;

    lv_obj_t*           _touchLabel;
    bool                _touched;

    public:
        UIScreenStandby();
        void    show(){if(_container != nullptr){lv_obj_set_hidden(_container,false);lv_obj_move_foreground(_container);}};
        void    hide(){if(_container != nullptr){lv_obj_set_hidden(_container,true);lv_obj_move_background(_container);}};
        bool    showInLauncher(){return _showInLauncher;};
        char*   getLabel(){return _label;};
        void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback);
        void    lvUpdateTask(struct _lv_task_t* data);
        void    updateIcons();
};

#endif /*__UISCREENSTANDBY_H */
