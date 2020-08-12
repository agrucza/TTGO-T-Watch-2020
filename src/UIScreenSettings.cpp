#include "UIScreenSettings.h"
#include "UIModal.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "TFT_eSPI/Fonts/Custom/IconsFontsSup24pt7b.h"

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
    
}

void UIScreenSettings::_createWiFiModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "WiFi");
    
}

void UIScreenSettings::_createBluetoothModal()
{
    UIModal* modal      = new UIModal(this, _callbackElement, "Bluetooth");
    
}

void UIScreenSettings::eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback)
{
    if(event == LV_EVENT_CLICKED)
    {
        if(obj == _closeBtn)
        {
            _gui->showScreen(SCREEN_MAIN);
        }
        else
        {
            UIModal::show(this, obj);
        }
    }
}

void UIScreenSettings::lvUpdateTask(struct _lv_task_t* data)
{
    
}