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
    
    // Create a window*/
    _container = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(_container, _label);

    // Add control button to the header
    _closeBtn = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    
    _callbackData = new ScreenCallback(this,CALLBACK_SWITCH_SCREEN,SCREEN_MAIN);

    lv_obj_set_user_data(_closeBtn, _callbackData);
    lv_obj_set_event_cb(_closeBtn,GUI::screenEventCallback);
    
    lv_win_add_btn(_container, LV_SYMBOL_SETTINGS);

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

void UIScreenSettings::eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback)
{
    if(obj == _closeBtn){
        // close the screen
        _gui->showScreen(SCREEN_MAIN);
    }
}

void UIScreenSettings::lvUpdateTask(struct _lv_task_t* data)
{

}
