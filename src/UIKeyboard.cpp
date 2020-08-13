#include "UIKeyboard.h"
#include "UIScreen.h"

lv_obj_t*   UIKeyboard::modal      = nullptr;
lv_obj_t*   UIKeyboard::kb         = nullptr;
lv_obj_t*   UIKeyboard::ta         = nullptr;
lv_obj_t*   UIKeyboard::boundObj   = nullptr;

void UIKeyboard::bindObj(lv_obj_t* obj)
{
    boundObj = obj;
}

void UIKeyboard::show()
{
    if(modal == nullptr)
    {
        modal = lv_obj_create(lv_scr_act(), NULL);
    }
    
    if(kb == nullptr)
    {
        kb = lv_keyboard_create(modal, NULL);
        lv_keyboard_set_cursor_manage(kb, true);
    }

    if(ta == nullptr)
    {
        ta = lv_textarea_create(lv_scr_act(), NULL);
        lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 16);
        lv_coord_t max_h = LV_VER_RES / 2 - LV_DPI / 8;
        if(lv_obj_get_height(ta) > max_h) lv_obj_set_height(ta, max_h);
        lv_keyboard_set_textarea(kb, ta);
    }

    lv_textarea_set_text(ta, "");
    lv_obj_set_hidden(modal,false);
    lv_obj_move_foreground(modal);
}

void UIKeyboard::close()
{
    lv_textarea_set_text(ta, "");
    lv_obj_set_hidden(modal,true);
    lv_obj_move_background(modal);
}