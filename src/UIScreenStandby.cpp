#include "UIScreenStandby.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

#define DEG2RAD 0.0174532925

extern GUI *gui;

UIScreenStandby::UIScreenStandby(){
    _gui = gui;
    _tft = _gui->getTFT();
    //draw();
}

void UIScreenStandby::draw(bool init)
{
    uint16_t    margin      = 40;
    uint16_t    labelTop    = margin;
    uint16_t    textWidth   = 0;
    char        label[20];

    time(&_currentTime);
    localtime_r(&_currentTime, &_timeInfo);

    _tft->fillScreen(TFT_BLACK);
    
    // time label
    _tft->setFreeFont(&FreeSansBold24pt7b);
    _tft->setTextColor(TFT_WHITE);
    strftime(label, sizeof(label), "%H : %M", &_timeInfo);
    textWidth = _tft->textWidth(label);
    _tft->drawString(label, (TFT_WIDTH - textWidth)/2, labelTop);
    labelTop += _tft->fontHeight();
    
    // date label
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(TFT_DARKGREY);
    strftime(label, sizeof(label), "%a %d %B", &_timeInfo);
    textWidth = _tft->textWidth(label);
    _tft->drawString(label, (TFT_WIDTH - textWidth)/2, labelTop);
    labelTop += _tft->fontHeight();

    // getting batery level
    _gui->updateBatteryLevel();

    // small bar beneath date
    uint16_t barHeight  = _tft->fontHeight() + 4;
    sprintf(label, "TODO: icons %d", barHeight);
    uint16_t barWidth   = _tft->textWidth(label) + 6;
    labelTop += 10;
    _tft->fillRoundRect((TFT_WIDTH - barWidth)/2, labelTop, barWidth, barHeight, 4, TFT_LIGHTGREY);
    _tft->setTextColor(TFT_LIGHTGREY);
    _tft->drawString(label, (TFT_WIDTH - barWidth)/2, labelTop + 5);

    // swipe up text
    _tft->drawString("^ swipe up ^", (TFT_WIDTH - _tft->textWidth("^ swipe up ^"))/2, TFT_HEIGHT - _tft->fontHeight());
}

// #########################################################################
// Draw a circular or elliptical arc with a defined thickness
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 6 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn
void UIScreenStandby::_fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{
    byte seg = 6; // Segments are 3 degrees wide = 120 segments for 360 degrees
    byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

    // Calculate first pair of coordinates for segment start
    float sx = cos((start_angle - 90) * DEG2RAD);
    float sy = sin((start_angle - 90) * DEG2RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;

    // Draw colour blocks every inc degrees
    for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {
        // Calculate pair of coordinates for segment end
        float sx2 = cos((i + seg - 90) * DEG2RAD);
        float sy2 = sin((i + seg - 90) * DEG2RAD);
        int x2 = sx2 * (rx - w) + x;
        int y2 = sy2 * (ry - w) + y;
        int x3 = sx2 * rx + x;
        int y3 = sy2 * ry + y;

        _tft->fillTriangle(x0, y0, x1, y1, x2, y2, colour);
        _tft->fillTriangle(x1, y1, x2, y2, x3, y3, colour);

        // Copy segment end to sgement start for next segment
        x0 = x2;
        y0 = y2;
        x1 = x3;
        y1 = y3;
    }
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