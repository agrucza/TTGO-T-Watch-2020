/**
    This is the modal class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 8/12/2020
*/

#ifndef __UIMODAL_H
#define __UIMODAL_H

#include <Arduino.h>
#include "UIScreen.h"

class UIModal{
    static std::vector<UIModal*>    store;
    UIScreen*   screen;
    lv_obj_t*   trigger;
    lv_obj_t*   modalContainer;
    lv_obj_t*   modalContent;
    uint8_t     modalID;
    public:
        UIModal(UIScreen* screen, lv_obj_t* trigger, char* head);
        static void show(UIScreen* screen, lv_obj_t* trigger);
        void show();
        void hide();
};

#endif /*__UIMODAL_H */
