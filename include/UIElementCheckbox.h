/**
    This is the UIElementCheckbox class
    @file UIElementTextInput.h
    @author Alexander Grucza
    @version 0.1 9/01/2020
*/

#ifndef __UIELEMENTCHECKBOX_H
#define __UIELEMENTCHECKBOX_H

#include <Arduino.h>

#include "gfxfont.h"

#include "UITypes.h"
#include "UIColors.h"
#include "UIElement.h"

class GUI;
class TFT_esPI;

class UIElementCheckbox : public UIElement{
    String          _label;
    String          _text;
    void            _setDimensions();

    public:
        UIElementCheckbox(String label, const GFXfont* font, UIContainer* parent = nullptr, UIEOrientation_t orientation = ORIENTATION_RIGHT);
        bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void            draw(bool task = false);
        void            reDraw();
};

#endif /*__UIELEMENTCHECKBOX_H */
