/**
    This is the UIElementTextInput class
    @file UIElementTextInput.h
    @author Alexander Grucza
    @version 0.1 9/01/2020
*/

#ifndef __UIELEMENTTEXTINPUT_H
#define __UIELEMENTTEXTINPUT_H

#include <Arduino.h>

#include "gfxfont.h"

#include "UITypes.h"
#include "UIColors.h"
#include "UIElement.h"

class GUI;
class TFT_esPI;

class UIElementTextInput : public UIElement{
    String          _placeholder;
    String          _text;
    void            _setDimensions();

    public:
        UIElementTextInput(String placeholder, const GFXfont* font, UIContainer* parent = nullptr, UIEOrientation_t orientation = ORIENTATION_CENTER);
        bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void            draw(bool task = false);
        void            reDraw(bool recursive = false){};
};

#endif /*__UIELEMENTTEXTINPUT_H */
