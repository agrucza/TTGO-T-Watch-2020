#include "config.h"
#include "LilyGoWatch.h"

#include "UIScreen.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIColors.h"

extern GUI* gui;

UIScreen::UIScreen(String label, bool showHeader)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showHeader         = showHeader;

    _screenContainer = new UIContainer(this);
    _screenContainer->setPadding(0);

    if(_showHeader)
    {
        UIElementLabel* labelHead = new UIElementLabel(_label, &FreeSansBold9pt7b, _screenContainer, ORIENTATION_RIGHT);
        labelHead->setTextColor(FLAT_UI_V1_CLOUDS);
        labelHead->showLine(true, ORIENTATION_RIGHT);
        _screenContainer->addUIElement(labelHead);
    }
    
    _contentContainer = new UIContainer(_screenContainer);
    _screenContainer->addUIElement(_contentContainer);
}