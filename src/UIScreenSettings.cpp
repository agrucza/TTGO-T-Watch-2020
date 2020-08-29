#include "UIScreenSettings.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "fonts/IconsFontsSup24pt7b.h"

UIScreenSettings::UIScreenSettings():UIScreen()
{
    _label      = "Settings";
    _padding    = 10;
}

void UIScreenSettings::draw(bool init, bool task)
{
    if(!task)
    {
        _tft->fillScreen(_backgroundColor);
    }

    // main UI
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(_textColor);
}

void UIScreenSettings::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    // icon background
    _tft->fillRect(x,y,w,h, _iconColor);
    
    // print cog weel
    _tft->setFreeFont(&IconsFontsSup24pt7b);
    _tft->drawString(
        "C",
        x + (w - _tft->textWidth("C"))/2,
        y + 3 + (h - _tft->fontHeight())/2
    );
}

void UIScreenSettings::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch(touchType)
    {
        case TouchMetrics::SWIPE_BOTTOM:
        case TouchMetrics::SWIPE_BOTTOM_EDGE:
        case TouchMetrics::SWIPE_LEFT:
        case TouchMetrics::SWIPE_LEFT_EDGE:
        case TouchMetrics::SWIPE_RIGHT:
        case TouchMetrics::SWIPE_RIGHT_EDGE:
        case TouchMetrics::SWIPE_TOP:
        case TouchMetrics::SWIPE_TOP_EDGE:
        case TouchMetrics::TOUCH:
            break;
    }
}
