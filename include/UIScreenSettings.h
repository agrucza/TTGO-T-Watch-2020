/**
    This is the settings screen class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __UISCREENSETTINGS_H
#define __UISCREENSETTINGS_H

#include <Arduino.h>
#include "UIScreen.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class UIScreenSettings : public UIScreen{
    // date & time
    lv_obj_t*   _ddTimezone;
    lv_obj_t*   _taTime;
    lv_obj_t*   _taDate;
    void        _createDateTimeModal();

    // wifi
    lv_obj_t*   _wiFiBtn = nullptr;
    void        _createWiFiModal();
    void        _createBluetoothModal();
    void        _updateDateTimeModal();
    void        _switchWiFi();
    public:
        UIScreenSettings();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback = nullptr);
        void    lvUpdateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENSETTINGS_H */