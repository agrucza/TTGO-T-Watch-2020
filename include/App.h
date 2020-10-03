/**
    This is the App class
    @file App.h
    @author Alexander Grucza
    @version 0.1 7/24/2020
*/

#ifndef __APP_H
#define __APP_H

#include <Arduino.h>
#include "GUI.h"
#include "UIModal.h"

enum apps_t : uint8_t;

extern GUI* gui;

class App{
    public:
        GUI*                _gui;

        char*               _label;
        bool                _showInLauncher;
        
        lv_obj_t*           _container;
        lv_obj_t*           _callbackElement;
        AppCallback*        _callbackData;

        lv_obj_t*           _closeBtn;
        lv_obj_t*           _settingsBtn;
        
        App();
        
        bool            showInLauncher(){return _showInLauncher;};
        char*           getLabel(){return _label;};
        
        void            show();
        void            hide();
        
        virtual void    updateTask(struct _lv_task_t* data) = 0;
        void            eventCallback(lv_obj_t* obj, lv_event_t event, AppCallback* callback = nullptr);
        virtual void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr) = 0;
};

#endif /*__APP_H */