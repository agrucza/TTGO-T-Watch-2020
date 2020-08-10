/**
    This is the main screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENMAIN_H
#define __UISCREENMAIN_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;

class UIScreenMain : public UIScreen{
    GUI*                _gui;
    lv_obj_t*           _container;

    char*               _label;
    bool                _showInLauncher;

    std::vector<icon_t> _launcherIcons;
    std::vector<ScreenCallback*>   _callbackData;
    uint8_t             _callbackElement;

    public:
        UIScreenMain();
        void    show(){if(_container != nullptr){lv_obj_set_hidden(_container,false);lv_obj_move_foreground(_container);}};
        void    hide(){if(_container != nullptr){lv_obj_set_hidden(_container,true);lv_obj_move_background(_container);}};
        bool    showInLauncher(){return _showInLauncher;};
        char*   getLabel(){return _label;}
        void    updateLauncherList();
        void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback);
        void    lvUpdateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENMAIN_H */
