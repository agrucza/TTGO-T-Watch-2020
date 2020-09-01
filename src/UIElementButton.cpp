#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementButton.h"

#include "GUI.h"

UIElementButton::UIElementButton(String label, const GFXfont* font, UIElement* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label  =label;
    _font   = font;
    _setDimensions();
}

void UIElementButton::_setDimensions()
{
    _tft->setFreeFont(_font);
    _dimensions                 = _parent->getDimensionsInner();
    _dimensions.bottomRight.y   = _tft->fontHeight()+4;
}

void UIElementButton::draw(bool task)
{
    if(!task)
    {
        _tft->setFreeFont(_font);
        _tft->setTextColor(_textColor);

        // input outline
        _tft->fillRoundRect(
            _dimensions.topLeft.x,
            _dimensions.topLeft.y,
            _dimensions.bottomRight.x,
            _dimensions.bottomRight.y,
            4,
            _colorActive
        );

        _tft->drawString(
            _label,
            _dimensions.topLeft.x + (_dimensions.bottomRight.x/2),
            _dimensions.topLeft.y + (_tft->fontHeight()/2)
        );
    }
}

void UIElementButton::reDraw()
{
    
}

bool UIElementButton::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch (touchType)
    {
    case TouchMetrics::TOUCH:
        //draw();
        /*
        if(_eventCallback)
        {
            _eventCallback(&_eventData);
        }
        */
        break;
    default:
        break;
    }
    
    return true;
}
