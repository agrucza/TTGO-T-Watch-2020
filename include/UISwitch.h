/**
    This is the UISwitch class
    @file UISwitch.h
    @author Alexander Grucza
    @version 0.1 8/29/2020
*/

#ifndef __UISWITCH_H
#define __UISWITCH_H

#include <Arduino.h>
#include "UITypes.h"
#include "UIElement.h"
#include "gfxfont.h"

class GUI;
class TFT_esPI;

class UISwitch : public UIElement{
    String          _label;
    const GFXfont*  _font;
    uint16_t        _textColor;
    uint16_t        _bgColor;
    uint16_t        _swColorActive;
    uint16_t        _swColorInactive;
    uint8_t         _paddingInner;
    uint8_t         _switchSize;
    bool            _switchEnabled;
    void            _setDimensions();

    public:
        UISwitch(String label, const GFXfont* font, UIElement* parent = nullptr, UIEOrientation_t orientation = CENTER_CENTER);
        void    setTextColor(uint16_t color){_textColor = color;};
        void    setBackgroundColor(uint16_t color){_bgColor = color;};
        void    setEnabled(bool enable){_switchEnabled = enable;};
        bool    getEnabled(){return _switchEnabled;};
        bool    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    draw(bool task = false);
        void    reDraw();
};

#endif /*__UISWITCH_H */
