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

extern UIDimensions_t defaultUIDimensions;

class UIContainer;
class UIElement;

class UIContainer{
    UIContainer*                        _parent;
    UIEAlignment_t                      _alignment;
    std::vector<UIContainerDetails_t>   _container;
    std::vector<UIElementDetails_t>     _element;
    UIDimensions_t                      _dimensions;

    public:
        UIContainer(UIContainer* parent = NULL, UIEAlignment_t alignment = ALIGNMENT_VERTICAL, UIESize_t sizeX = FULL, UIESize_t sizeY = FULL, UIDimensions_t sizeGap = defaultUIDimensions);
        void            addUIContainer(UIContainer* container);
        void            addUIElement(UIElement* element);
        UIDimensions_t  getDimensions(){return _dimensions;};
        UIDimensions_t  getContainerDimensions(UIContainer* container);
        UIDimensions_t  getElementDimensions(UIElement* element);
        void            draw(bool task = false);
        void            reDraw();
};

#endif /*__UICONTAINER_H */
