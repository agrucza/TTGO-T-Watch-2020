#include "UIElementSwitch.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UIElementSwitch::UIElementSwitch(String label, const GFXfont* font, UIElement* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label              = label;
    _font               = font;
    _setDimensions();
}

void UIElementSwitch::_setDimensions()
{
    _tft->setFreeFont(_font);

    _size                       = _tft->fontHeight() * 2;

    _dimensions                 = _parent->getDimensionsInner();
    _dimensions.bottomRight.y   = _tft->fontHeight();
    _paddingInner               = _dimensions.bottomRight.x - _tft->textWidth(_label) - _size;
}

void UIElementSwitch::draw(bool task)
{
    if(!task)
    {
        UIPoint_t posSwitchE;
        uint16_t textWidth,textHeight;

        _tft->setFreeFont(_font);
        _tft->setTextColor(_textColor);

        textWidth   = _tft->textWidth(_label);
        textHeight  = _tft->fontHeight();

        _tft->drawString(
            _label,
            _dimensions.topLeft.x + (_orientation == ORIENTATION_LEFT?_dimensions.bottomRight.x - textWidth/2:textWidth/2),
            _dimensions.topLeft.y + (_dimensions.bottomRight.y/2)
        );

        posSwitchE.x = _dimensions.topLeft.x + (_orientation == ORIENTATION_RIGHT?textWidth + _paddingInner:0);
        posSwitchE.y = _dimensions.topLeft.y;

        // switch outline
        _tft->fillRoundRect(
            posSwitchE.x,
            posSwitchE.y,
            _size,
            textHeight,
            textHeight/2,
            (_enabled ? _colorActiveBg : _colorInactiveBg)
        );
        
        // switch element
        _tft->fillRoundRect(
            posSwitchE.x + (_enabled? _size - (textHeight -8) - 4 : 4),
            posSwitchE.y + 4,
            textHeight - 8,
            textHeight - 8,
            (textHeight-8)/2,
            (_enabled ? _colorActive : _colorInactive)
        );
    }
}

void UIElementSwitch::reDraw()
{
    
}

bool UIElementSwitch::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
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
