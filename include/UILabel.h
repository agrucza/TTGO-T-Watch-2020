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
#include "gfxfont.h"

class GUI;
class TFT_esPI;

enum screens_t : uint8_t;

class UILabel : public UIElement{
    String          _label;
    const GFXfont*  _font;
    UIColor_t       _fgColor;
    UIColor_t       _bgColor;
    void            _setDimensions();

    public:
        UILabel(String label, const GFXfont* font, UIContainer* parent = NULL, UIEOrientation_t orientation = CENTER_CENTER);
        void    setFont(const GFXfont* font){_font = font;};
        void    setTextColor(uint8_t r, uint8_t g, uint8_t b);
        void    setBackgroundColor(int16_t r, int16_t g, int16_t b);
        void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    draw(bool task = false);
        void    reDraw();
};

#endif /*__UILABEL_H */
