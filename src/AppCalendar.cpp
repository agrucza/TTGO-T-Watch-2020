#include "config.h"
#include "LilyGoWatch.h"

#include "AppCalendar.h"

#include "GUI.h"
#include "UIColors.h"

<<<<<<< HEAD:src/UIScreenCalendar.cpp
UIScreenCalendar::UIScreenCalendar():UIScreen()
{
    _label              = "Calendar";
    _showInLauncher     = true;
    
    // Create a window*/
    _container = lv_win_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_win_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    lv_win_set_title(_container, _label);

    // Add control button to the header
    _closeBtn = lv_win_add_btn(_container, LV_SYMBOL_CLOSE);
    _callbackData = new ScreenCallback(this, CALLBACK_SWITCH_SCREEN,SCREEN_MAIN);
    lv_obj_set_user_data(_closeBtn, _callbackData);
    lv_obj_set_event_cb(_closeBtn,GUI::screenEventCallback);
    
    _settingsBtn = lv_win_add_btn(_container, LV_SYMBOL_SETTINGS);
    _callbackData = new ScreenCallback(this, CALLBACK_NONE);
    lv_obj_set_user_data(_settingsBtn, _callbackData);
    lv_obj_set_event_cb(_settingsBtn,GUI::screenEventCallback);

    // calendar
    _calendar = lv_calendar_create(_container, NULL);
    lv_obj_add_style(_calendar, LV_CONT_PART_MAIN, &GUI::borderlessStyle);
    _callbackData = new ScreenCallback(this, CALLBACK_NONE);
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
    RTC_Date rtc_today  = GUI::getDateTime();
    today.year          = rtc_today.year;
    today.month         = rtc_today.month;
    today.day           = rtc_today.day;

    lv_calendar_set_today_date(_calendar, &today);
    lv_calendar_set_showed_date(_calendar, &today);

    /*Highlight a few days*/
    /*
    _highlightedDays = new lv_calendar_date_t[3];
    
    _highlightedDays[0].year = 2020;
    _highlightedDays[0].month = 8;
    _highlightedDays[0].day = 14;
    
    _highlightedDays[1].year = 2020;
    _highlightedDays[1].month = 8;
    _highlightedDays[1].day = 15;

    _highlightedDays[2].year = 2020;
    _highlightedDays[2].month = 8;
    _highlightedDays[2].day = 16;
    
    lv_calendar_set_highlighted_dates(_calendar, _highlightedDays, 3);
    */

    // modal
    /*
    UIModal* modal      = new UIModal(this, _callbackElement, "Events");
    lv_win_set_layout(modal->modalContent, LV_LAYOUT_COLUMN_LEFT);
    */
}

void UIScreenCalendar::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, ScreenCallback* callback)
{
    if(event == LV_EVENT_CLICKED)
    {
        if(obj == _closeBtn)
=======
AppCalendar::AppCalendar():App("Calendar", false)
{
    _weekDayColor       = FLAT_UI_V1_SILVER;
    _weekEndColor       = FLAT_UI_V1_ASBESTOS;
    _todayColor         = FLAT_UI_V1_BELIZE_HOLE;
    _highlightDayColor  = FLAT_UI_V1_PETER_RIVER;
    _padding            = 10;
    _iconSizeX          = 2;
    _iconSizeY          = 2;
    _todayLabelWidth    = 0;
    _todayLabelHeight   = 0;
    _setDate(true);
}

void AppCalendar::_setDate(bool init)
{
    time(&_currentTime);
    localtime_r(&_currentTime, &_timeInfo);
    
    _day                = _timeInfo.tm_mday;
    _month              = _timeInfo.tm_mon + 1;
    _year               = _timeInfo.tm_year + 1900;
    _startDayOfMonth    = _getDayOfWeek(1, _month, _year);
    _endOfMonth         = _getDaysOfMonth(_month, _year);

    if(_startDayOfMonth < 1)
    {
        _startDayOfMonth = 7;
    }

    if(init)
    {
        _displayTimeInfo        = _timeInfo;
    }

    _displayDay             = _displayTimeInfo.tm_mday;
    _displayMonth           = _displayTimeInfo.tm_mon +1;
    _displayYear            = _displayTimeInfo.tm_year + 1900;
    _displayStartDayOfMonth = _getDayOfWeek(1, _displayMonth, _displayYear);
    
    if(_displayStartDayOfMonth < 1)
    {
        _displayStartDayOfMonth = 7;
    }

    _displayEndOfMonth      = _getDaysOfMonth(_displayMonth, _displayYear);
    _displayPrevEndOfMonth  = _getDaysOfPrevMonth(_displayMonth, _displayYear);
    _displayNextEndOfMonth  = _getDaysOfNextMonth(_displayMonth, _displayYear);
}

uint8_t AppCalendar::_getDayOfWeek(uint8_t d, uint8_t m, uint16_t y)  
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y / 4 - y / 100 +  y / 400 + t[m - 1] + d) % 7;
}

uint8_t AppCalendar::_getDaysOfMonth(uint8_t month, uint16_t year)
{
	//leap year condition, if month is 2
	if( month == 2)
	{
		if((year%400==0) || (year%4==0 && year%100!=0))
        {
			return 29;
        }
        else
>>>>>>> no_lvgl:src/AppCalendar.cpp
        {
            _gui->showScreen(SCREEN_MAIN);
        }
<<<<<<< HEAD:src/UIScreenCalendar.cpp
        else if(obj == _settingsBtn)
        {

        }
    }
    else if(event == LV_EVENT_VALUE_CHANGED)
    {
        lv_calendar_date_t* date = lv_calendar_get_pressed_date(obj);
        if(date) {
            // modal

=======
	}
	//months which has 31 days
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||month == 10 || month==12)
    {
		return 31;
    }
    else
    {
        return 30;
    }
}

uint8_t AppCalendar::_getDaysOfPrevMonth(uint8_t month, uint16_t year)
{
    if(month<=1)
    {
        month   = 12;
        year    -= 1;
    }
    else
    {
        month -= 1;
    }

    return _getDaysOfMonth(month, year);
}

uint8_t AppCalendar::_getDaysOfNextMonth(uint8_t month, uint16_t year)
{
    if(month>=12)
    {
        month   = 1;
        year    += 1;
    }
    else
    {
        month += 1;
    }

    return _getDaysOfMonth(month, year);
}

void AppCalendar::draw(bool init, bool task)
{
    _setDate(init);

    if(!task)
    {
        _tft->fillScreen(_bgColor);

        // main UI
        _tft->setFreeFont(&FreeSansBold9pt7b);
        _tft->setTextColor(_textColor);
        
        // print today label/button
        if(_displayMonth != _month || _displayYear != _year)
        {
            _tft->drawString(
                "Today",
                _padding + _tft->textWidth("Today")/2,
                _padding + _tft->fontHeight()/2
            );
        }

        if(_todayLabelWidth <= 0 && _todayLabelHeight <= 0)
        {
            _todayLabelWidth    = _tft->textWidth("Today");
            _todayLabelHeight   = _tft->fontHeight();
        }

        char buf[30];
        strftime(buf, sizeof(buf), "%B %Y", &_displayTimeInfo);
        _tft->drawString(
            buf,
            TFT_WIDTH - _padding - _tft->textWidth(buf)/2,
            _padding + _tft->fontHeight()/2
        );

        _tft->fillRect(_padding, _padding+_tft->fontHeight(), TFT_WIDTH, 4, _textColor);

        // print calendar
        _drawCalendar(
            0,
            _padding + _tft->fontHeight() + 4,
            TFT_WIDTH,
            TFT_HEIGHT - (_padding + _tft->fontHeight() + 4),
            _padding,
            true
        );
    }
}

void AppCalendar::_drawCalendar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t padding, bool numbers)
{
    uint8_t weeks           = 6;
    uint8_t dayWidth        = (w-(padding*2)-(6))/7;
    uint8_t dayHeight       = (h-(padding*2)-(weeks-1))/weeks;
    int8_t  counter         = 1 - _displayStartDayOfMonth;
    bool    displayMonth    = false;
    bool    showToday       = false;
    char    dayNumber[3];
    
    for(uint8_t week = 0; week < weeks; week++)
    {
        for(uint8_t day = 0; day < 7; day++)
        {
            displayMonth    = false;
            showToday       = false;

            if(counter < 0)
            {
                sprintf(dayNumber,"%d", _displayPrevEndOfMonth + (counter+1));
            }
            else if(counter >= 0 && counter < _displayEndOfMonth)
            {
                displayMonth = true;
            
                // check if day needs to be shown highlighted as today
                if(
                    _displayYear        == _year
                    && _displayMonth    == _month
                    && counter+1        == _day
                )
                {
                    showToday = true;
                }

                sprintf(dayNumber,"%d",counter+1);
            }
            else
            {
                sprintf(dayNumber,"%d",(counter+1) - _displayEndOfMonth);
            }

            if(displayMonth)
            {
                _tft->fillRect(
                    x+padding+(day*(dayWidth+1)),
                    y+padding+(week*(dayHeight+1)),
                    dayWidth,
                    dayHeight,
                    (showToday?_todayColor:(day<5?_weekDayColor:_weekEndColor))
                );
            }
            
            if(numbers)
            {
                if(displayMonth && day<5 && !showToday)
                {
                    _tft->setTextColor(_bgColor);
                }
                else
                {
                    _tft->setTextColor(_textColor);
                }
                _tft->drawString(
                    dayNumber,
                    x+padding+(day*(dayWidth+1)) + dayWidth/2,
                    y+padding+(week*(dayHeight+1)) + dayHeight/2
                );
            }
            counter++;
>>>>>>> no_lvgl:src/AppCalendar.cpp
        }
    }
}

<<<<<<< HEAD:src/UIScreenCalendar.cpp
void UIScreenCalendar::updateTask(struct _lv_task_t* data)
{
    RTC_Date rtc_today  = GUI::getDateTime();
    today.year          = rtc_today.year;
    today.month         = rtc_today.month;
    today.day           = rtc_today.day;
=======
void AppCalendar::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    char    label[20];
    uint8_t weekdayHeight       = 0;
    uint8_t dayOfMonthHeight    = 0;

    _setDate(true);

    // icon background
    _tft->fillRect(x,y,w,h, _iconColor);
    
    _tft->setFreeFont(&FreeSansBold9pt7b);
    weekdayHeight = _tft->fontHeight();

    _tft->setFreeFont(&FreeSansBold24pt7b);
    dayOfMonthHeight = _tft->fontHeight();

    _tft->setTextColor(TFT_WHITE);
    
    // print weekday
    _tft->setFreeFont(&FreeSansBold9pt7b);
    strftime(label, sizeof(label), "%A", &_displayTimeInfo);
    _tft->drawString(
        label,
        (x + (w/2)),
        (y + (h/2)) - ((weekdayHeight+dayOfMonthHeight)/2) + weekdayHeight/2
    );
    
    // print day of month
    _tft->setFreeFont(&FreeSansBold24pt7b);
    sprintf(label, "%d", _day);
    _tft->drawString(
        label,
        (x + (w/2)),
        (y + (h/2)) + ((weekdayHeight+dayOfMonthHeight)/2) - dayOfMonthHeight/2
    );
}

void AppCalendar::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch(touchType)
    {
        case TouchMetrics::SWIPE_BOTTOM:
        case TouchMetrics::SWIPE_BOTTOM_EDGE:
            break;
        case TouchMetrics::SWIPE_LEFT:
            _displayTimeInfo.tm_mday    = 1;
            _displayTimeInfo.tm_mon     += 1;
            _displayTime = mktime(&_displayTimeInfo);
            draw();
            break;
        case TouchMetrics::SWIPE_LEFT_EDGE:
            break;
        case TouchMetrics::SWIPE_RIGHT:
            _displayTimeInfo.tm_mday    = 1;
            _displayTimeInfo.tm_mon     -= 1;
            _displayTime = mktime(&_displayTimeInfo);
            draw();
            break;
        case TouchMetrics::SWIPE_RIGHT_EDGE:
        case TouchMetrics::SWIPE_TOP:
        case TouchMetrics::SWIPE_TOP_EDGE:
            break;
        case TouchMetrics::TOUCH_RELEASE:
            // today label click
            if(
                (_displayMonth != _month || _displayYear != _year)
                && (lastX <= (_padding + _todayLabelWidth))
                && (lastY <= (_padding + _todayLabelHeight))
            )
            {
                draw(true);
            }
            break;
    }
>>>>>>> no_lvgl:src/AppCalendar.cpp
}
