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
#include "UIModal.h"

enum screens_t : uint8_t;

extern GUI* gui;

class UIScreen{
    public:
        GUI*                _gui;

        char*               _label;
        bool                _showInLauncher;
        
        lv_obj_t*           _container;
        lv_obj_t*           _callbackElement;
        ScreenCallback*     _callbackData;

        lv_obj_t*           _closeBtn;
        lv_obj_t*           _settingsBtn;
        
        UIScreen(){
            _gui                = gui;
            _container          = nullptr;
            _callbackElement    = nullptr;
        };
        
        bool            showInLauncher(){return _showInLauncher;};
        char*           getLabel(){return _label;};
        
        void            show();
        void            hide();
        
        virtual void    lvUpdateTask(struct _lv_task_t* data) = 0;
        void            eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback = nullptr);
        virtual void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback = nullptr) = 0;
};

#endif /*__UISCREEN_H */