#include "UIScreen.h"

void UIScreen::eventCallback(lv_obj_t *obj, lv_event_t event, ScreenCallback* callback)
{
    eventCallback(obj,  NULL, event, callback);
};

void UIScreen::show(){
    if(_container != nullptr)
    {
        lv_obj_set_hidden(_container,false);
        lv_obj_move_foreground(_container);
        UIModal::show(this);
    }
};

void UIScreen::hide()
{
    if(_container != nullptr)
    {
        UIModal::hideAll();
        lv_obj_set_hidden(_container,true);
        lv_obj_move_background(_container);
    }
}
