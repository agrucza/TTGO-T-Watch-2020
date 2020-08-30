#include "UITypes.h"
#include "UIElement.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI* gui;

UIElement::UIElement(UIElement* parent, UIEOrientation_t orientation)
{
    _tft            = gui->getTTGO()->tft;
    _parent         = parent;
    _orientation    = orientation;

    if(_parent)
    {
        _parentDimensions = _parent->getDimensions();
    }
    else
    {
        _parentDimensions.topLeft.x      = _parentDimensions.topLeft.y = 0;
        _parentDimensions.bottomRight.x  = TFT_WIDTH;
        _parentDimensions.bottomRight.y  = TFT_HEIGHT;
    }
}

void UIElement::setEventData(ui_event_data_t* data)
{
    _eventData.event    = data->event;
    _eventData.screen   = data->screen;
    _eventData.source   = data->source;
}
