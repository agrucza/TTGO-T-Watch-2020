#include "AppTesting.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI* gui;

AppTesting::AppTesting():App("Testing")
{
    // Create a window*/
    _container = lv_win_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_win_set_title(_container, _label.c_str());

    // Add control button to the header
    _closeBtn       = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData   = new AppCallback(_label, CALLBACK_SWITCH_APP, "Launcher");
    lv_obj_set_user_data(_closeBtn, _callbackData);
    lv_obj_set_event_cb(_closeBtn, GUI::appEventCallback);
    
    _settingsBtn    = lv_win_add_btn(_container, LV_SYMBOL_SETTINGS);
    _callbackData   = new AppCallback(_label, CALLBACK_SWITCH_APP, "Launcher");
    lv_obj_set_user_data(_settingsBtn, _callbackData);
    lv_obj_set_event_cb(_settingsBtn, GUI::appEventCallback);

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

void AppTesting::_generateLauncherIcon()
{
    lv_obj_t* label = lv_label_create(_launcherIcon, NULL);
    lv_label_set_text(label, _label.c_str());
}

void AppTesting::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback)
{
    if(event == LV_EVENT_CLICKED)
    {
        if(obj == _closeBtn)
        {
            _gui->showApp("Launcher");
        }
        else if(obj == _settingsBtn)
        {

        }
    }
}

void AppTesting::updateTask(struct _lv_task_t* data)
{

}
