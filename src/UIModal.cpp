#include "UIModal.h"
#include "UIKeyboard.h"

std::vector<UIModal*> UIModal::store;

UIModal::UIModal(UIScreen* screen, lv_obj_t* trigger, char* header, bool accept, bool close)
{
    showCloseBtn    = close;
    showAcceptBtn   = accept;
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

    if(showCloseBtn)
    {
        closeBtn    = lv_win_add_btn(modalContent, LV_SYMBOL_CLOSE);
        lv_obj_set_user_data(closeBtn, this);
        lv_obj_set_event_cb(closeBtn, GUI::modalEventCallback);
    }

    if(showAcceptBtn)
    {
        acceptBtn   = lv_win_add_btn(modalContent, LV_SYMBOL_OK);
        lv_obj_set_user_data(acceptBtn, this);
        lv_obj_set_event_cb(acceptBtn, GUI::modalEventCallback);
    }
    
    this->store.push_back(this);
}

void UIModal::show(UIScreen* screen, lv_obj_t* trigger)
{
    for(uint8_t i = 0; i < store.size(); i++)
    {
        UIModal* modal = store[i];
        if(modal->screen == screen)
        {
            if((trigger != nullptr && trigger == modal->trigger) || (modal->showOnScreenOpen))
            {
                modal->show();
            }
        }
        else
        {
            modal->close();
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
            close();
        }
        else if(obj == acceptBtn)
        {
            close();
        }
        else
        {
            screen->eventCallback(obj, event);
        }
    }
}
