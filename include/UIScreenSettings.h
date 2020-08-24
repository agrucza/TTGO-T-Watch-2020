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
    lv_obj_t*   _dtTzUp             = nullptr;
    lv_obj_t*   _dtTzLabel          = nullptr;
    lv_obj_t*   _dtTzDown           = nullptr;
    int8_t      _dtTzValue = 1;
    
    lv_obj_t*   _dtDst              = nullptr;
    bool        _dtDstValue         = true;
    
    lv_obj_t*   _dtBtnNTP           = nullptr;;

    void        _createDateTimeModal();
    void        _updateDateTimeModal();
    void        _getDateTimeNTP();

    // wifi
    lv_obj_t*   _callbackWifi       = nullptr;
    bool        _wifiEnableValue    = false;
    lv_obj_t*   _wifiEnableSwitch   = nullptr;
    lv_obj_t*   _wifiScanCont       = nullptr;
    lv_obj_t*   _wifiAPList         = nullptr;
    void        _createWiFiModal();
    void        _switchWiFi();
    void        _scanWiFi();

    // bluetooth
    void        _createBluetoothModal();

    public:
        UIScreenSettings();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENSETTINGS_H */