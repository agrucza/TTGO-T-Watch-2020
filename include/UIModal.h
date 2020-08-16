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
    bool        showAcceptBtn       = true;
    bool        showCloseBtn        = true;
    bool        showOnScreenOpen;
    UIScreen*   screen;
    lv_obj_t*   trigger;
    lv_obj_t*   modalContainer;
    ScreenCallback* _callbackData;
    lv_obj_t*   closeBtn            = nullptr;
    lv_obj_t*   acceptBtn           = nullptr;

    public:
        UIModal(UIScreen* screen, lv_obj_t* trigger, char* head, bool accept = true, bool close = true);
        lv_obj_t*   modalContent;
        static void show(UIScreen* screen, lv_obj_t* trigger = nullptr);
        static void hideAll();
        void        show();
        void        hide();
        void        close();
        void        eventCallback(lv_obj_t* obj, lv_event_t event);
};

#endif /*__UIMODAL_H */
