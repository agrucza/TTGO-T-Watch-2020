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
    _dimensions.bottomRight.y   =  _tft->fontHeight() + 6;
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
        // check if the elements needs to be drawn at all
        if(isDrawable())
        {
            UIPoint_t absPos;

            if(_parent->getSprite()->created())
            {
                TFT_eSprite* sprite = _parent->getSprite();
                absPos = _dimensions.topLeft;
                absPos.x -= _parent->getPadding() + _parent->getSpritePos().x;
                absPos.y -= _parent->getPadding() + _parent->getSpritePos().y;
                Serial.print("Button - dim: ");
                Serial.print(_dimensions.topLeft.x);
                Serial.print(":");
                Serial.print(_dimensions.topLeft.y);
                Serial.print(" pos: ");
                Serial.print(absPos.x);
                Serial.print(":");
                Serial.print(absPos.y);
                Serial.print(" spritePos: ");
                Serial.print(_parent->getSpritePos().x);
                Serial.print(":");
                Serial.print(_parent->getSpritePos().y);
                Serial.print(" Parent: ");
                Serial.print(_parent->_dimensions.topLeft.x);
                Serial.print(":");
                Serial.print(_parent->_dimensions.topLeft.y);
                Serial.print(":");
                Serial.print(_parent->_dimensions.bottomRight.x);
                Serial.print(":");
                Serial.println(_parent->_dimensions.bottomRight.y);
                
                sprite->setFreeFont(_font);
                sprite->setTextColor(_textColor);
                // input outline
                sprite->fillRoundRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,4,(_active?_colorActive:_colorInactive));
                sprite->drawString(_label,absPos.x + (_dimensions.bottomRight.x/2), absPos.y + (_dimensions.bottomRight.y/2));
            }
            else
            {
                absPos = getTopPosition();
                _tft->setFreeFont(_font);
                _tft->setTextColor(_textColor);
                // input outline
                _tft->fillRoundRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,4,(_active?_colorActive:_colorInactive));
                _tft->drawString(_label,absPos.x + (_dimensions.bottomRight.x/2), absPos.y + (_dimensions.bottomRight.y/2));
            }
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
