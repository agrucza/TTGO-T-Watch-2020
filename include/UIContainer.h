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
    UIESize_t                   _size;
    UIEAlignment_t              _alignment;
    std::vector<UIElement*>     _elements;
    uint8_t                     _padding = 5;
    void                        _setDimensions(){};

    public:
        UIContainer(UIContainer* parent = nullptr, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        UIContainer(UIScreen* screen, UIESize_t size = SIZE_ELEMENT, UIEAlignment_t alignment = ALIGNMENT_VERTICAL);
        void            addUIElement(UIElement* element);
        UIDimensions_t  getElementDimensions(UIElement* element);
        uint8_t         getPadding(){return _padding;};
        void            setPadding(uint8_t padding){_padding = padding;};
        UIEAlignment_t  getAlignment(){return _alignment;};
        
        UIDimensions_t  calculateContentSize(bool passToParent = false);
        bool            touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType);
        void            draw(bool task = false);
        void            reDraw();
};

#endif /*__UICONTAINER_H */
