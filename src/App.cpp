#include "config.h"
#include "LilyGoWatch.h"

#include "App.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIColors.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup18pt7b.h"

extern GUI* gui;

App::App(String label, bool showHeader)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showHeader         = showHeader;

    _appContainer = new UIContainer(this, SIZE_ELEMENT, ALIGNMENT_HORIZONTAL);
    _appContainer->setPadding(0);
    
    _menuContainer = new UIContainer(_appContainer);
    _appContainer->addUIElement(_menuContainer);
    _menuContainer->setPadding(0);
    
    UIElementLabel* labelMenu1 = new UIElementLabel(UIICON_SUP_WRENCH, &IconsFontsSup18pt7b, _menuContainer);
    _menuContainer->addUIElement(labelMenu1);
    
    UIElementLabel* labelMenu2 = new UIElementLabel(UIICON_SUP_TRASH_BIN, &IconsFontsSup18pt7b, _menuContainer);
    _menuContainer->addUIElement(labelMenu2);
    
    _contentContainer = new UIContainer(_appContainer, SIZE_FULL);
    _appContainer->addUIElement(_contentContainer);
}

void App::clean()
{
    _appContainer->clean();
};