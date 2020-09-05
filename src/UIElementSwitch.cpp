#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementSwitch.h"

#include "GUI.h"
#include "UIContainer.h"

UIElementSwitch::UIElementSwitch(String label, const GFXfont* font, UIContainer* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label              = label;
    _font               = font;
    _setDimensions();
}

void UIElementSwitch::_setDimensions()
{
    _tft->setFreeFont(_font);

    _switchSize                 = _tft->fontHeight() * 2;

    _dimensions                 = _parent->getDimensions();
    _dimensions.topLeft.x       += _parent->getPadding();
    _dimensions.topLeft.y       += _parent->getPadding();
    _dimensions.bottomRight.x   -= 2*_parent->getPadding();
    _dimensions.bottomRight.y   = _tft->fontHeight();
    _paddingInner               = _dimensions.bottomRight.x - _tft->textWidth(_label) - _switchSize;
}

void UIElementSwitch::draw(bool task)
{
    if(!task)
    {
        TFT_eSPI* target;
        UIPoint_t absPos;
        UIPoint_t posSwitchE;
        uint16_t textWidth,textHeight;

        if(_parent->getSprite()->created())
        {
            target = _parent->getSprite();
            absPos = _dimensions.topLeft;
            absPos.x -= _parent->getPadding() + _parent->getSpritePos().x;
            absPos.y -= _parent->getPadding() + _parent->getSpritePos().y;
        }
        else
        {
            target = _tft;
            absPos = getTopPosition();
        }

        target->setFreeFont(_font);
        target->setTextColor(_textColor);

        textWidth   = target->textWidth(_label);
        textHeight  = target->fontHeight();

        target->drawString(
            _label,
            absPos.x + (_orientation == ORIENTATION_LEFT?_dimensions.bottomRight.x - textWidth/2:textWidth/2),
            absPos.y + (_dimensions.bottomRight.y/2)
        );

        posSwitchE.x = absPos.x + (_orientation == ORIENTATION_RIGHT?textWidth + _paddingInner:0);
        posSwitchE.y = absPos.y;

        // switch outline
        target->fillRoundRect(
            posSwitchE.x,
            posSwitchE.y,
            _switchSize,
            textHeight,
            textHeight/2,
            (_enabled ? _colorActiveBg : _colorInactiveBg)
        );
        
        // switch element
        target->fillRoundRect(
            posSwitchE.x + (_enabled? _switchSize - (textHeight -8) - 4 : 4),
            posSwitchE.y + 4,
            textHeight - 8,
            textHeight - 8,
            (textHeight-8)/2,
            (_enabled ? _colorActive : _colorInactive)
        );
    }
}

bool UIElementSwitch::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch (touchType)
    {
    case TouchMetrics::TOUCH_RELEASE:
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
