#include "UIElementSwitch.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UIElementSwitch::UIElementSwitch(String label, const GFXfont* font, UIElement* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label              = label;
    _font               = font;
    _paddingInner       = 10;
    _switchEnabled      = false;
    _swColorActive      = FLAT_UI_V1_PETER_RIVER;
    _swColorInactive    = FLAT_UI_V1_ASBESTOS;
    _setDimensions();
}

void UIElementSwitch::_setDimensions()
{
    _tft->setFreeFont(_font);

    _switchSize                 = _tft->fontHeight() * 2;

    _dimensions                 = _parent->getDimensionsInner();
    _dimensions.bottomRight.y   = _tft->fontHeight();
    _dimensions.bottomRight.x   = _tft->textWidth(_label) + _paddingInner + _switchSize;
    
    switch(_orientation)
    {
        case CENTER_TOP:
        case CENTER_CENTER:
        case CENTER_BOTTOM:
            _dimensions.topLeft.x += (_parent->getDimensionsInner().bottomRight.x-_dimensions.bottomRight.x)/2;
            break;
        case RIGHT_TOP:
        case RIGHT_CENTER:
        case RIGHT_BOTTOM:
            _dimensions.topLeft.x += _parent->getDimensionsInner().bottomRight.x - _dimensions.bottomRight.x;
            break;
    }
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
            _dimensions.topLeft.x + (textWidth/2),
            _dimensions.topLeft.y + (_dimensions.bottomRight.y/2)
        );

        posSwitchE.x = _dimensions.topLeft.x + textWidth + _paddingInner;
        posSwitchE.y = _dimensions.topLeft.y;

        // switch outline
        _tft->fillRoundRect(
            posSwitchE.x,
            posSwitchE.y,
            _switchSize,
            textHeight,
            textHeight/2,
            _textColor
        );

        // switch inner
        _tft->fillRoundRect(
            posSwitchE.x + 2,
            posSwitchE.y + 2,
            _switchSize - 4,
            textHeight - 4,
            (textHeight-4)/2,
            FLAT_UI_V1_SILVER
        );

        // switch element
        _tft->fillRoundRect(
            posSwitchE.x + (_switchEnabled? _switchSize - (textHeight -8) - 4 : 4),
            posSwitchE.y + 4,
            textHeight - 8,
            textHeight - 8,
            (textHeight-8)/2,
            (_switchEnabled ? _swColorActive : _swColorInactive)
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
        _switchEnabled ^= true;
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
