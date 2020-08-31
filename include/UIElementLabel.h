/**
    This is the UIlementELabel class
    @file UIElementLabel.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UIELEMENTLABEL_H
#define __UIELEMENTLABEL_H

#include <Arduino.h>
#include "UITypes.h"
#include "UIElement.h"
#include "gfxfont.h"

class GUI;
class TFT_esPI;

class UIElementLabel : public UIElement{
    String          _label;
    const GFXfont*  _font;
    uint16_t        _fgColor;
    void            _setDimensions();

    public:
        UIElementLabel(String label, const GFXfont* font, UIElement* parent = nullptr, UIEOrientation_t orientation = CENTER_CENTER);
        void    setFont(const GFXfont* font){_font = font;};
        void    setTextColor(uint16_t color){_fgColor = color;};
        bool    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    draw(bool task = false);
        void    reDraw();
};

#endif /*__UIELEMENTLABEL_H */
