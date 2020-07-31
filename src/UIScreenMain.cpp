#include "UIScreenMain.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

UIScreenMain::UIScreenMain(){
    _gui            = gui;
    _tft            = _gui->getTFT();
    _screensX       = _screensY = 2;
    _screensPerPage = _screensX * _screensY;
    _page           = 0;
    _padding        = 10;
    _visibleScreen  = 0;
    _firstScreen    = 0;
    _lastScreen     = 0;
    _screenCount    = SCREEN_COUNT - (SCREEN_MAIN+1);
    _pageMax        = (_screenCount + (_screensX*_screensY) - 1) / (_screensX*_screensY);
    
    if(_pageMax == 0){_pageMax = 1;}

    _pageAmount = _pageMax - _page;
}

void UIScreenMain::draw(bool init)
{
    _tft->fillScreen(TFT_WHITE);

    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->setTextColor(TFT_LIGHTGREY);

    _visibleScreen                  = TFT_HEIGHT - _padding * 3;
    uint8_t     nonVisibleScreen    = SCREEN_MAIN + _page * _screensX * _screensY;
    _firstScreen                    = nonVisibleScreen + 1;
    _lastScreen                     = SCREEN_MAIN + _screenCount;
    _screenWidth                    = (TFT_WIDTH - ((_screensX+1)*_padding))/_screensX;
    _screenHeight                   = (_visibleScreen - ((_screensY+1)*_padding))/_screensY;
    char*       label;
    uint8_t     screen              = 0;
    uint8_t     labelHeight         = _tft->fontHeight();
    
    for(uint8_t row = 0; row < _screensY; row++)
    {
        for(uint8_t column = 0; column < _screensX; column++)
        {
            screen = _firstScreen + (row * _screensY) + column;
            if(screen >= _firstScreen && screen <= _lastScreen)
            {
                _gui->drawUIScreenIcon(
                    static_cast<screens_t>(screen),
                    _padding + column * (_padding + _screenWidth),
                    _padding + row * (_padding + _screenHeight),
                    _screenWidth,
                    _screenHeight - labelHeight
                );
                label = _gui->getUIScreenLabel(static_cast<screens_t>(screen));
                _tft->drawString(
                    label,
                    _padding + column * (_padding + _screenWidth) + _screenWidth/2 - (_tft->textWidth(label)/2),
                    _padding + _screenHeight + 5 + row * (_padding + _screenHeight) - labelHeight
                );
            }
        }
    }

    uint8_t navigationWidth = (_pageAmount * _padding) + ((_pageAmount - 2) * _padding);

    // draw navigation circles
    for(uint8_t i = 0; i<_pageAmount; i++)
    {
        uint8_t pos = (TFT_WIDTH-navigationWidth)/2 + i*(2*_padding);
        _tft->fillCircle(pos, TFT_HEIGHT - 1.5*_padding, _padding/2, (_page == i?TFT_BLACK:TFT_LIGHTGREY));
    }
}

void UIScreenMain::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void UIScreenMain::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    if(touchType == TouchMetrics::TOUCH)
    {
        uint8_t screen = 0;
        uint8_t leftEdge, topEdge = 0;
        
        for(uint8_t row = 0; row < _screensY; row++)
        {
            for(uint8_t column = 0; column < _screensX; column++)
            {
                screen      = _firstScreen + (row * _screensY) + column;
                leftEdge    = _padding + column * (_padding + _screenWidth);
                topEdge     = _padding + row * (_padding + _screenHeight);

                if(
                    screen <= _lastScreen
                    && lastX >= leftEdge && lastX <= leftEdge + _screenWidth
                    && lastY >= topEdge && lastY <= topEdge + _screenHeight
                )
                {
                    _gui->setScreen(static_cast<screens_t>(screen), true);
                }
            }
        }
    }
    else if (touchType == TouchMetrics::SWIPE_LEFT)
    {
        // go forth in navigation
        if(_page < _pageMax-1){
            _page++;
            draw();
        }
    }
    else if (touchType == TouchMetrics::SWIPE_RIGHT)
    {
        // go back in navigation
        if(_page > 0){
            _page--;
            draw();
        }
    }
}
