#include "config.h"
#include "LilyGoWatch.h"

<<<<<<< HEAD:src/UIScreenStandby.cpp
extern GUI* gui;

UIScreenStandby::UIScreenStandby():UIScreen()
{
    _label              = "Standby";
    _showInLauncher     = false;

    _timeLabel          = nullptr;
    _dateLabel          = nullptr;
    
    _touched            = false;

    // Create a container
    _container = lv_cont_create(lv_scr_act(), NULL);
=======
#include "AppStandby.h"

#include "GUI.h"

#define DEG2RAD 0.0174532925

AppStandby::AppStandby():App("Standby", false)
{
    _acceptsGlobalTouch = false;
    _lastMinute         = 0;
    _lastMonth          = 0;
    _gui->setStandbyApp(this);
}

void AppStandby::draw(bool init, bool task)
{
    uint16_t    margin      = 40;
    uint16_t    labelTop    = margin;
    char        label[20];
>>>>>>> no_lvgl:src/AppStandby.cpp

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    _callbackData = new ScreenCallback(this, CALLBACK_NONE);

<<<<<<< HEAD:src/UIScreenStandby.cpp
    lv_obj_set_user_data(_container,_callbackData);
    lv_obj_set_event_cb(_container,GUI::screenEventCallback);
    
    lv_obj_add_style(_container, LV_CONT_PART_MAIN, &GUI::borderlessStyle);

    lv_obj_set_auto_realign(_container, true);
    lv_obj_align_origo(_container, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_layout(_container, LV_LAYOUT_COLUMN_MID);
=======
    if(!task)
    {
        _tft->fillScreen(_bgColor);
    }
    
    // time label
    _tft->setFreeFont(&FreeSansBold24pt7b);
    _tft->setTextColor(_textColor,_bgColor);
    strftime(label, sizeof(label), "%H : %M", &_timeInfo);
    if(init || (_lastMinute != _timeInfo.tm_min))
    {
        _tft->fillRect(0,labelTop,TFT_WIDTH, _tft->fontHeight(), _bgColor);
        _lastMinute = _timeInfo.tm_min;
        _tft->drawString(label, TFT_WIDTH/2, labelTop + _tft->fontHeight()/2);
    }
    labelTop += _tft->fontHeight();
>>>>>>> no_lvgl:src/AppStandby.cpp

    lv_obj_set_size(_container, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(_container, NULL, LV_ALIGN_CENTER, 0, 0);
    
    // time label
    lv_style_init(&_timeLabelStyle);
    lv_style_set_text_font(&_timeLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_48);
    _timeLabel = lv_label_create(_container, NULL);
    lv_obj_add_style(_timeLabel, LV_LABEL_PART_MAIN, &_timeLabelStyle);
    GUI::updateTimeLabel(_timeLabel, GUI::timeFormatHM);
    
    // date label
<<<<<<< HEAD:src/UIScreenStandby.cpp
    _dateLabel = lv_label_create(_container, NULL);
    GUI::updateTimeLabel(_dateLabel, GUI::dateFormatLong);

    // create a container with some icons
    lv_style_copy(&_iconContainerStyle, &GUI::borderlessStyle);
    lv_style_set_bg_color(&_iconContainerStyle, LV_CONT_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_pad_inner(&_iconContainerStyle, LV_CONT_PART_MAIN, 2);
    lv_style_set_pad_top(&_iconContainerStyle, LV_CONT_PART_MAIN, 2);
    lv_style_set_pad_left(&_iconContainerStyle, LV_CONT_PART_MAIN, 4);
    lv_style_set_pad_bottom(&_iconContainerStyle, LV_CONT_PART_MAIN, 2);
    lv_style_set_pad_right(&_iconContainerStyle, LV_CONT_PART_MAIN, 4);

    _iconContainer = lv_cont_create(_container, NULL);
    
    lv_obj_add_style(_iconContainer, LV_CONT_PART_MAIN, &_iconContainerStyle);

    lv_obj_set_auto_realign(_iconContainer, true);
    lv_obj_align(_iconContainer, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_layout(_iconContainer, LV_LAYOUT_PRETTY_MID);
    lv_cont_set_fit(_iconContainer, LV_FIT_TIGHT);
    lv_obj_align(_iconContainer, NULL, LV_ALIGN_CENTER, 0, 0);

    // label to notify of unlock
    _touchNotifyLabel = lv_label_create(_container, NULL);
    lv_label_set_text(_touchNotifyLabel, "Press and hold to unlock");

    // label for unlock lock
    _touchLabel = lv_label_create(_container, NULL);
    lv_obj_add_style(_touchLabel, LV_LABEL_PART_MAIN, &_timeLabelStyle);
    lv_label_set_text(_touchLabel, LV_SYMBOL_EYE_OPEN);
    lv_obj_set_hidden(_touchLabel, true);

    updateIcons();
}

void UIScreenStandby::updateIcons()
=======
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(_tft->color565(127, 140, 141)); //#7f8c8d
    strftime(label, sizeof(label), "%a %d %B", &_timeInfo);
    if(init || (_lastMonth != _timeInfo.tm_mon))
    {
        _tft->fillRect(0,labelTop,TFT_WIDTH, _tft->fontHeight(), _bgColor);
        _lastMonth = _timeInfo.tm_mon;
        _tft->drawString(label, TFT_WIDTH/2, labelTop + (_tft->fontHeight()/2));
    }
    labelTop += _tft->fontHeight();

    // getting batery level
    _gui->updateBatteryLevel();

    // small bar beneath date
    uint16_t barHeight  = _tft->fontHeight() + 4;
    sprintf(label, "TODO: icons %d", barHeight);
    uint16_t barWidth   = _tft->textWidth(label) + 6;
    labelTop += 10;
    _tft->fillRoundRect((TFT_WIDTH - barWidth)/2, labelTop, barWidth, barHeight, 4, _tft->color565(189, 195, 199)); //#bdc3c7
    _tft->setTextColor(_bgColor);
    _tft->drawString(label, TFT_WIDTH/2, labelTop + (_tft->fontHeight()/2) + 2);

    // swipe up text
    _tft->setTextColor(_tft->color565(189, 195, 199));
    _tft->drawString("^ swipe up ^", TFT_WIDTH/2, TFT_HEIGHT - _tft->fontHeight());
}

void AppStandby::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
>>>>>>> no_lvgl:src/AppStandby.cpp
{
    char* systemIcon;
    for(uint8_t i = 0; i < GUI::systemIcons.size(); i++)
    {
        if(GUI::systemIcons[i].obj != nullptr)
        {
            if(GUI::systemIcons[i].label == LV_SYMBOL_CHARGE)
            {
                systemIcon = GUI::getBatteryIcon();
                if(systemIcon != GUI::systemIcons[i].label)
                {
                    // icon needs to be removed and another has to be added
                    lv_label_set_text(GUI::systemIcons[i].obj, systemIcon);
                    GUI::systemIcons[i].label = systemIcon;
                }
            }
            else {
                // check for alarm, wifi and bluetooth
                if(!(GUI::systemIcons[i].show && (GUI::systemIcons[i].label != nullptr)))
                {
                    lv_obj_clean(_iconContainer);
                    GUI::systemIcons[i].label = nullptr;
                    updateIcons();
                }
            }
        }
        else
        {
            if(GUI::systemIcons[i].show)
            {
                GUI::systemIcons[i].obj = lv_label_create(_iconContainer, NULL);
                lv_label_set_text(GUI::systemIcons[i].obj, GUI::systemIcons[i].label);
            }
        }
    }
}

<<<<<<< HEAD:src/UIScreenStandby.cpp
void UIScreenStandby::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback)
=======
void AppStandby::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
>>>>>>> no_lvgl:src/AppStandby.cpp
{
    if(!_touched && event == LV_EVENT_PRESSED){
        _touched = true;
        lv_obj_set_hidden(_touchLabel, false);
    }

    if(event == LV_EVENT_LONG_PRESSED)
    {
<<<<<<< HEAD:src/UIScreenStandby.cpp
        //_gui->getTTGO()->motor->onec();
        lv_obj_set_hidden(_touchLabel,true);
        if(_gui->getLastScreen() > SCREEN_STANDBY)
        {
            _gui->showScreen(_gui->getLastScreen());
        }
        else
        {
            _gui->showScreen(SCREEN_MAIN);
=======
        if(_gui->getLastApp() > _gui->getStandbyApp())
        {
            _gui->showApp(_gui->getLastApp());
        }
        else
        {
            _gui->showApp(_gui->getLauncherApp(), true);
>>>>>>> no_lvgl:src/AppStandby.cpp
        }
        _touched = false;
    }

    if(event == LV_EVENT_RELEASED)
    {
        _touched = false;
    }
}

void UIScreenStandby::updateTask(struct _lv_task_t* data)
{
    if(_touched && lv_obj_get_hidden(_touchLabel))
    {
        lv_obj_set_hidden(_touchLabel, false);
    }
    else if(!_touched)
    {
        lv_obj_set_hidden(_touchLabel, true);
    }
    
    GUI::updateTimeLabel(_timeLabel, GUI::timeFormatHM);
    GUI::updateTimeLabel(_dateLabel, GUI::dateFormatLong);

    updateIcons();
}
