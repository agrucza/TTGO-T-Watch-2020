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
        UIDimensions_t      _sizeGap;
        UIDimensions_t      _dimensions;
        TFT_eSprite*        _sprite;
    public:
        UIElement(UIContainer* parent = NULL, UIEOrientation_t orientation = CENTER_CENTER, UIESize_t sizeX = FULL, UIESize_t sizeY = ELEMENT, UIDimensions_t sizeGap = defaultUIDimensions);
        ~UIElement(){};
        UIDimensions_t      getDimensions(){return _dimensions;};
        void                setDimensions(UIDimensions_t dimensions){_dimensions = dimensions;};
        UIPoint_t           getTopLeft(){return _dimensions.topLeft;}
        void                setTopLeft(UIPoint_t topLeft){_dimensions.topLeft = topLeft;};
        UIPoint_t           getBottomRight(){return _dimensions.bottomRight;}
        UIEOrientation_t    getOrientation(){return _orientation;};
        virtual void        draw(bool task = false) = 0;
        virtual void        reDraw() = 0;
};

#endif /*__UIELEMENT_H */