/**
    This is the UIElementSwitch class
    @file UIElementSwitch.h
    @author Alexander Grucza
    @version 0.1 8/29/2020
*/

#ifndef __UIELEMENTSWITCH_H
#define __UIELEMENTSWITCH_H

#include <Arduino.h>

#include "UITypes.h"
#include "UIColors.h"
#include "UIElement.h"

class GUI;
class TFT_esPI;

class UIElementSwitch : public UIElement{
    String      _label;
    uint8_t     _paddingInner;
    uint8_t     _switchSize;
    void        _setDimensions();

    public:
        UIElementSwitch(String label, const GFXfont* font, UIContainer* parent = nullptr, UIEOrientation_t orientation = ORIENTATION_RIGHT);
        bool    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    draw(bool task = false);
        void    reDraw(bool recursive = false){};
};

#endif /*__UIELEMENTSWITCH_H */
