/**
    This is the UIElement class
    @file UIElement.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UIELEMENT_H
#define __UIELEMENT_H

#include <Arduino.h>
#include "UITypes.h"
#include "TouchMetrics.h"
#include "UIColors.h"
#include "UIScreen.h"

class TFT_eSPI;
class TFT_eSprite;

class UIElement{
    public:
        TFT_eSPI*           _tft;
        UIScreen*           _screen = nullptr;
        UIElement*          _parent = nullptr;
        uint16_t            _bgColor;
        UIEOrientation_t    _orientation;
        UIDimensions_t      _dimensions;
        UIDimensions_t      _dimensionsInner;
        UIDimensions_t      _parentDimensions;
        UIDimensions_t      _remainingSpace;
        TFT_eSprite*        _sprite = nullptr;
        virtual void        _setDimensions() = 0;

        ui_event_cb_t       _eventCallback = nullptr;
        ui_event_data_t     _eventData;

        UIElement(UIElement* parent = nullptr, UIEOrientation_t orientation = CENTER_CENTER);
        void                setBackgroundColor(int16_t color){_bgColor = color;};
        UIDimensions_t      getDimensions(){return _dimensions;};
        void                setDimensions(UIDimensions_t dimensions){_dimensions = dimensions;};
        UIDimensions_t      getDimensionsInner(){return _dimensionsInner;};
        UIDimensions_t      getRemainingSpace(){return _remainingSpace;};
        void                setEventData(ui_event_data_t* data);
        void                setEventCallback(ui_event_cb_t eventCallback){_eventCallback = eventCallback;};
        virtual bool        touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType) = 0;
        virtual void        draw(bool task = false) = 0;
        virtual void        reDraw() = 0;
};

#endif /*__UIELEMENT_H */
