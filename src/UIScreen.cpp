#include "UIScreen.h"
#include "GUI.h"
#include "UIColors.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI* gui;

UIScreen::UIScreen()
{
    Serial.println("UIScreen constructor init");
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _textColor          = FLAT_UI_V1_CLOUDS;
    _backgroundColor    = FLAT_UI_V1_MIDNIGHT_BLUE;
    _iconColor          = FLAT_UI_V1_PETER_RIVER;
    _iconSizeX          = 1;
    _iconSizeY          = 1;
    Serial.println("UIScreen constructor init done");
}