#include "AppSettings.h"
#include "UIModal.h"
#include "GUI.h"
#include "UIKeyboard.h"
#include "config.h"
#include "LilyGoWatch.h"
#include <string.h>
#include "esp_wifi.h"
#include <WiFi.h>

extern GUI *gui;

AppSettings::AppSettings():App("Settings")
{
    // Create a window
    _container          = lv_win_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    
    // title
    lv_win_set_title(_container, _label.c_str());

    // Add control button to the header
    _closeBtn       = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData   = new AppCallback(_label, CALLBACK_SWITCH_APP, "Launcher");
    lv_obj_set_user_data(_closeBtn, _callbackData);
    lv_obj_set_event_cb(_closeBtn, GUI::appEventCallback);

    // create a list
    lv_obj_t* list = lv_list_create(_container, NULL);
    lv_obj_add_style(list, LV_CONT_PART_MAIN, &GUI::styleBorderless);
    lv_obj_set_pos(list,0,0);
    lv_obj_set_size(list, TFT_WIDTH, TFT_HEIGHT-lv_win_get_header_height(_container));
    lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 0);

    _callbackElement    = lv_list_add_btn(list, LV_SYMBOL_BELL, "Date & Time");
    _callbackData       = new AppCallback(_label, CALLBACK_NONE);
    lv_obj_set_user_data(_callbackElement, _callbackData);
    lv_obj_set_event_cb(_callbackElement, GUI::appEventCallback);
    _createDateTimeModal();

    _callbackWifi       = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    _callbackData       = new AppCallback(_label, CALLBACK_NONE);
    lv_obj_set_user_data(_callbackWifi, _callbackData);
    lv_obj_set_event_cb(_callbackWifi, GUI::appEventCallback);
    _createWiFiModal();

    _callbackElement    = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    _callbackData       = new AppCallback(_label, CALLBACK_NONE);
    lv_obj_set_user_data(_callbackElement, _callbackData);
    lv_obj_set_event_cb(_callbackElement, GUI::appEventCallback);
    _createBluetoothModal();
}

void AppSettings::_createDateTimeModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "Date & Time");

    lv_win_set_layout(modal->modalContent, LV_LAYOUT_COLUMN_MID);

    // timezone
    lv_obj_t* _dtTzCont    = lv_cont_create(modal->modalContent, NULL);
    lv_obj_add_style(_dtTzCont, LV_OBJ_PART_MAIN, &GUI::styleBorderless);
    lv_obj_set_width(_dtTzCont, lv_win_get_width(modal->modalContent));
    lv_cont_set_layout(_dtTzCont, LV_LAYOUT_OFF);

    _dtTzUp = lv_btn_create(_dtTzCont, NULL);
    lv_obj_align(_dtTzUp, NULL, LV_ALIGN_IN_LEFT_MID, 10, 5);
    lv_obj_set_size(_dtTzUp, 30, 30);
    lv_obj_set_user_data(_dtTzUp, modal);
    lv_obj_set_event_cb(_dtTzUp, GUI::modalEventCallback);
    lv_obj_set_style_local_value_str(_dtTzUp, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_UP);

    _dtTzLabel   = lv_label_create(_dtTzCont, NULL);
    lv_label_set_text(_dtTzLabel, "UTC-0");
    lv_obj_align(_dtTzLabel, NULL, LV_ALIGN_CENTER, 0, 0);

    _dtTzDown = lv_btn_create(_dtTzCont, _dtTzUp);
    lv_obj_align(_dtTzDown, NULL, LV_ALIGN_IN_RIGHT_MID, -10, 0);
    lv_obj_set_user_data(_dtTzDown, modal);
    lv_obj_set_event_cb(_dtTzDown, GUI::modalEventCallback);
    lv_obj_set_style_local_value_str(_dtTzDown, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_DOWN);

    // dst
    _dtDst = lv_checkbox_create(modal->modalContent, NULL);
    lv_obj_set_user_data(_dtDst, modal);
    lv_obj_set_event_cb(_dtDst, GUI::modalEventCallback);
    lv_checkbox_set_text(_dtDst, "summer time");
    //lv_obj_align(dtDst, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_local_outline_width(_dtDst, LV_CHECKBOX_PART_BG, LV_STATE_DEFAULT, 0);
    lv_checkbox_set_checked(_dtDst, _dtDstValue);

    // get NTP time button    
    _dtBtnNTP = lv_btn_create(modal->modalContent, NULL);
    lv_obj_set_user_data(_dtBtnNTP, modal);
    lv_obj_set_event_cb(_dtBtnNTP, GUI::modalEventCallback);
    lv_obj_set_width(_dtBtnNTP, lv_win_get_width(modal->modalContent));
    lv_btn_set_state(_dtBtnNTP, LV_STATE_DISABLED);
    lv_obj_set_click(_dtBtnNTP, false);
    lv_obj_set_style_local_value_str(_dtBtnNTP, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Get time (NTP)");
}

void AppSettings::_getDateTimeNTP()
{
    const long  gmtOffsetSec       = (_dtTzValue * 3600);
    const int   daylightOffsetSec  = (_dtDstValue?3600:0);
    configTime(gmtOffsetSec, daylightOffsetSec, "pool.ntp.org");
    
    char buf[50];
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo))
    {
        sprintf(buf,"Failed to obtain time");
    }
    else
    {
        strftime(buf, sizeof(buf), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    }
    _gui->getTTGO()->tft->drawString(buf,0,0);
}

void AppSettings::_createWiFiModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "WiFi", false);
    
    _wifiEnableValue = (WiFi.getMode() == WIFI_OFF?false:true);

    lv_win_set_layout(modal->modalContent, LV_LAYOUT_COLUMN_MID);

    lv_obj_t* _wifiEnableCont = lv_cont_create(modal->modalContent, NULL);
    lv_obj_add_style(_wifiEnableCont, LV_OBJ_PART_MAIN, &GUI::styleBorderless);
    lv_obj_set_width(_wifiEnableCont, lv_win_get_width(modal->modalContent));
    lv_cont_set_layout(_wifiEnableCont, LV_LAYOUT_OFF);

    lv_obj_t* _wifiEnableLabel = lv_label_create(_wifiEnableCont, NULL);
    lv_obj_align(_wifiEnableLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);
    lv_label_set_text(_wifiEnableLabel, "enabled");

    _wifiEnableSwitch = lv_switch_create(_wifiEnableCont, NULL);
    lv_obj_align(_wifiEnableSwitch, NULL, LV_ALIGN_IN_RIGHT_MID, -10, 0);
    lv_obj_set_user_data(_wifiEnableSwitch, modal);
    lv_obj_set_event_cb(_wifiEnableSwitch, GUI::modalEventCallback);

    _wifiScanCont = lv_cont_create(modal->modalContent, NULL);
    lv_obj_add_style(_wifiScanCont, LV_OBJ_PART_MAIN, &GUI::styleBorderless);
    lv_obj_set_width(_wifiScanCont, lv_win_get_width(modal->modalContent));
    lv_cont_set_layout(_wifiScanCont, LV_LAYOUT_PRETTY_MID);

    lv_obj_t* _wifiScanLabel = lv_label_create(_wifiScanCont, NULL);
    lv_obj_align(_wifiScanLabel, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(_wifiScanLabel, LV_SYMBOL_REFRESH " Scanning");
    //lv_obj_set_hidden(_wifiScanCont, true);

    // wifi APs list
    _wifiAPList = lv_list_create(modal->modalContent, NULL);
    //lv_obj_set_width(_wifiAPList, lv_win_get_width(modal->modalContent));
    lv_obj_set_size(_wifiAPList, 188, 84);
    lv_obj_set_hidden(_wifiAPList, true);
    
    if(_wifiEnableValue)
    {
        lv_switch_on(_wifiEnableSwitch, LV_ANIM_OFF);
        //_scanWiFi();
    }
    else
    {
        lv_switch_off(_wifiEnableSwitch, LV_ANIM_OFF);
    }

    /*
     * wifi scan:
     * WiFi.disconnect();
     * WiFi.scanNetworks(true);
     */
}

void AppSettings::_createBluetoothModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "Bluetooth");
}

void AppSettings::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback)
{
    switch(event){
        case LV_EVENT_CLICKED:
            if(obj == _closeBtn)
            {
                Serial.println("Start Launcher");
                _gui->showApp("Launcher");
            }
            else if(obj == _dtTzUp)
            {
                // timezone up clicked
                _dtTzValue += 1;
                if(_dtTzValue > 14)
                {
                    _dtTzValue = -14;
                }
            }
            else if(obj == _dtTzDown)
            {
                // timezone down clicked
                _dtTzValue -= 1;
                if(_dtTzValue < -14)
                {
                    _dtTzValue = 14;
                }
            }
            else if(obj == _dtDst)
            {
                _dtDstValue = false;
                if(lv_checkbox_is_checked(obj))
                {
                    _dtDstValue = true;
                }
            }
            else if(obj == _dtBtnNTP)
            {
                // button get ntp time clicked
                _getDateTimeNTP();
            }
            else if(obj == _wifiEnableSwitch)
            {
                _switchWiFi();
            }
            else
            {
                UIModal::show(this, obj);
                if(obj == _callbackWifi && _wifiEnableValue)
                {
                    //_scanWiFi();
                }
            }
        break;
        /*
        case LV_EVENT_VALUE_CHANGED:
            if(obj == _wifiEnableSwitch)
            {
                _switchWiFi();
            }
            break;
        */
    }
}

void AppSettings::_updateDateTimeModal()
{
    char buf[7];
    sprintf(buf,"UTC%+i", _dtTzValue);
    lv_label_set_text(_dtTzLabel, buf);

    if(WiFi.isConnected())
    {
        lv_btn_set_state(_dtBtnNTP, LV_STATE_DEFAULT);
        lv_obj_set_click(_dtBtnNTP, true);
    }
    else
    {
        lv_btn_set_state(_dtBtnNTP, LV_STATE_DISABLED);
        lv_obj_set_click(_dtBtnNTP, false);
    }
}

void AppSettings::_switchWiFi()
{
    if(WiFi.getMode() == WIFI_STA){
        WiFi.mode(WIFI_OFF);
        _wifiEnableValue = false;
        lv_obj_set_hidden(_wifiAPList, true);
    }
    else
    {
        //lv_switch_on(_wifiEnableSwitch, LV_ANIM_ON);
        //lv_obj_set_hidden(_wifiScanCont, false);
        
        WiFi.mode(WIFI_STA);
        _scanWiFi();
        _wifiEnableValue = true;
    }
}

void AppSettings::_scanWiFi()
{
        // scan for APs
        uint8_t apNum= WiFi.scanNetworks();

        // clear APs list
        lv_list_clean(_wifiAPList);

        // add ssids to list
        _gui->wifiSSIDs.clear();
        for (int i = 0; i < apNum; ++i) {
            _gui->wifiSSIDs.push_back(WiFi.SSID(i));
            lv_obj_t* listBtn = lv_list_add_btn(_wifiAPList, LV_SYMBOL_WIFI, _gui->wifiSSIDs[i].c_str());
            lv_obj_set_style_local_text_font(listBtn, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_12);
            //lv_obj_set_event_cb(listBtn, event_handler);
        }
        
        // show AP list
        //lv_obj_set_hidden(_wifiScanCont, true);
        lv_obj_set_hidden(_wifiAPList, false);
}

void AppSettings::updateTask(struct _lv_task_t* data)
{
    _updateDateTimeModal();
    _wifiEnableValue = (WiFi.getMode() == WIFI_OFF?false:true);
}
