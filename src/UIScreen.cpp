#include "UIScreen.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI* gui;

UIScreen::UIScreen()
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _textColor          = _tft->color565(236, 240, 241);    //#ecf0f1
    _backgroundColor    = _tft->color565(44, 62, 80);       //#2c3e50
    _iconSizeX          = 1;
    _iconSizeY          = 1;
}