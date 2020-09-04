#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementLabel.h"

#include "GUI.h"
#include "UIContainer.h"

UIElementLabel::UIElementLabel(String label, const GFXfont* font, UIContainer* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label          = label;
    _font           = font;
    _setDimensions();
}

void UIElementLabel::_setDimensions()
{
    _tft->setFreeFont(_font);

    _dimensions                 = _parent->getDimensions();
    _dimensions.topLeft.x       += _parent->getPadding();
    _dimensions.topLeft.y       += _parent->getPadding();
    _dimensions.bottomRight.y   = _tft->fontHeight() + (_showLine?_lineHeight:0);
    _dimensions.bottomRight.x   = _tft->textWidth(_label);
    
    switch(_orientation)
    {
        case ORIENTATION_CENTER:
            _dimensions.topLeft.x += (_parent->getDimensions().bottomRight.x + _parent->getPadding()-_dimensions.bottomRight.x)/2;
            break;
        case ORIENTATION_RIGHT:
            _dimensions.topLeft.x += _parent->getDimensions().bottomRight.x +_parent->getPadding() - _dimensions.bottomRight.x;
            break;
    }
}

void UIElementLabel::draw(bool task)
{
    if(!task)
    {
        UIPoint_t absPos = getTopPosition();

        _tft->setFreeFont(_font);
        _tft->setTextColor(_textColor);
        
        _tft->drawString(
            _label,
            absPos.x + _dimensions.bottomRight.x/2,
            absPos.y + _tft->fontHeight()/2
        );

        if(_showLine)
        {
            _tft->fillRect(
                _parent->getTopPosition().x,
                absPos.y + _dimensions.bottomRight.y - _lineHeight,
                _parent->_dimensions.bottomRight.x + (_lineOrientation == ORIENTATION_CENTER?(_parent)->getPadding():0),
                _lineHeight,
                _textColor
            );
        }
    }
}

bool UIElementLabel::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    char buf[50];
    _tft->setFreeFont();
    sprintf(
        buf,
        "%d/%d %s x:%d y:%d w:%d h:%d",
        lastX,
        lastY,
        _label.c_str(),
        _dimensions.topLeft.x,
        _dimensions.topLeft.y,
        _dimensions.bottomRight.x,
        _dimensions.bottomRight.y
    );
    _tft->fillRect(0, TFT_HEIGHT - _tft->fontHeight(), TFT_WIDTH, _tft->fontHeight(), TFT_BLACK);
    _tft->drawString(buf,0, TFT_HEIGHT - (_tft->fontHeight()/2));
    return true;
}
