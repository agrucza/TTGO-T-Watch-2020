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
            _dimensions.bottomRight.x = _tft->textWidth(_label) + 2*_padding;
        break;
        default:
            _dimensions.bottomRight.x = _parent->_dimensions.bottomRight.x - 2*_parent->getPadding();
        break;
    }
}

void UIElementButton::draw(bool task)
{
    if(!task)
    {
        TFT_eSPI* target;
        UIPoint_t absPos;

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
        
        // check if the elements needs to be drawn at all
        if(isDrawable())
        {
            target->setFreeFont(_font);
            target->setTextColor(_textColor);
            // input outline
            target->fillRoundRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,4,(_active?_colorActive:_colorInactive));
            target->drawString(_label,absPos.x + (_dimensions.bottomRight.x/2), absPos.y + (_dimensions.bottomRight.y/2));
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
