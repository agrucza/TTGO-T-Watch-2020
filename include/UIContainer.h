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
    std::vector<UIElement*>     _elements;
    uint8_t                     _padding                = 5;
    UIPoint_t                   _fullSize               = {0,0};
    TFT_eSprite                 _sprite                 = TFT_eSprite(_tft);
    uint16_t*                   _spriteData             = nullptr;
    UIPoint_t                   _spritePosOld           = {0,0};
    UIPoint_t                   _spritePos              = {0,0};
    UIPoint_t                   _spritePosMax           = {0,0};
    struct{
        bool x = true;
        bool y = true;
    } _spritePosMaxReached;
    void                        _setDimensions(){};
    void                        _pushSpriteRect(int16_t tftX, int16_t tftY, uint16_t spriteX, uint16_t spriteY, uint16_t spriteW, uint16_t spriteH);

    public:
        UIContainer(UIContainer* parent = nullptr, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        UIContainer(UIScreen* screen, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        void            addUIElement(UIElement* element);
        UIDimensions_t  getElementDimensions(UIElement* element);
        uint8_t         getPadding(){return _padding;};
        void            setPadding(uint8_t padding){_padding = padding;};
        UIEAlignment_t  getAlignment(){return _alignment;};
        
        UIDimensions_t  calculateContentSize(bool passToParent = false);
        TFT_eSprite*    getSprite(){return &_sprite;};
        bool            hasActiveSprite(){return _sprite.created();};
        bool            isWithinDimensions(int x, int y);

        bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void            draw(bool task = false);
        void            reDraw();
};

#endif /*__UICONTAINER_H */
