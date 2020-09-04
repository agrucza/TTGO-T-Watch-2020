#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementCheckbox.h"

#include "GUI.h"
#include "UIContainer.h"

UIElementCheckbox::UIElementCheckbox(String label, const GFXfont* font, UIContainer* parent, UIEOrientation_t orientation)
:UIElement(parent,orientation)
{
    _label              = label;
    _font               = font;
    _setDimensions();
}

void UIElementCheckbox::_setDimensions()
{
    _tft->setFreeFont(_font);
    _dimensions                 = _parent->getDimensions();
    _dimensions.topLeft.x       += _parent->getPadding();
    _dimensions.topLeft.y       += _parent->getPadding();
    _dimensions.bottomRight.x   -= 2*_parent->getPadding();
    _dimensions.bottomRight.y   = _tft->fontHeight()+4;
}

void UIElementCheckbox::draw(bool task)
{
    if(!task)
    {
        UIPoint_t absPos = getTopPosition();

        _tft->setFreeFont(_font);
        _tft->setTextColor((_active?_colorActive:_colorInactive));

        // input outline
        _tft->fillRoundRect(
            absPos.x + (_orientation == ORIENTATION_RIGHT? _dimensions.bottomRight.x - _tft->fontHeight():0),
            absPos.y,
            _tft->fontHeight(),
            _tft->fontHeight(),
            4,
            (_active ? _colorActive : _colorInactive)
        );

        _tft->drawString(
            _label,
            absPos.x + (_orientation == ORIENTATION_LEFT?_dimensions.bottomRight.x - (_tft->textWidth(_label)/2):_tft->textWidth(_label)/2),
            absPos.y + (_tft->fontHeight()/2)
        );

        if(_active)
        {
            _tft->setTextColor(FLAT_UI_V1_CLOUDS);
            _tft->drawString(
                "X",
                absPos.x + _tft->fontHeight()/2 + (_orientation == ORIENTATION_RIGHT? _dimensions.bottomRight.x - _tft->fontHeight():0),
                absPos.y + _tft->fontHeight()/2
            );
        }
    }
}

void UIElementCheckbox::reDraw()
{
    
}

bool UIElementCheckbox::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
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
