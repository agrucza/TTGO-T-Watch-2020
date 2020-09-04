#include "config.h"
#include "LilyGoWatch.h"

#include "UIElement.h"

#include "UITypes.h"
#include "GUI.h"
#include "UIContainer.h"

extern GUI* gui;

UIElement::UIElement(UIContainer* parent, UIEOrientation_t orientation)
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

UIPoint_t UIElement::getTopPosition()
{
    if(!_parent)
    {
        return _dimensions.topLeft;
    }

    UIPoint_t pos       = _dimensions.topLeft;
    UIPoint_t parentPos = _parent->getTopPosition();
    pos.x               += parentPos.x;
    pos.y               += parentPos.y;

    return pos;
}

bool UIElement::isWithinDimensions(int x, int y){
    if(
        (x >= _dimensions.topLeft.x && x <= _dimensions.topLeft.x + _dimensions.bottomRight.x)
        && (y >= _dimensions.topLeft.y && y <= _dimensions.topLeft.y + _dimensions.bottomRight.y)
    ){
        return true;
    }
    return false;
};

void UIElement::setEventData(ui_event_data_t* data)
{
    _eventData.event    = data->event;
    _eventData.screen   = data->screen;
    _eventData.source   = data->source;
}
