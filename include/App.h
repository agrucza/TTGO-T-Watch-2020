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

extern GUI* gui;

class App{
    protected:
        GUI*                _gui;

        String              _label;
        bool                _showInLauncher;
        lv_obj_t*           _launcherIcon;

        lv_obj_t*           _container;
        lv_obj_t*           _callbackElement;
        AppCallback*        _callbackData;

        lv_obj_t*           _closeBtn;
        lv_obj_t*           _settingsBtn;
        virtual void        _generateLauncherIcon() = 0;
        
    public:
        App(String label, bool showInLauncher = true);
        
        bool            showInLauncher(){return _showInLauncher;};
        lv_obj_t*       getLauncherIcon(){return _launcherIcon;};
        void            setLauncherIcon(lv_obj_t* launcherIcon){_launcherIcon = launcherIcon; _generateLauncherIcon();};
        String          getLabel(){return _label;};
        
        void            show();
        void            hide();
        
        virtual void    updateTask(struct _lv_task_t* data) = 0;
        void            eventCallback(lv_obj_t* obj, lv_event_t event, AppCallback* callback = nullptr);
        virtual void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr) = 0;
};

#endif /*__APP_H */