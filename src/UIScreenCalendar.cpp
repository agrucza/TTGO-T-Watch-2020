#include "UIScreenCalendar.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

UIScreenCalendar::UIScreenCalendar():UIScreen()
{
    _label              = "Calendar";
    _showInLauncher     = true;
    _callbackElement    = 0;

    // Add buttons
    lv_obj_t* element;
    
    // Create a window*/
    _container = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    lv_win_set_title(_container, _label);

    // Add control button to the header
    element = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_SWITCH_SCREEN,SCREEN_MAIN);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element,GUI::screenEventCallback);
    
    element = lv_win_add_btn(_container, LV_SYMBOL_SETTINGS);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_NONE);
    lv_obj_set_user_data(element, _callbackData);
    lv_obj_set_event_cb(element,GUI::screenEventCallback);

    // calendar
    _calendar = lv_calendar_create(_container, NULL);
    lv_obj_add_style(_calendar, LV_CONT_PART_MAIN, &GUI::borderlessStyle);
    _callbackData = new ScreenCallback(this, _callbackElement++, CALLBACK_NONE);
    lv_obj_set_pos(_calendar,0,0);
    lv_obj_set_width(_calendar, TFT_WIDTH);
    lv_obj_set_height(_calendar, TFT_HEIGHT-lv_win_get_header_height(_container));
    lv_obj_align(_calendar, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_user_data(_calendar, _callbackData);
    lv_obj_set_event_cb(_calendar, GUI::screenEventCallback);

    /*Make the date number smaller to be sure they fit into their area*/
    lv_obj_set_style_local_text_font(_calendar, LV_CALENDAR_PART_HEADER, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_obj_set_style_local_text_font(_calendar, LV_CALENDAR_PART_DAY_NAMES, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_obj_set_style_local_text_font(_calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, &lv_font_montserrat_12);

    /*Set today's date*/
    lv_calendar_date_t today;
    today.year = 2020;
    today.month = 8;
    today.day = 10;

    lv_calendar_set_today_date(_calendar, &today);
    lv_calendar_set_showed_date(_calendar, &today);

    /*Highlight a few days*/
    _highlightedDays = new lv_calendar_date_t[1];
    
    _highlightedDays[0].year = 2020;
    _highlightedDays[0].month = 8;
    _highlightedDays[0].day = 11;
    /*
    highlighted_days[1].year = 2018;
    highlighted_days[1].month = 10;
    highlighted_days[1].day = 11;

    highlighted_days[2].year = 2018;
    highlighted_days[2].month = 11;
    highlighted_days[2].day = 22;
    */
    lv_calendar_set_highlighted_dates(_calendar, _highlightedDays, 1);
}

void UIScreenCalendar::eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t* date = lv_calendar_get_pressed_date(obj);
        if(date) {
            char buf[50];
            sprintf(buf, "Clicked date: %02d.%02d.%d", date->day, date->month, date->year);
            _gui->getTTGO()->tft->drawString(buf,0,0);
        }
    }
    else
    {
        switch(callback->getCbElement()){
            case 0:
                // close button
                _gui->showScreen(SCREEN_MAIN);
                break;
            case 1:
                // settings button
                break;
            case 2:
                // calendar
                break;
        }
    }
}

void UIScreenCalendar::lvUpdateTask(struct _lv_task_t* data)
{
    
}
