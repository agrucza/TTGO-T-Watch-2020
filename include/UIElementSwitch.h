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
#include "gfxfont.h"

class GUI;
class TFT_esPI;

class UIElementSwitch : public UIElement{
    String          _label;
    const GFXfont*  _font;
    uint16_t        _textColor;
    uint16_t        _bgColor;
    uint16_t        _swColorActive      = FLAT_UI_V1_PETER_RIVER;
    uint16_t        _swColorActiveBg    = FLAT_UI_V1_BELIZE_HOLE;
    uint16_t        _swColorInactive    = FLAT_UI_V1_SILVER;
    uint16_t        _swColorInactiveBg  = FLAT_UI_V1_ASBESTOS;
    uint8_t         _paddingInner;
    uint8_t         _switchSize;
    bool            _switchEnabled;
    void            _setDimensions();

    public:
        UIElementSwitch(String label, const GFXfont* font, UIElement* parent = nullptr, UIEOrientation_t orientation = ORIENTATION_CENTER);
        void    setTextColor(uint16_t color){_textColor = color;};
        void    setBackgroundColor(uint16_t color){_bgColor = color;};
        void    setEnabled(bool enable){_switchEnabled = enable;};
        bool    getEnabled(){return _switchEnabled;};
        bool    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void    draw(bool task = false);
        void    reDraw();
};

#endif /*__UIELEMENTSWITCH_H */
