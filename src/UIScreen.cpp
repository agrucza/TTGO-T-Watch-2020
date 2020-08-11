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
        if(_activeModal > 0)
        {
            modalVisibility(_activeModal,false);
        };
        lv_obj_set_hidden(_container,true);
        lv_obj_move_background(_container);
    }
};

void UIScreen::modalVisibility(uint8_t element, bool visible)
{
    if(element > 0 && element <= _modals.size())
    {
        lv_obj_t* modal = _modals[element-1];
        if(modal != nullptr)
        {
            if(visible)
            {
                _activeModal = element;
                lv_obj_set_hidden(modal,false);
                lv_obj_move_foreground(modal);
            }
            else
            {
                _activeModal = 0;
                lv_obj_set_hidden(modal,true);
                lv_obj_move_background(modal);
            }
        }
    }
}