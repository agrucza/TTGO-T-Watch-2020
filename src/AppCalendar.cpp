#include "AppCalendar.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

AppCalendar::AppCalendar():App("Calendar")
{
    // Create a window*/
    _container = lv_win_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    lv_win_set_title(_container, _label.c_str());

    // Add control button to the header
    _closeBtn = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData = new AppCallback(this, CALLBACK_SWITCH_APP, _gui->getApp("Launcher"));
    lv_obj_set_user_data(_closeBtn, _callbackData);
    lv_obj_set_event_cb(_closeBtn,GUI::appEventCallback);
    
    _settingsBtn = lv_win_add_btn(_container, LV_SYMBOL_SETTINGS);
    _callbackData = new AppCallback(this, CALLBACK_NONE);
    lv_obj_set_user_data(_settingsBtn, _callbackData);
    lv_obj_set_event_cb(_settingsBtn,GUI::appEventCallback);

    // calendar
    _calendar = lv_calendar_create(_container, NULL);
    lv_obj_add_style(_calendar, LV_CONT_PART_MAIN, &GUI::styleBorderless);
    _callbackData = new AppCallback(this, CALLBACK_NONE);
    lv_obj_set_pos(_calendar,0,0);
    lv_obj_set_width(_calendar, TFT_WIDTH);
    lv_obj_set_height(_calendar, TFT_HEIGHT-lv_win_get_header_height(_container));
    lv_obj_align(_calendar, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_user_data(_calendar, _callbackData);
    lv_obj_set_event_cb(_calendar, GUI::appEventCallback);

    /*Make the date number smaller to be sure they fit into their area*/
    lv_obj_set_style_local_text_font(_calendar, LV_CALENDAR_PART_HEADER, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_obj_set_style_local_text_font(_calendar, LV_CALENDAR_PART_DAY_NAMES, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    lv_obj_set_style_local_text_font(_calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, &lv_font_montserrat_12);

    /*Set today's date*/
    RTC_Date rtc_today  = GUI::getDateTime();
    _today.year          = rtc_today.year;
    _today.month         = rtc_today.month;
    _today.day           = rtc_today.day;

    lv_calendar_set_today_date(_calendar, &_today);
    lv_calendar_set_showed_date(_calendar, &_today);

    /*Highlight a few days*/
    _highlightedDays = new lv_calendar_date_t[3];
    
    _highlightedDays[0].year = 2020;
    _highlightedDays[0].month = 10;
    _highlightedDays[0].day = 1;
    
    _highlightedDays[1].year = 2020;
    _highlightedDays[1].month = 10;
    _highlightedDays[1].day = 2;

    _highlightedDays[2].year = 2020;
    _highlightedDays[2].month = 10;
    _highlightedDays[2].day = 4;
    
    lv_calendar_set_highlighted_dates(_calendar, _highlightedDays, 3);

    // modal
    /*
    UIModal* modal      = new UIModal(this, _callbackElement, "Events");
    lv_win_set_layout(modal->modalContent, LV_LAYOUT_COLUMN_LEFT);
    */
}

void AppCalendar::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback)
{
    if(event == LV_EVENT_CLICKED)
    {
        if(obj == _closeBtn)
        {
            _gui->showApp("Launcher");
        }
        else if(obj == _settingsBtn)
        {

        }
    }
    else if(event == LV_EVENT_VALUE_CHANGED)
    {
        lv_calendar_date_t* date = lv_calendar_get_pressed_date(obj);
        if(date) {
            // modal

        }
    }
}

void AppCalendar::updateTask(struct _lv_task_t* data)
{
    RTC_Date rtc_today  = GUI::getDateTime();
    _today.year          = rtc_today.year;
    _today.month         = rtc_today.month;
    _today.day           = rtc_today.day;
}
