#include "UIScreenTesting.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI* gui;

UIScreenTesting::UIScreenTesting():UIScreen()
{
    _label              = "Testing";
    _showInLauncher     = true;
    _callbackElement    = 0;
    
    // Create a window*/
    _container = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(_container, _label);

    // Add control button to the header
    lv_obj_t* element = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_SWITCH_SCREEN, SCREEN_MAIN);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);
    
    element = lv_win_add_btn(_container, LV_SYMBOL_SETTINGS);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_SWITCH_SCREEN, SCREEN_MAIN);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element, GUI::screenEventCallback);

    // Add some dummy content
    lv_obj_t * txt = lv_label_create(_container, NULL);
    lv_label_set_text(txt, "This is the content of the window\n\n"
                           "You can add control buttons to\n"
                           "the window header\n\n"
                           "The content area becomes\n"
                           "automatically scrollable is it's \n"
                           "large enough.\n\n"
                           " You can scroll the content\n"
                           "See the scroll bar on the right!");
}

void UIScreenTesting::eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback)
{
    switch(callback->getCbElement()){
        case 0:
            // close button
            _gui->showScreen(SCREEN_MAIN);
        case 1:
            // settings button
            break;
    }
    
}

void UIScreenTesting::lvUpdateTask(struct _lv_task_t* data)
{

}
