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
#include "UIContainer.h"

class TFT_eSPI;
class TFT_eSprite;

class UIElement{
    protected:
        TFT_eSPI*           _tft;
        UIContainer*        _parent;
        UIEOrientation_t    _orientation;
        UIESize_t           _sizeX;
        UIESize_t           _sizeY;
        UIDimensions_t      _dimension;
        UIDimensions_t      _dimensions;
        UIDimensions_t      _parentDimensions;
        TFT_eSprite*        _sprite;
        virtual void        _setDimensions() = 0;
    public:
        UIElement(UIContainer* parent = NULL, UIEOrientation_t orientation = CENTER_CENTER);
        UIDimensions_t      getDimensions(){return _dimensions;};
        void                setDimensions(UIDimensions_t dimensions){_dimensions = dimensions;};
        UIPoint_t           getTopLeft(){return _dimensions.topLeft;}
        void                setTopLeft(UIPoint_t topLeft){_dimensions.topLeft = topLeft;};
        UIPoint_t           getBottomRight(){return _dimensions.bottomRight;};
        void                setOrientation(UIEOrientation_t orientation){_orientation = orientation;};
        UIEOrientation_t    getOrientation(){return _orientation;};
        virtual void        touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType) = 0;
        virtual void        draw(bool task = false) = 0;
        virtual void        reDraw() = 0;
};

#endif /*__UIELEMENT_H */
