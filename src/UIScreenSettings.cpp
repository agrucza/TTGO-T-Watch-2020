#include "UIScreenSettings.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "TFT_eSPI/Fonts/Custom/IconsFontsSup24pt7b.h"

extern GUI *gui;

UIScreenSettings::UIScreenSettings():UIScreen()
{
    _label              = "Settings";
    _showInLauncher     = true;
    _callbackElement    = 0;

    // Add buttons
    lv_obj_t* element;

    // Create a window*/
    _container          = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    
    // title
    lv_win_set_title(_container, _label);

    // Add control button to the header
    element = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_SWITCH_SCREEN, SCREEN_MAIN);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);

    // create a list
    lv_obj_t* list = lv_list_create(_container, NULL);
    lv_obj_add_style(list, LV_CONT_PART_MAIN, &GUI::borderlessStyle);
    lv_obj_set_pos(list,0,0);
    lv_obj_set_width(list, TFT_WIDTH);
    lv_obj_set_height(list, TFT_HEIGHT-lv_win_get_header_height(_container));
    //lv_obj_set_size(list,220,200);
    lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 0);

    element = lv_list_add_btn(list, LV_SYMBOL_BELL, "Time & Date");
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_NONE);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);

    element = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_NONE);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);

    element = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_NONE);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);
}

void UIScreenSettings::eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback)
{
    switch(callback->getCbElement()){
        case 0:
            // close button
            _gui->showScreen(SCREEN_MAIN);
            break;
        case 1:
            // first list item (time & date)
            break;
    }
}

void UIScreenSettings::lvUpdateTask(struct _lv_task_t* data)
{

}
