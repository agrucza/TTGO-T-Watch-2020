#include "UIScreenSettings.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

UIScreenSettings::UIScreenSettings()
{
    _gui        = gui;
    _tft        = _gui->getTFT();
    _label      = "Settings";
    _padding    = 10;
    _iconSizeX  = 1;
    _iconSizeY  = 1;
    _iconColor  = _tft->color565(0,120,215);
}

void UIScreenSettings::draw(bool init)
{
    _tft->fillScreen(TFT_BLACK);

    // main UI
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(TFT_WHITE);
}

void UIScreenSettings::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    // icon background
    _tft->fillRect(x,y,w,h, _iconColor);
    /*
    // print cog weel
    _tft->setFreeFont(&IconsFontsSup24pt7b);
    _tft->drawString(
        "B",
        x + (w - _tft->textWidth("B"))/2,
        y + (h - _tft->fontHeight())/2
    );
    */
}

void UIScreenSettings::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch(touchType)
    {
        case TouchMetrics::TOUCH:
            break;
        case TouchMetrics::SWIPE_LEFT:
            draw();
            break;
        case TouchMetrics::SWIPE_RIGHT:
            draw();
            break;
        case TouchMetrics::SWIPE_BOTTOM_EDGE:
            _gui->setScreen(SCREEN_MAIN);
            break;
    }
}
