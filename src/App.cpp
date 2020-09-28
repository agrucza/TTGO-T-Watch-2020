#include "config.h"
#include "LilyGoWatch.h"

#include "App.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementTab.h"

extern GUI* gui;

App::App(String label, bool showHeader)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showHeader         = showHeader;

    _appContainer = new UIContainer(this, SIZE_ELEMENT, ALIGNMENT_HORIZONTAL);
    _appContainer->setPadding(0);
    
    _contentContainer = new UITab(_appContainer, ALIGNMENT_VERTICAL);
    _appContainer->addUIElement(_contentContainer);
}

void App::clean()
{
    if(_appContainer != nullptr)
    {
        _appContainer->clean();
    }
};