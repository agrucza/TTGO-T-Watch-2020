/**
    This is the settings app class
    @file AppSettings.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPSETTINGS_H
#define __APPSETTINGS_H

#include <Arduino.h>
#include "App.h"
#include "TouchMetrics.h"

class GUI;
class TFT_esPI;

class AppSettings : public App{
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
        AppSettings();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
};

#endif /*__APPSETTINGS_H */