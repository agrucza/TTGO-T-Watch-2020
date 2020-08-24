#include "UIScreenStandby.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

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

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    _callbackData = new ScreenCallback(this, CALLBACK_NONE);

    lv_obj_set_user_data(_container,_callbackData);
    lv_obj_set_event_cb(_container,GUI::screenEventCallback);
    
    lv_obj_add_style(_container, LV_CONT_PART_MAIN, &GUI::borderlessStyle);

    lv_obj_set_auto_realign(_container, true);
    lv_obj_align_origo(_container, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_layout(_container, LV_LAYOUT_COLUMN_MID);

    lv_obj_set_size(_container, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(_container, NULL, LV_ALIGN_CENTER, 0, 0);
    
    // time label
    lv_style_init(&_timeLabelStyle);
    lv_style_set_text_font(&_timeLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_48);
    _timeLabel = lv_label_create(_container, NULL);
    lv_obj_add_style(_timeLabel, LV_LABEL_PART_MAIN, &_timeLabelStyle);
    GUI::updateTimeLabel(_timeLabel, GUI::timeFormatHM);
    
    // date label
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

void UIScreenStandby::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback)
{
    if(!_touched && event == LV_EVENT_PRESSED){
        _touched = true;
        lv_obj_set_hidden(_touchLabel, false);
    }

    if(event == LV_EVENT_LONG_PRESSED)
    {
        //_gui->getTTGO()->motor->onec();
        lv_obj_set_hidden(_touchLabel,true);
        if(_gui->getLastScreen() > SCREEN_STANDBY)
        {
            _gui->showScreen(_gui->getLastScreen());
        }
        else
        {
            _gui->showScreen(SCREEN_MAIN);
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
