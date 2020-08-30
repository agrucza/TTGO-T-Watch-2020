#include "UISwitch.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UISwitch::UISwitch(String label, const GFXfont* font, UIElement* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label              = label;
    _bgColor.r          = _bgColor.g = _bgColor.b = -1;
    _font               = font;
    _paddingInner       = 10;
    _switchEnabled      = false;
    _swColorActive      = _tft->color565(41,128,185); //#2980b9
    _swColorInactive    = _tft->color565(127,140,141); //#7f8c8d
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
        UIPoint_t posSwitchE;
        uint16_t textWidth,textHeight;

        _tft->setFreeFont(_font);
        _tft->setTextColor(_tft->color565(_textColor.r,_textColor.g,_textColor.b));

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
            _tft->color565(_textColor.r,_textColor.g,_textColor.b)
        );

        // switch inner
        _tft->fillRoundRect(
            posSwitchE.x + 2,
            posSwitchE.y + 2,
            _switchSize - 4,
            textHeight - 4,
            (textHeight-4)/2,
            _tft->color565(52,73,94) //#34495e
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

void UISwitch::reDraw()
{
    
}

bool UISwitch::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch (touchType)
    {
    case TouchMetrics::TOUCH:
        _switchEnabled ^= true;
        draw();
        break;
    
    default:
        break;
    }
    /*
    char buf[50];
    _tft->setFreeFont();
    sprintf(buf,"%d/%d %s x:%d y:%d w:%d h:%d", lastX, lastY, _label.c_str(), _dimensions.topLeft.x, _dimensions.topLeft.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y);
    _tft->fillRect(0, TFT_HEIGHT - _tft->fontHeight(), TFT_WIDTH, _tft->fontHeight(), TFT_BLACK);
    _tft->drawString(buf,0, TFT_HEIGHT - _tft->fontHeight());
    */
    return true;
}
