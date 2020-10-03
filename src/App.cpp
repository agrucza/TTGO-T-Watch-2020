#include "config.h"
#include "LilyGoWatch.h"

#include "App.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementTab.h"

extern GUI* gui;

App::App(String label, bool showTab)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showTab            = showTab;

    _appContainer = new UIContainer(this, SIZE_FULL);
    _appContainer->setPadding(0);

    if(_showTab)
    {
        _contentContainer = new UIElementTab(_appContainer, ALIGNMENT_HORIZONTAL);
        _appContainer->addUIElement(_contentContainer);
    }
}

void App::clean()
{
    if(_appContainer != nullptr)
    {
        _appContainer->clean();
    }
}
