/**
    This is the UIElement class
    @file UIElement.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UIELEMENT_H
#define __UIELEMENT_H

#include <Arduino.h>

#include "libraries\Adafruit-GFX-Library\gfxfont.h"

#include "UITypes.h"
#include "TouchMetrics.h"
#include "UIColors.h"
#include "App.h"

class TFT_eSPI;
class TFT_eSprite;

class UIElement{
    protected:
        TFT_eSPI*           _tft;
        App*                _app    = nullptr;
        UIContainer*        _parent = nullptr;

        String              _name   = "";
        
        const GFXfont*      _font;
        uint16_t            _textColor;
        uint16_t            _bgColor            = 0;
        uint16_t            _colorActive        = FLAT_UI_V1_PETER_RIVER;
        uint16_t            _colorActiveBg      = FLAT_UI_V1_BELIZE_HOLE;
        uint16_t            _colorInactive      = FLAT_UI_V1_SILVER;
        uint16_t            _colorInactiveBg    = FLAT_UI_V1_ASBESTOS;
        UIESize_t           _size;
        bool                _enabled;
        bool                _active             = false;

        UIEOrientation_t    _orientation;
        UIDimensions_t      _dimensions;
        UIDimensions_t      _parentDimensions;
        virtual void        _setDimensions() = 0;

        ui_event_cb_t       _eventCallback = nullptr;
        ui_event_data_t     _eventData;
    public:
        UIElement(UIContainer* parent = nullptr, UIEOrientation_t orientation = ORIENTATION_CENTER);
        String                  getName(){return _name;};

        UIDimensions_t          getDimensions(){return _dimensions;};
        void                    setDimensions(UIDimensions_t dimensions){_dimensions = dimensions;};
        void                    setEventData(ui_event_data_t* data);
        void                    setEventCallback(ui_event_cb_t eventCallback){_eventCallback = eventCallback;};
        
        void                    setBackgroundColor(int16_t color){_bgColor = color;};
        uint16_t                getBackgroundColor(){return _bgColor;};
        void                    setTextColor(uint16_t color){_textColor = color;};
        void                    setEnabled(bool enable){_enabled = enable;};
        bool                    getEnabled(){return _enabled;};
        
        UIPoint_t               getTopPosition();
        bool                    isWithinDimensions(int x, int y);
        bool                    hasActiveSprite(){return false;};
        bool                    isDrawable();

        virtual bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType) = 0;
        virtual void            draw(bool task = false) = 0;
        virtual void            reDraw(bool recursive = false) = 0;
};

#endif /*__UIELEMENT_H */
