#include "UIScreen.h"


void UIScreen::show(){
    if(_container != nullptr)
    {
        lv_obj_set_hidden(_container,false);
        lv_obj_move_foreground(_container);
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
