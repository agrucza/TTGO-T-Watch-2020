#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementButton.h"

#include "GUI.h"
#include "UIContainer.h"

UIElementButton::UIElementButton(String label, const GFXfont* font, UIContainer* parent, UIESize_t size)
:UIElement(parent)
{
    _label  = label;
    _font   = font;
    _size   = size;
    _setDimensions();
}

void UIElementButton::_setDimensions()
{
    _tft->setFreeFont(_font);
    _dimensions                 = _parent->getDimensions();
    _dimensions.topLeft.x       += _parent->getPadding();
    _dimensions.topLeft.y       += _parent->getPadding();
    _dimensions.bottomRight.x   -= 2*_parent->getPadding();
    _dimensions.bottomRight.y   =  _tft->fontHeight()+4;
    switch(_size)
    {
        case SIZE_ELEMENT:
            _dimensions.bottomRight.x = _tft->textWidth(_label) + _padding*2;
        break;
        case SIZE_FULL:
        break;
    }
}

void UIElementButton::draw(bool task)
{
    if(!task)
    {
        if(_parent->getSprite()->created())
        {
            //Serial.println("Button: parent sprite detected - draw on sprite");
            TFT_eSprite* sprite = _parent->getSprite();
            sprite->setTextDatum(MC_DATUM);
            //Serial.println("setting font");
            sprite->setFreeFont(_font);
            //Serial.println("setting text color");
            sprite->setTextColor(_textColor);
            // input outline
            //Serial.println("drawing outline");
            sprite->fillRoundRect(
                _dimensions.topLeft.x - _parent->getPadding(),
                _dimensions.topLeft.y - _parent->getPadding(),
                _dimensions.bottomRight.x,
                _dimensions.bottomRight.y,
                4,
                (_active?_colorActive:_colorInactive)
            );

            //Serial.println("drawing string");
            sprite->drawString(
                _label,
                _dimensions.topLeft.x + (_dimensions.bottomRight.x/2) - _parent->getPadding(),
                _dimensions.topLeft.y + (sprite->fontHeight()/2) - _parent->getPadding()
            );
        }
        else
        {
            UIPoint_t absPos = getTopPosition();
            _tft->setFreeFont(_font);
            _tft->setTextColor(_textColor);
            // input outline
            _tft->fillRoundRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,4,(_active?_colorActive:_colorInactive));
            _tft->drawString(_label,absPos.x + (_dimensions.bottomRight.x/2),absPos.y + (_tft->fontHeight()/2));
        }
    }
}

bool UIElementButton::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
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
