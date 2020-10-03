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

class App;

class UIKeyboard{
    static App*         app;
    static lv_obj_t*    modal;
    static lv_obj_t*    kb;
    static lv_obj_t*    ta;
    static lv_obj_t*    boundObj;
    static void         UIKeyboardInit();
    static void         eventCallback(lv_obj_t * obj, lv_event_t event);
    
    public:
        static void bindObj(App* app, lv_obj_t* obj);
        static void show();
        static void close();
};

#endif /* __UIKEYBOARD_H */
