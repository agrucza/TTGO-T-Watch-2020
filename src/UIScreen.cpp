#include "UIScreen.h"
#include "GUI.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIColors.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI* gui;

UIScreen::UIScreen(String label, bool showHeader)
{
    Serial.println("UIScreen constructor init");
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showHeader         = showHeader;

    Serial.println("Creating screenContainer");
    _screenContainer = new UIContainer(this);
    _screenContainer->setPadding(0);

    if(_showHeader)
    {
        Serial.println("Add header to screenContainer");
        UIElementLabel* labelHead = new UIElementLabel(_label, &FreeSansBold9pt7b, _screenContainer, ORIENTATION_RIGHT);
        labelHead->setTextColor(FLAT_UI_V1_CLOUDS);
        labelHead->showLine(true, ORIENTATION_RIGHT);
        _screenContainer->addUIElement(labelHead);
    }
    
    Serial.println("Creating contentContainer");
    _contentContainer = new UIContainer(_screenContainer);
    
    Serial.println("Add contentContainer to screenContainer");
    _screenContainer->addUIElement(_contentContainer);

    Serial.println("UIScreen constructor init done");
}