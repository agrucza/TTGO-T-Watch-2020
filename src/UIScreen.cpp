#include "config.h"
#include "LilyGoWatch.h"

#include "UIScreen.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIColors.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup18pt7b.h"

extern GUI* gui;

UIScreen::UIScreen(String label, bool showHeader)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showHeader         = showHeader;

    _screenContainer = new UIContainer(this, SIZE_ELEMENT, ALIGNMENT_HORIZONTAL);
    _screenContainer->setPadding(0);
    
    _menuContainer = new UIContainer(_screenContainer);
    _screenContainer->addUIElement(_menuContainer);
    _menuContainer->setPadding(0);
    
    UIElementLabel* labelMenu1 = new UIElementLabel(UIICON_SUP_WRENCH, &IconsFontsSup18pt7b, _menuContainer);
    _menuContainer->addUIElement(labelMenu1);
    
    UIElementLabel* labelMenu2 = new UIElementLabel(UIICON_SUP_TRASH_BIN, &IconsFontsSup18pt7b, _menuContainer);
    _menuContainer->addUIElement(labelMenu2);
    
    _contentContainer = new UIContainer(_screenContainer, SIZE_FULL);
    _screenContainer->addUIElement(_contentContainer);
}

void UIScreen::clean()
{
    _screenContainer->clean();
};