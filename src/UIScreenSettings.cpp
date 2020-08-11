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
    _activeModal        = 0;

    // Create a window
    _container          = lv_win_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    
    // title
    lv_win_set_title(_container, _label);

    // Add control button to the header
    lv_obj_t* element = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_SWITCH_SCREEN, SCREEN_MAIN);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);

    // create a list
    lv_obj_t* list = lv_list_create(_container, NULL);
    lv_obj_add_style(list, LV_CONT_PART_MAIN, &GUI::borderlessStyle);
    lv_obj_set_pos(list,0,0);
    lv_obj_set_size(list, TFT_WIDTH, TFT_HEIGHT-lv_win_get_header_height(_container));
    lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 0);

    element = lv_list_add_btn(list, LV_SYMBOL_BELL, "Date & Time");
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

    lv_obj_t *modalContainer = lv_cont_create(lv_scr_act(), nullptr);
    lv_obj_set_size(modalContainer,TFT_WIDTH,TFT_HEIGHT);
    lv_cont_set_layout(modalContainer, LV_LAYOUT_CENTER);
    lv_obj_add_style(modalContainer, LV_OBJ_PART_MAIN, &GUI::modalStyle);

    lv_obj_t* modalContent = lv_cont_create(modalContainer, NULL);
    lv_cont_set_layout(modalContent, LV_LAYOUT_CENTER);
    
    // modal content
    element = lv_label_create(modalContent, NULL);
    lv_label_set_text(element, "Date & Time");
    
    
    _modals.push_back(modalContainer);
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
            modalVisibility(1,true);
            break;
    }
}

void UIScreenSettings::lvUpdateTask(struct _lv_task_t* data)
{

}