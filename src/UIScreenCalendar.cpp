#include "UIScreenCalendar.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UIScreenCalendar::UIScreenCalendar()
{
    _label              = "Calendar";
    _weekDayColor       = _tft->color565(189, 195, 199);    //#bdc3c7
    _weekEndColor       = _tft->color565(127, 140, 141);    //#7f8c8d
    _todayColor         = _tft->color565(41, 128, 185);     //#2980b9
    _highlightDayColor  = _tft->color565(149, 165, 166);    //#95a5a6
    _padding            = 10;
    _iconSizeX          = 2;
    _iconSizeY          = 2;
    _iconColor          = _tft->color565(0,120,215);
    _todayLabelWidth    = 0;
    _todayLabelHeight   = 0;
    _setDate(true);
}

void UIScreenCalendar::_setDate(bool init)
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

uint8_t UIScreenCalendar::_getDayOfWeek(uint8_t d, uint8_t m, uint16_t y)  
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y / 4 - y / 100 +  y / 400 + t[m - 1] + d) % 7;
}

uint8_t UIScreenCalendar::_getDaysOfMonth(uint8_t month, uint16_t year)
{
	//leap year condition, if month is 2
	if( month == 2)
	{
		if((year%400==0) || (year%4==0 && year%100!=0))
        {
			return 29;
        }
        else
        {
			return 28;
        }
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

uint8_t UIScreenCalendar::_getDaysOfPrevMonth(uint8_t month, uint16_t year)
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

uint8_t UIScreenCalendar::_getDaysOfNextMonth(uint8_t month, uint16_t year)
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

void UIScreenCalendar::draw(bool init, bool task)
{
    _setDate(init);

    if(!task)
    {
        _tft->fillScreen(_backgroundColor);

        // main UI
        _tft->setFreeFont(&FreeSansBold9pt7b);
        _tft->setTextColor(_textColor);
        
        // print today label/button
        if(_displayMonth != _month && _displayYear != _year)
        {
            _tft->drawString("Today", _padding, _padding);
        }

        if(_todayLabelWidth <= 0 && _todayLabelHeight <= 0)
        {
            _todayLabelWidth    = _tft->textWidth("Today");
            _todayLabelHeight   = _tft->fontHeight();
        }

        char buf[30];
        strftime(buf, sizeof(buf), "%B %Y", &_displayTimeInfo);
        _tft->drawString(buf, TFT_WIDTH - _padding - _tft->textWidth(buf), _padding);

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

void UIScreenCalendar::_drawCalendar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t padding, bool numbers)
{
    //uint8_t weeks         = ((_displayStartDayOfMonth + _displayEndOfMonth)+7-1)/7;
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
                    _tft->setTextColor(_backgroundColor);
                }
                /*
                else if(displayMonth)
                {
                    _tft->setTextColor(_textColor);
                }
                */
                else
                {
                    _tft->setTextColor(_textColor);
                }
                _tft->drawString(
                    dayNumber,
                    x+padding+(day*(dayWidth+1)) + (dayWidth-_tft->textWidth(dayNumber))/2,
                    y+padding+(week*(dayHeight+1)) + (dayHeight - _tft->fontHeight())/2 + 4
                );
            }
            counter++;
        }
    }
}

void UIScreenCalendar::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
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
        (x + (w/2)) - (_tft->textWidth(label)/2),
        (y + (h/2)) - ((weekdayHeight+dayOfMonthHeight)/2)
    );
    
    // print day of month
    _tft->setFreeFont(&FreeSansBold24pt7b);
    sprintf(label, "%d", _day);
    _tft->drawString(
        label,
        (x + (w/2)) - (_tft->textWidth(label)/2),
        (y + (h/2)) - ((weekdayHeight+dayOfMonthHeight)/2) + weekdayHeight
    );
}

void UIScreenCalendar::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
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
        case TouchMetrics::TOUCH:
            // today label click
            if(
                (_displayMonth != _month && _displayYear != _year)
                && (lastX <= (_padding + _todayLabelWidth))
                && (lastY <= (_padding + _todayLabelHeight))
            )
            {
                draw();
            }
            break;
    }
}
