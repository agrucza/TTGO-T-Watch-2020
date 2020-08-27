#include "UIScreenStartup.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UIScreenStartup::UIScreenStartup():UIScreen()
{
    _label  = "Startup";
}

void UIScreenStartup::draw(bool init, bool task)
{
    String label        = "Starting up please wait...";
    _tft->setFreeFont();
    uint16_t textWidth  = _tft->textWidth(label);
    uint16_t textHeight = _tft->fontHeight();

    _tft->fillScreen(TFT_BLACK);
    _tft->fillRect(0,0, TFT_WIDTH, 20, TFT_RED);
    _tft->fillRect(0,TFT_HEIGHT - 20, TFT_WIDTH, 20, TFT_RED);
    _tft->setTextColor(TFT_RED);
    _tft->drawString(label, (TFT_WIDTH - textWidth)/2, (TFT_HEIGHT - textHeight)/2);
    
    _gui->getTTGO()->openBL();
    
    delay(1000);
    _gui->setScreen(SCREEN_STANDBY, true);
}

void UIScreenStartup::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void UIScreenStartup::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    
}