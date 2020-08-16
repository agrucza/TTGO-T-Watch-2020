#include "UIScreenSettings.h"
#include "UIModal.h"
#include "GUI.h"
#include "UIKeyboard.h"
#include "config.h"
#include "LilyGoWatch.h"
#include <string.h>
#include "esp_wifi.h"
#include <WiFi.h>

extern GUI *gui;

UIScreenSettings::UIScreenSettings():UIScreen()
{
    _label              = "Settings";
    _showInLauncher     = true;

    // Create a window
    _container          = lv_win_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    
    // title
    lv_win_set_title(_container, _label);

    // Add control button to the header
    _closeBtn       = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData   = new ScreenCallback(this, CALLBACK_SWITCH_SCREEN, SCREEN_MAIN);
    lv_obj_set_user_data(_closeBtn, _callbackData);
    lv_obj_set_event_cb(_closeBtn, GUI::screenEventCallback);

    // create a list
    lv_obj_t* list = lv_list_create(_container, NULL);
    lv_obj_add_style(list, LV_CONT_PART_MAIN, &GUI::borderlessStyle);
    lv_obj_set_pos(list,0,0);
    lv_obj_set_size(list, TFT_WIDTH, TFT_HEIGHT-lv_win_get_header_height(_container));
    lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 0);

    _callbackElement    = lv_list_add_btn(list, LV_SYMBOL_BELL, "Date & Time");
    _callbackData       = new ScreenCallback(this, CALLBACK_NONE);
    lv_obj_set_user_data(_callbackElement, _callbackData);
    lv_obj_set_event_cb(_callbackElement, GUI::screenEventCallback);
    _createDateTimeModal();

    _callbackElement    = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    _callbackData       = new ScreenCallback(this, CALLBACK_NONE);
    lv_obj_set_user_data(_callbackElement, _callbackData);
    lv_obj_set_event_cb(_callbackElement, GUI::screenEventCallback);
    _createWiFiModal();

    _callbackElement    = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    _callbackData       = new ScreenCallback(this, CALLBACK_NONE);
    lv_obj_set_user_data(_callbackElement, _callbackData);
    lv_obj_set_event_cb(_callbackElement, GUI::screenEventCallback);
    _createBluetoothModal();
}

void UIScreenSettings::_createDateTimeModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "Date & Time");

    lv_win_set_layout(modal->modalContent, LV_LAYOUT_COLUMN_LEFT);

    /*
    lv_obj_t* label   = lv_label_create(modal->modalContent, NULL);
    lv_label_set_text(label, "Timezone:");
    
    _ddTimezone = lv_dropdown_create(modal->modalContent, NULL);
    String sTimeZone = "";

    for(int8_t i = -14; i < 14; i++)
    {
        sTimeZone += "GMT";
        if(i<0)
        {
            sTimeZone += "-";
        } else if(i>0)
        {
            sTimeZone += "+";
        }
        sTimeZone += i;
    }
    
    lv_obj_set_width(_ddTimezone, lv_obj_get_width_fit(modal->modalContent)-32);
    lv_dropdown_set_options(_ddTimezone, "GMT\nGMT+1");
    */

    lv_obj_t* label   = lv_label_create(modal->modalContent, NULL);
    lv_label_set_text(label, "Time:");
    
    // time textarea
    _taTime = lv_textarea_create(modal->modalContent, NULL);
    lv_obj_set_user_data(_taTime, modal);
    lv_obj_set_event_cb(_taTime, GUI::modalEventCallback);
    lv_label_set_align(lv_textarea_get_label(_taTime), LV_LABEL_ALIGN_CENTER);
    lv_textarea_set_one_line(_taTime, true);
    lv_textarea_set_cursor_hidden(_taTime, true);
    lv_obj_set_width(_taTime, lv_obj_get_width_fit(modal->modalContent)-32);
    lv_textarea_set_accepted_chars(_taTime, "0123456789:");
    lv_textarea_set_max_length(_taTime, 15);

    label   = lv_label_create(modal->modalContent, NULL);
    lv_label_set_text(label, "Date:");

    _taDate = lv_textarea_create(modal->modalContent, NULL);
    lv_obj_set_user_data(_taDate, modal);
    lv_obj_set_event_cb(_taDate, GUI::modalEventCallback);
    lv_label_set_align(lv_textarea_get_label(_taDate), LV_LABEL_ALIGN_CENTER);
    lv_textarea_set_one_line(_taDate, true);
    lv_textarea_set_cursor_hidden(_taDate, true);
    lv_obj_set_width(_taDate, lv_obj_get_width_fit(modal->modalContent)-32);
    lv_textarea_set_accepted_chars(_taDate, "0123456789.-");
    lv_textarea_set_max_length(_taTime, 15);

    lv_page_scroll_ver(lv_win_get_content(modal->modalContent),lv_page_get_scrl_height(lv_win_get_content(modal->modalContent)));

    _updateDateTimeModal();
}

void UIScreenSettings::_createWiFiModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "WiFi", false);
    _wiFiBtn = lv_win_add_btn(modal->modalContent, LV_SYMBOL_WIFI);
    lv_obj_set_user_data(_wiFiBtn, modal);
    lv_obj_set_event_cb(_wiFiBtn, GUI::modalEventCallback);
    /*
     * wifi scan:
     * WiFi.disconnect();
     * WiFi.scanNetworks(true);
     */
    
}

void UIScreenSettings::_createBluetoothModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "Bluetooth");
    
}

void UIScreenSettings::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback)
{
    switch(event){
        case LV_EVENT_CLICKED:
            if(obj == _closeBtn)
            {
                _gui->showScreen(SCREEN_MAIN);
            }
            else if(obj == _wiFiBtn)
            {
                _switchWiFi();
            }
            else if(obj == _taTime)
            {
                // textarea clicked
                UIKeyboard::bindObj(this, _taTime);
                UIKeyboard::show();
            }
            else if(obj == _taDate)
            {
                // textarea clicked
                UIKeyboard::bindObj(this, _taDate);
                UIKeyboard::show();
            }
            else
            {
                UIModal::show(this, obj);
            }
        break;
        case LV_EVENT_VALUE_CHANGED:
            uint16_t    newdata[6];
            char        delimiter[] = ":-./";
            
            char*       token   = strtok(lv_label_get_text(lv_textarea_get_label(ext)),delimiter);
            uint8_t     count   = 0;
            
            while(token != NULL)
            {
                newdata[count++] = ((String)token).toInt();
                token = strtok(NULL, delimiter);
            }

            if(obj == _taTime)
            {
                token = strtok(lv_label_get_text(lv_textarea_get_label(_taDate)),delimiter);
                count = 3;
                while(token != NULL)
                {
                    newdata[count++] = ((String)token).toInt();
                    token = strtok(NULL, delimiter);
                }
                // newdata[0] = hour
                // newdata[1] = minute
                // newdata[2] = second
                // newdata[3] = day
                // newdata[4] = month
                // newdata[5] = year
                _gui->setRTC(newdata[5],newdata[4],newdata[3],newdata[0],newdata[1],newdata[2]);
            }
            else if(obj == _taDate)
            {
                token = strtok(lv_label_get_text(lv_textarea_get_label(_taTime)),delimiter);
                count = 3;
                while(token != NULL)
                {
                    newdata[count++] = ((String)token).toInt();
                    token = strtok(NULL, delimiter);
                }
                
                // newdata[0] = day
                // newdata[1] = month
                // newdata[2] = year
                // newdata[3] = hour
                // newdata[4] = minute
                // newdata[5] = second
                _gui->setRTC(newdata[2],newdata[1],newdata[0],newdata[3],newdata[4],newdata[5]);
            }
            break;
    }
}

void UIScreenSettings::_updateDateTimeModal()
{
    // update the time text area
    time_t now;
    struct tm  info;
    char buf[20];
    time(&now);
    localtime_r(&now, &info);
    strftime(buf, sizeof(buf), GUI::timeFormatHMS, &info);
    lv_textarea_set_text(_taTime, buf);

    // update the date text are
    strftime(buf, sizeof(buf), GUI::dateFormat, &info);
    lv_textarea_set_text(_taDate, buf);
}

void UIScreenSettings::_switchWiFi()
{
    if(WiFi.isConnected()){
        WiFi.mode(WIFI_OFF);
    }
    else
    {
        WiFi.mode(WIFI_STA);
        // connect to AP
        WiFi.begin("SSID","PASSWORD");
    }
}

void UIScreenSettings::lvUpdateTask(struct _lv_task_t* data)
{
    _updateDateTimeModal();
}