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
    public:
        GUI*                _gui;

        char*               _label;
        bool                _showInLauncher;
        
        lv_obj_t*           _container;
        ScreenCallback*     _callbackData;
        uint8_t             _callbackElement;
        
        uint8_t             _activeModal;

        std::vector<lv_obj_t*> _modals;
        
        UIScreen(){
            _gui                = gui;
            _container          = nullptr;
            _callbackElement    = 0;
            _activeModal        = 0;
        };
        
        bool            showInLauncher(){return _showInLauncher;};
        char*           getLabel(){return _label;};
        
        void            show();
        void            hide();

        void            modalVisibility(uint8_t element, bool visible);
        
        virtual void    lvUpdateTask(struct _lv_task_t* data) = 0;
        virtual void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback) = 0;
};

#endif /*__UISCREEN_H */