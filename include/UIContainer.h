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

extern UIDimensions_t defaultUIDimensions;

class UIContainer : public UIElement{
    UIEAlignment_t              _alignment;
    uint8_t                     _padding                = 5;
    std::vector<UIElement*>     _elements;
    UIPoint_t                   _elementSize            = {0,0};
    TFT_eSprite                 _sprite                 = TFT_eSprite(_tft);
    uint16_t*                   _spriteData             = nullptr;
    UIPoint_t                   _spritePosOld           = {0,0};
    UIPoint_t                   _spritePos              = {0,0};
    UIPoint_t                   _spritePosMax           = {0,0};
    uint8_t                     _spriteBottomSafety     = 32;
    struct{
        bool x = true;
        bool y = true;
    } _spritePosMaxReached;
    void                        _setDimensions(){};
    void                        _pushSprite();

    public:
        UIContainer(UIContainer* parent = nullptr, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        UIContainer(App* app, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        void            addUIElement(UIElement* element);
        uint8_t         getPadding(){return _padding;};
        void            setPadding(uint8_t padding){_padding = padding;};
        UIEAlignment_t  getAlignment(){return _alignment;};
        
        TFT_eSprite*    getSprite(){return &_sprite;};
        UIPoint_t       getSpritePos(){return _spritePos;};
        bool            hasActiveSprite(){return _sprite.created();};
        bool            isWithinDimensions(int x, int y);
        bool            acceptsTouchType(TouchMetrics::touch_t touchType);
        void            clean();
        UIPoint_t       getNextElementPosition();
        void            calculateSize();

        bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void            draw(bool task = false);
        void            reDraw(bool recursive = false);
};

#endif /*__UICONTAINER_H */
