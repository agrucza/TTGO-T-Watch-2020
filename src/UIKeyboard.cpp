#include "UIKeyboard.h"
#include "App.h"

App*        UIKeyboard::app         = nullptr;
lv_obj_t*   UIKeyboard::modal       = nullptr;
lv_obj_t*   UIKeyboard::kb          = nullptr;
lv_obj_t*   UIKeyboard::ta          = nullptr;
lv_obj_t*   UIKeyboard::boundObj    = nullptr;

void UIKeyboard::bindObj(App* scr, lv_obj_t* obj)
{
    UIKeyboardInit();
    app         = scr;
    boundObj    = obj;
    lv_label_set_align(lv_textarea_get_label(ta), lv_label_get_align(lv_textarea_get_label(obj)));
    lv_textarea_set_one_line(ta, lv_textarea_get_one_line(obj));
    lv_textarea_set_accepted_chars(ta, lv_textarea_get_accepted_chars(obj));
    lv_textarea_set_max_length(ta, lv_textarea_get_max_length(obj));
    lv_textarea_set_text(ta,lv_textarea_get_text(obj));
}

void UIKeyboard::UIKeyboardInit()
{
    if(modal == nullptr)
    {
        modal = lv_cont_create(lv_scr_act(), NULL);
        lv_obj_set_size(modal, TFT_WIDTH, TFT_HEIGHT);
        lv_obj_add_style(modal, LV_OBJ_PART_MAIN, &GUI::modalStyle);
    }
    
    if(kb == nullptr)
    {
        kb = lv_keyboard_create(modal, NULL);
        lv_obj_set_event_cb(kb, eventCallback);
        lv_keyboard_set_cursor_manage(kb, true);
        lv_obj_set_width(kb, TFT_WIDTH);
        lv_obj_set_x(kb, 0);
    }

    if(ta == nullptr)
    {
        ta = lv_textarea_create(modal, NULL);
        lv_obj_set_width(ta, TFT_WIDTH);
        lv_keyboard_set_textarea(kb, ta);
    }
}

void UIKeyboard::show()
{
    UIKeyboardInit();
    lv_obj_set_hidden(modal,false);
    lv_obj_move_foreground(modal);
    lv_obj_set_hidden(kb,false);
}

void UIKeyboard::close()
{
    lv_textarea_set_text(ta, "");
    lv_obj_set_hidden(modal,true);
    lv_obj_move_background(modal);
}

void UIKeyboard::eventCallback(lv_obj_t * obj, lv_event_t event)
{
    lv_keyboard_def_event_cb(kb, event);
    switch(event)
    {
        case LV_EVENT_APPLY:
            // when apply we need to notify the screen of the changes
            app->eventCallback(boundObj, ta, LV_EVENT_VALUE_CHANGED);
            close();
            break;
        case LV_EVENT_CANCEL:
            close();
            break;
        default:
            break;
    }
}