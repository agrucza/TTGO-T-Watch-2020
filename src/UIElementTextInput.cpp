#include "UIElementTextInput.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UIElementTextInput::UIElementTextInput(String placeholder, const GFXfont* font, UIElement* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _placeholder        = (placeholder!=""?placeholder:"Placeholder");
    _font               = font;
    _setDimensions();
}

void UIElementTextInput::_setDimensions()
{
    _tft->setFreeFont(_font);
    _dimensions                 = _parent->getDimensionsInner();
    _dimensions.bottomRight.y   = _tft->fontHeight()+4;
}

void UIElementTextInput::draw(bool task)
{
    String textToDraw = (_text!=""?_text:_placeholder);

    if(!task)
    {
        _tft->setFreeFont(_font);
        _tft->setTextColor((_text!=""?_textColor:_colorInactive));

        // input outline
        _tft->drawRoundRect(
            _dimensions.topLeft.x,
            _dimensions.topLeft.y,
            _dimensions.bottomRight.x,
            _dimensions.bottomRight.y,
            4,
            (_enabled ? _colorActive : _colorInactive)
        );

        _tft->drawString(
            textToDraw,
            _dimensions.topLeft.x + (_dimensions.bottomRight.x/2),
            _dimensions.topLeft.y + (_tft->fontHeight()/2)
        );
    }
}

void UIElementTextInput::reDraw()
{
    
}

bool UIElementTextInput::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch (touchType)
    {
    case TouchMetrics::TOUCH:
        _enabled ^= true;
        draw();
        Serial.println("Switch changed");
        if(_eventCallback)
        {
            _eventCallback(&_eventData);
        }
        break;
    default:
        break;
    }
    
    return true;
}
