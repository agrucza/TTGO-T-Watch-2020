/**
    This is the UIContainer class
    @file UIContainer.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UICONTAINER_H
#define __UICONTAINER_H

#include <Arduino.h>

#include "UITypes.h"
#include "UIElement.h"

extern UIDimensions_t   defaultUIDimensions;
extern UIPoint_t        defaultUIPoint;

class UIContainer : public UIElement{
    protected:
        struct{
            bool x = true;
            bool y = true;
        } _spritePosMaxReached;
        
        UIEAlignment_t          _alignment;
        uint8_t                 _padding                = 5;
        std::vector<UIElement*> _elements;
        int16_t                 _drawElement            = -1;
        UIPoint_t               _elementSize            = defaultUIPoint;
        TFT_eSprite             _sprite                 = TFT_eSprite(_tft);
        uint16_t*               _spriteData             = nullptr;
        UIPoint_t               _spritePosOld           = defaultUIPoint;
        UIPoint_t               _spritePos              = defaultUIPoint;
        UIPoint_t               _spritePosMax           = defaultUIPoint;
        uint8_t                 _spriteBottomSafety     = 32;
        void                    _setDimensions(){};
        void                    _pushSprite();

    public:
        UIContainer(UIContainer* parent = nullptr, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        UIContainer(App* app, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        UIEAlignment_t          getAlignment(){return _alignment;};
        std::vector<UIElement*> getElements(){return _elements;};
        UIElement*              getElementByName(String name);
        void                    setDrawElement(int16_t element){_drawElement = element;};
        
        uint8_t                 getPadding(){return _padding;};
        void                    setPadding(uint8_t padding){_padding = padding;};

        void                    addUIElement(UIElement* element);
        
        TFT_eSprite*            getSprite(){return &_sprite;};
        UIPoint_t               getSpritePos(){return _spritePos;};
        bool                    hasActiveSprite(){return _sprite.created();};
        bool                    isWithinDimensions(int x, int y);
        bool                    acceptsTouchType(TouchMetrics::touch_t touchType);
        void                    clean();
        UIPoint_t               getNextElementPosition();
        void                    calculateSize();

        bool                    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void                    draw(bool task = false);
        void                    reDraw(bool recursive = false);
};

#endif /*__UICONTAINER_H */
