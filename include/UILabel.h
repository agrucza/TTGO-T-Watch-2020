/**
    This is the UILabel class
    @file UILabel.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UILABEL_H
#define __UILABEL_H

#include <Arduino.h>
#include "UITypes.h"
#include "UIElement.h"

#define LOAD_GFXFF

#include "TFT_eSPI/Fonts/GFXFF/gfxfont.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;

class UILabel : public UIElement{
    char*           _label;
    const GFXfont*  _font;
    UIColor_t       _fgColor;
    UIColor_t       _bgColor;

    public:
        UILabel(char* label, const GFXfont* font, UIContainer *parent = NULL, UIEOrientation_t orientation = CENTER_CENTER, UIESize_t sizeX = FULL, UIESize_t sizeY = ELEMENT);
        void    setFont(const GFXfont* font){_font = font;};
        void    setTextColor(uint8_t r, uint8_t g, uint8_t b){
            _fgColor.r  = r;
            _fgColor.g  = g;
            _fgColor.b  = b;
        };
        void    setBackgroundColor(int16_t r, int16_t g, int16_t b){
            _bgColor.r  = r;
            _bgColor.g  = g;
            _bgColor.b  = b;
        };
        void    draw(bool task = false);
        void    reDraw();
};

#endif /*__UILABEL_H */
