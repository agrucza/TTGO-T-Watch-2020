#include "config.h"
#include "LilyGoWatch.h"

#include "AppSettings.h"

#include "GUI.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup24pt7b.h"

AppSettings::AppSettings():App("Settings"){}

void AppSettings::draw(bool init, bool task)
{
    if(!task)
    {
        _tft->fillScreen(_bgColor);
    }

    // main UI
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(_textColor);
}

void AppSettings::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    // icon background
    _tft->fillRect(x,y,w,h, _iconColor);
    
    // print cog weel
    _tft->setFreeFont(&IconsFontsSup24pt7b);
    _tft->drawString(
        UIICON_SUP_GEAR,
        x + (w/2),
        y + (h/2)-3
    );
}

void AppSettings::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
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
        case TouchMetrics::TOUCH_RELEASE:
            break;
    }
}
