#include "App.h"

App::App(String label, bool showInLauncher)
{
    _gui                = gui;
    _label              = label;
    _showInLauncher     = showInLauncher;
    _container          = nullptr;
    _callbackElement    = nullptr;
}

void App::eventCallback(lv_obj_t *obj, lv_event_t event, AppCallback* callback)
{
    eventCallback(obj,  NULL, event, callback);
}

void App::show()
{
    if(_container != nullptr)
    {
        lv_obj_set_hidden(_container, false);
        lv_obj_move_foreground(_container);
        //UIModal::show(this);
    }
}

void App::hide()
{
    if(_container != nullptr)
    {
        //UIModal::hideAll();
        lv_obj_set_hidden(_container, true);
        lv_obj_move_background(_container);
    }
}
