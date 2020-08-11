/**
    This is the testing screen class
    @file UIScreenTesting.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UISCREENTESTING_H
#define __UISCREENTESTING_H

#include <Arduino.h>
#include "UIScreen.h"

#include "lvgl/src/lv_core/lv_obj.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;
typedef _lv_obj_t lv_obj_t;

class UIScreenTesting : public UIScreen{
    public:
        UIScreenTesting();
        void    eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback);
        void    lvUpdateTask(struct _lv_task_t* data);
};

#endif /*__UISCREENTESTING_H */
