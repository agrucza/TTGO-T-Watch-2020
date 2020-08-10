/**
    This is the UI class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/24/2020
*/

#ifndef __UISCREEN_H
#define __UISCREEN_H

#include <Arduino.h>
#include "GUI.h"

enum screens_t : uint8_t;

extern GUI* gui;

class UIScreen{
    GUI*                _gui;

    char*               _label;
    bool                _showInLauncher;
    
    lv_obj_t*           _container;
    ScreenCallback*     _callbackData;
    uint8_t             _callbackElement;

    public:
        UIScreen(){
            _gui        = gui;
            _container  = nullptr;
        };
        virtual void    lvUpdateTask(struct _lv_task_t* data) = 0;
        virtual void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback) = 0;
        virtual void    show() = 0;
        virtual void    hide() = 0;
        virtual bool    showInLauncher() = 0;
        virtual char*   getLabel() = 0;
};

#endif /*__UISCREEN_H */