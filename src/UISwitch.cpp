#include "UISwitch.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UISwitch::UISwitch(String label, const GFXfont* font, UIElement* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label          = label;
    _bgColor.r      = _bgColor.g = _bgColor.b = -1;
    _font           = font;
    _paddingInner   = 10;
    _setDimensions();
}

void UISwitch::_setDimensions()
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

void UISwitch::setTextColor(uint8_t r, uint8_t g, uint8_t b)
{
    _textColor.r  = r;
    _textColor.g  = g;
    _textColor.b  = b;
}

void UISwitch::setBackgroundColor(int16_t r, int16_t g, int16_t b)
{
    _bgColor.r  = r;
    _bgColor.g  = g;
    _bgColor.b  = b;
}

void UISwitch::draw(bool task)
{
    if(!task)
    {
        _tft->setFreeFont(_font);
        _tft->setTextColor(_tft->color565(_textColor.r,_textColor.g,_textColor.b));

        _tft->drawString(
            _label,
            _dimensions.topLeft.x + (_tft->textWidth(_label)/2),
            _dimensions.topLeft.y + (_dimensions.bottomRight.y/2)
        );

        _tft->fillRoundRect(
            _dimensions.topLeft.x + _tft->textWidth(_label) + _paddingInner,
            _dimensions.topLeft.y,
            _switchSize,
            _tft->fontHeight(),
            _tft->fontHeight()/2,
            _tft->color565(_textColor.r,_textColor.g,_textColor.b)
        );

        _tft->fillRoundRect(
            _dimensions.topLeft.x + _tft->textWidth(_label) + _paddingInner + 2,
            _dimensions.topLeft.y + 2,
            _switchSize - 4,
            _tft->fontHeight() - 4,
            (_tft->fontHeight()-4)/2,
            _tft->color565(52,73,94) //#34495e
        );
    }
}

void UISwitch::reDraw()
{
    
}

bool UISwitch::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    /*
    char buf[50];
    _tft->setFreeFont();
    sprintf(buf,"%d/%d %s x:%d y:%d w:%d h:%d", lastX, lastY, _label.c_str(), _dimensions.topLeft.x, _dimensions.topLeft.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y);
    _tft->fillRect(0, TFT_HEIGHT - _tft->fontHeight(), TFT_WIDTH, _tft->fontHeight(), TFT_BLACK);
    _tft->drawString(buf,0, TFT_HEIGHT - _tft->fontHeight());
    */
    return true;
}
