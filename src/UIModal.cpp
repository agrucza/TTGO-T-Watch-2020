#include "UIModal.h"
#include "UIKeyboard.h"

std::vector<UIModal*> UIModal::store;

UIModal::UIModal(UIScreen* screen, lv_obj_t* trigger, char* header)
{
    this->screen    = screen;
    this->trigger   = trigger;
    showOnScreenOpen = false;

    modalContainer = lv_cont_create(lv_scr_act(), nullptr);

    lv_obj_set_hidden(modalContainer, true);
    lv_obj_move_background(modalContainer);

    lv_obj_set_size(modalContainer,TFT_WIDTH,TFT_HEIGHT);
    lv_cont_set_layout(modalContainer, LV_LAYOUT_CENTER);
    lv_obj_add_style(modalContainer, LV_OBJ_PART_MAIN, &GUI::modalStyle);

    modalContent = lv_win_create(modalContainer, NULL);
    lv_win_set_title(modalContent, header);

    closeBtn    = lv_win_add_btn(modalContent, LV_SYMBOL_CLOSE);
    lv_obj_set_user_data(closeBtn, this);
    lv_obj_set_event_cb(closeBtn, GUI::modalEventCallback);

    acceptBtn   = lv_win_add_btn(modalContent, LV_SYMBOL_OK);
    
    this->store.push_back(this);
}

void UIModal::show(UIScreen* screen, lv_obj_t* trigger)
{
    for(uint8_t i = 0; i < store.size(); i++)
    {
        UIModal* modal = store[i];
        if(modal->screen == screen && modal->trigger == trigger)
        {
            modal->show();
        }
        else
        {
            modal->hide();
        }
    }
}

void UIModal::hideAll()
{
    for(uint8_t i = 0; i < store.size(); i++)
    {
        store[i]->hide();
    }
}

void UIModal::show()
{
    showOnScreenOpen = true;
    lv_obj_set_hidden(modalContainer,false);
    lv_obj_move_foreground(modalContainer);
}

void UIModal::hide()
{
    lv_obj_set_hidden(modalContainer,true);
    lv_obj_move_background(modalContainer);
}

void UIModal::close()
{
    showOnScreenOpen = false;
    hide();
}

void UIModal::eventCallback(lv_obj_t* obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED)
    {
        if(obj == closeBtn)
        {
            hide();
        }
        else if(obj == acceptBtn)
        {
            // send store to screen including modal pointer?
            UIKeyboard::show();
        }
        else
        {
            // send action to screen including modal pointer?
        }
    }
}
