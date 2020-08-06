#include "UILabel.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI gui;

UILabel::UILabel(char* label, const GFXfont *font, UIContainer *parent, UIEOrientation_t orientation, UIESize_t sizeX, UIESize_t sizeY)
//:UIElement()
{
    _label          = label;
    _bgColor.r      = _bgColor.g = _bgColor.b = -1;
    _parent         = parent;
    _orientation    = orientation;
    _sizeX          = sizeX;
    _sizeY          = sizeY;
    _tft            = gui.getTFT();
    _font           = font;
    
    _tft->setFreeFont(_font);

    _dimensions.topLeft.x       = -1;
    _dimensions.topLeft.y       = -1;
    _dimensions.bottomRight.x   = -1;
    _dimensions.bottomRight.y   = _tft->fontHeight();
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
