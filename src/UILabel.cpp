#include "UILabel.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

UILabel::UILabel(String label, const GFXfont* font, UIContainer* parent)
{
    _label          = label;
    _bgColor.r      = _bgColor.g = _bgColor.b = -1;
    _font           = font;
    _setDimensions();
}

void UILabel::_setDimensions()
{
    _tft->setFreeFont(_font);

    //_dimensions                 = defaultUIDimensions;
    _dimensions.bottomRight.y   = _tft->fontHeight();
    _dimensions.bottomRight.x   = _tft->textWidth(_label);
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

void UILabel::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    char buf[50];
    _tft->setFreeFont();
    sprintf(buf,"touch: %s x:%d y:%d w:%d h:%d", _label, _dimensions.topLeft.x, _dimensions.topLeft.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y);
    _tft->fillRect(0, TFT_HEIGHT - _tft->fontHeight(), TFT_WIDTH, _tft->fontHeight(), TFT_BLACK);
    _tft->drawString(buf,0, TFT_HEIGHT - _tft->fontHeight());
}
