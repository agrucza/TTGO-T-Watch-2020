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

#include "lvgl/src/lv_core/lv_obj.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;
typedef _lv_obj_t lv_obj_t;

class UIScreenTesting : public UIScreen{
    GUI*            _gui;

    char*           _label;
    bool            _showInLauncher;

    lv_obj_t*       _container;
    lv_obj_t*       _closeBtn;
    ScreenCallback* _callbackData;
    
    public:
        UIScreenTesting();
        void    show(){if(_container != nullptr){lv_obj_set_hidden(_container,false);lv_obj_move_foreground(_container);}};
        void    hide(){if(_container != nullptr){lv_obj_set_hidden(_container,true);lv_obj_move_background(_container);}};
        bool    showInLauncher(){return _showInLauncher;};
        char*   getLabel(){return _label;};
        void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback);
        void    lvUpdateTask(struct _lv_task_t* data);
        void    updateIcons();
};

#endif /*__UISCREENTESTING_H */
