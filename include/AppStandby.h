/**
    This is the standby app class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/26/2020
*/

#ifndef __APPSTANDBY_H
#define __APPSTANDBY_H

#include <Arduino.h>
<<<<<<< HEAD:include/UIScreenStandby.h
#include "UIScreen.h"

#include "lvgl/src/lv_core/lv_obj.h"
=======

#include "App.h"
#include "TouchMetrics.h"
>>>>>>> no_lvgl:include/AppStandby.h

class GUI;
class TFT_esPI;

<<<<<<< HEAD:include/UIScreenStandby.h
enum screens_t : uint8_t;
typedef _lv_obj_t lv_obj_t;

class UIScreenStandby : public UIScreen{
    lv_obj_t*           _timeLabel;
    lv_style_t          _timeLabelStyle;
    
    lv_obj_t*           _dateLabel;
    lv_style_t          _dateLabelStyle;

    lv_obj_t*           _iconContainer;
    lv_style_t          _iconContainerStyle;

    lv_obj_t*           _touchNotifyLabel;

    lv_obj_t*           _touchLabel;
    bool                _touched;

    public:
        UIScreenStandby();
        void    eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback = nullptr);
        void    updateTask(struct _lv_task_t* data);
        void    updateIcons();
};

#endif /*__UISCREENSTANDBY_H */
=======
class AppStandby: public App{
    time_t      _currentTime;
    struct tm   _timeInfo;
    uint8_t     _iconSizeX;
    uint8_t     _iconSizeY;
    uint16_t    _iconColor;
    uint8_t     _lastMinute;
    uint8_t     _lastMonth;

    void _fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
    public:
        AppStandby();
        void    draw(bool init = false, bool task = false);
        void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    elementEventHandler(ui_event_data_t* eventData){};
        void    backgroundTaskHandler(){};
};

#endif /*__APPSTANDBY_H */
>>>>>>> no_lvgl:include/AppStandby.h
