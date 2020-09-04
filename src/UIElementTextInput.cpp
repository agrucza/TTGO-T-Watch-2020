#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementTextInput.h"

#include "GUI.h"
#include "UIContainer.h"

UIElementTextInput::UIElementTextInput(String placeholder, const GFXfont* font, UIContainer* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _placeholder        = (placeholder!=""?placeholder:"Placeholder");
    _font               = font;
    _setDimensions();
}

void UIElementTextInput::_setDimensions()
{
    _tft->setFreeFont(_font);
    _dimensions                 = _parent->getDimensions();
    _dimensions.topLeft.x       += _parent->getPadding();
    _dimensions.topLeft.y       += _parent->getPadding();
    _dimensions.bottomRight.x   -= 2*_parent->getPadding();
    _dimensions.bottomRight.y   = _tft->fontHeight()+4;
}

void UIElementTextInput::draw(bool task)
{
    if(!task)
    {
        UIPoint_t absPos = getTopPosition();
        String textToDraw = (_text!=""?_text:_placeholder);
        
        _tft->setFreeFont(_font);
        _tft->setTextColor((_text!=""?_textColor:_colorInactive));

        // input outline
        _tft->drawRoundRect(
            absPos.x,
            absPos.y,
            _dimensions.bottomRight.x,
            _dimensions.bottomRight.y,
            4,
            (_active ? _colorActive : _colorInactive)
        );

        _tft->drawString(
            textToDraw,
            absPos.x + (_dimensions.bottomRight.x/2),
            absPos.y + (_tft->fontHeight()/2)
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
    case TouchMetrics::TOUCH_RELEASE:
        _active ^= true;
        draw();
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
