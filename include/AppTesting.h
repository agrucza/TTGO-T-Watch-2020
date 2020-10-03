/**
    This is the testing app class
    @file AppTesting.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __APPTESTING_H
#define __APPTESTING_H

#include <Arduino.h>
#include "App.h"

#include "lvgl/src/lv_core/lv_obj.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;
typedef _lv_obj_t lv_obj_t;

class AppTesting : public App{
    public:
        AppTesting();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
};

#endif /*__APPTESTING_H */
