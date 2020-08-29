#include "UILabel.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UILabel::UILabel(String label, const GFXfont* font, UIContainer* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label          = label;
    _bgColor.r      = _bgColor.g = _bgColor.b = -1;
    _font           = font;
    _setDimensions();
}

void UILabel::_setDimensions()
{
    _tft->setFreeFont(_font);

    _dimensions                 = _parent->getDimensionsInner();
    _dimensions.bottomRight.y   = _tft->fontHeight();
    _dimensions.bottomRight.x   = _tft->textWidth(_label);
    
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

void UILabel::setTextColor(uint8_t r, uint8_t g, uint8_t b)
{
    _fgColor.r  = r;
    _fgColor.g  = g;
    _fgColor.b  = b;
}

void UILabel::setBackgroundColor(int16_t r, int16_t g, int16_t b)
{
    _bgColor.r  = r;
    _bgColor.g  = g;
    _bgColor.b  = b;
}

void UILabel::draw(bool task)
{
    if(!task)
    {
        _tft->setFreeFont(_font);
        _tft->setTextColor(_tft->color565(_fgColor.r,_fgColor.g,_fgColor.b));
    }

    _tft->drawString(_label,_dimensions.topLeft.x,_dimensions.topLeft.y);
}

void UILabel::reDraw()
{
    
}

bool UILabel::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    char buf[50];
    _tft->setFreeFont();
    sprintf(buf,"%d/%d %s x:%d y:%d w:%d h:%d", lastX, lastY, _label.c_str(), _dimensions.topLeft.x, _dimensions.topLeft.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y);
    _tft->fillRect(0, TFT_HEIGHT - _tft->fontHeight(), TFT_WIDTH, _tft->fontHeight(), TFT_BLACK);
    _tft->drawString(buf,0, TFT_HEIGHT - _tft->fontHeight());
    return true;
}
