#include "config.h"
#include "LilyGoWatch.h"

#include "AppStartup.h"

#include "GUI.h"

AppStartup::AppStartup():App("StartUp", false){}

void AppStartup::draw(bool init, bool task)
{
    String label        = "Starting up please wait...";
    _tft->setFreeFont();

    _tft->fillScreen(TFT_BLACK);
    _tft->fillRect(0,0, TFT_WIDTH, 20, TFT_RED);
    _tft->fillRect(0,TFT_HEIGHT - 20, TFT_WIDTH, 20, TFT_RED);
    _tft->setTextColor(TFT_RED);
    _tft->drawString(label, TFT_WIDTH/2, TFT_HEIGHT/2);
    
    _gui->getTTGO()->openBL();
    
    delay(1000);
    _gui->setApp(APP_STANDBY, true);
}

void AppStartup::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void AppStartup::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    
}