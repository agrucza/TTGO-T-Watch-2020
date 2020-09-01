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
    String              _label;
    bool                _showLine = false;
    UIEOrientation_t    _lineOrientation;
    uint8_t             _lineHeight = 2;
    void                _setDimensions();

    public:
        UIElementLabel(String label, const GFXfont* font, UIElement* parent = nullptr, UIEOrientation_t orientation = ORIENTATION_CENTER);
        void    setFont(const GFXfont* font){_font = font;};
        void    setTextColor(uint16_t color){_textColor = color;};
        void    showLine(bool show, UIEOrientation_t orientation = ORIENTATION_CENTER){_showLine = show; _lineOrientation = orientation; _setDimensions();};
        bool    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    draw(bool task = false);
        void    reDraw();
};

#endif /*__UIELEMENTLABEL_H */
