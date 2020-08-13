/**
    This is the keyboard class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 8/13/2020
*/

#ifndef __UIKEYBOARD_H
#define __UIKEYBOARD_H

#include <Arduino.h>
#include "config.h"
#include "LilyGoWatch.h"

class UIKeyboard{
    static lv_obj_t*    modal;
    static lv_obj_t*    kb;
    static lv_obj_t*    ta;
    static lv_obj_t*    boundObj;
    
    public:
        static void bindObj(lv_obj_t* obj);
        static void show();
        static void close();
};

#endif /* __UIKEYBOARD_H */
