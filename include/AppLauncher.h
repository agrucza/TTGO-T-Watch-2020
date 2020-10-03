/**
    This is the launcher app class
    @file AppLauncher.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENMAIN_H
#define __UISCREENMAIN_H

#include <Arduino.h>
#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;

class AppLauncher : public App{
    std::vector<icon_t> _launcherIcons;
    std::vector<AppCallback*> _callbackData;

    public:
        AppLauncher();
        void    updateLauncherList();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENMAIN_H */
