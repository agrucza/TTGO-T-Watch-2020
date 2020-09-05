/**
    This is the UIElementButton class
    @file UIElementTextInput.h
    @author Alexander Grucza
    @version 0.1 9/01/2020
*/

#ifndef __UIELEMENTBUTTON_H
#define __UIELEMENTBUTTON_H

#include <Arduino.h>

#include "gfxfont.h"

#include "UITypes.h"
#include "UIColors.h"
#include "UIElement.h"

class GUI;
class TFT_esPI;

class UIElementButton : public UIElement{
    String          _label;
    uint8_t         _padding = 10;
    void            _setDimensions();

    public:
        UIElementButton(String label, const GFXfont* font, UIContainer* parent = nullptr, UIESize_t size = SIZE_FULL);
        bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void            draw(bool task = false);
        void            reDraw(bool recursive = false){};
};

#endif /*__UIELEMENTBUTTON_H */
