#include "UIScreenStandby.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

#define DEG2RAD 0.0174532925

UIScreenStandby::UIScreenStandby():UIScreen()
{
    _label      = "Standby";
    _showHeader = false;
    _lastMinute = 0;
    _lastMonth  = 0;
}

void UIScreenStandby::draw(bool init, bool task)
{
    uint16_t    margin      = 40;
    uint16_t    labelTop    = margin;
    uint16_t    textWidth   = 0;
    char        label[20];

    time(&_currentTime);
    localtime_r(&_currentTime, &_timeInfo);

    if(!task)
    {
        _tft->fillScreen(_backgroundColor);
    }
    
    // time label
    _tft->setFreeFont(&FreeSansBold24pt7b);
    _tft->setTextColor(_textColor,_backgroundColor);
    strftime(label, sizeof(label), "%H : %M", &_timeInfo);
    textWidth = _tft->textWidth(label);
    if(init || (_lastMinute != _timeInfo.tm_min))
    {
        _tft->fillRect(0,labelTop,TFT_WIDTH, _tft->fontHeight(), _backgroundColor);
        _lastMinute = _timeInfo.tm_min;
        _tft->drawString(label, TFT_WIDTH/2, labelTop + _tft->fontHeight()/2);
    }
    labelTop += _tft->fontHeight();

    // date label
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(_tft->color565(127, 140, 141)); //#7f8c8d
    strftime(label, sizeof(label), "%a %d %B", &_timeInfo);
    textWidth = _tft->textWidth(label);
    if(init || (_lastMonth != _timeInfo.tm_mon))
    {
        _tft->fillRect(0,labelTop,TFT_WIDTH, _tft->fontHeight(), _backgroundColor);
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
    _tft->setTextColor(_backgroundColor);
    _tft->drawString(label, TFT_WIDTH/2, labelTop + (_tft->fontHeight()/2) + 2);

    // swipe up text
    _tft->setTextColor(_tft->color565(189, 195, 199));
    _tft->drawString("^ swipe up ^", TFT_WIDTH/2, TFT_HEIGHT - _tft->fontHeight());
}

void UIScreenStandby::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void UIScreenStandby::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    if(touchType == TouchMetrics::SWIPE_TOP)
    {
        if(_gui->getLastScreen() > SCREEN_STANDBY)
        {
            _gui->setScreen(_gui->getLastScreen());
        }
        else
        {
            _gui->setScreen(SCREEN_MAIN, true);
        }
    }
}