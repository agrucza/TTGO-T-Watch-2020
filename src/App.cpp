#include "config.h"
#include "LilyGoWatch.h"

#include "App.h"

#include "GUI.h"
#include "UIContainer.h"

extern GUI* gui;

App::App(String label)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;

    _appContainer = new UIContainer(this, SIZE_FULL);
    _appContainer->setPadding(0);

    _contentContainer = new UIContainer(_appContainer, SIZE_FULL);

    _appContainer->addUIElement(_contentContainer);
}

void App::clean()
{
    if(_appContainer != nullptr)
    {
        _appContainer->clean();
    }
}
