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

class TFT_eSPI;
class TFT_eSprite;

class UIElement{
    public:
        TFT_eSPI*           _tft;
        UIElement_t         _type = UIETYPE_ELEMENT;
        UIElement*          _parent;
        UIEOrientation_t    _orientation;
        UIDimensions_t      _dimensions;
        UIDimensions_t      _dimensionsInner;
        UIDimensions_t      _parentDimensions;
        TFT_eSprite*        _sprite;
        virtual void        _setDimensions() = 0;

        UIElement(UIElement* parent = NULL, UIEOrientation_t orientation = CENTER_CENTER);
        UIDimensions_t      getDimensions(){return _dimensions;};
        void                setDimensions(UIDimensions_t dimensions){_dimensions = dimensions;};
        UIDimensions_t      getDimensionsInner(){return _dimensionsInner;};
        virtual bool        touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType) = 0;
        virtual void        draw(bool task = false) = 0;
        virtual void        reDraw() = 0;
};

#endif /*__UIELEMENT_H */
