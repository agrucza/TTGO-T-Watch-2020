#include "UIModal.h"

std::vector<UIModal*> UIModal::store;

UIModal::UIModal(UIScreen* screen, lv_obj_t* trigger, char* header)
{
    this->screen = screen;

    modalContainer = lv_cont_create(lv_scr_act(), nullptr);

    lv_obj_set_hidden(modalContainer, true);
    lv_obj_move_background(modalContainer);

    lv_obj_set_size(modalContainer,TFT_WIDTH,TFT_HEIGHT);
    lv_cont_set_layout(modalContainer, LV_LAYOUT_CENTER);
    lv_obj_add_style(modalContainer, LV_OBJ_PART_MAIN, &GUI::modalStyle);

    modalContent = lv_cont_create(modalContainer, NULL);
    lv_cont_set_layout(modalContent, LV_LAYOUT_CENTER);
    
    // modal content
    lv_obj_t* element = lv_label_create(modalContent, NULL);
    lv_label_set_text(element, header);
    
    //this->screen->modals.push_back(modalContainer);
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

void UIModal::show()
{
    lv_obj_set_hidden(modalContainer,false);
    lv_obj_move_foreground(modalContainer);
}

void UIModal::hide()
{
    lv_obj_set_hidden(modalContainer,true);
    lv_obj_move_background(modalContainer);
}