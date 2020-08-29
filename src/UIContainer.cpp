#include "config.h"
#include "LilyGoWatch.h"
#include "UIContainer.h"
#include "UIElement.h"
#include "GUI.h"

UIContainer::UIContainer(UIContainer* parent, UIEAlignment_t alignment)
{
    _parent     = parent;
    _alignment  = alignment;
    
    if(_parent == nullptr)
    {
        _dimensions.topLeft.x       = _dimensions.topLeft.y = 0;
        _dimensions.bottomRight.x   = TFT_WIDTH;
        _dimensions.bottomRight.y   = TFT_HEIGHT;
    }
    else
    {
        UIDimensions_t dim          = _parent->getDimensions();
        _dimensions.topLeft.x       = dim.topLeft.x + _padding;
        _dimensions.topLeft.y       = dim.topLeft.y + _padding;
        _dimensions.bottomRight.x   = dim.bottomRight.x - 2*_padding;
        _dimensions.bottomRight.y   = dim.bottomRight.y - 2*_padding;
    }
    _dimensionsInner = _dimensions;
    _dimensionsInner.topLeft.x += _padding;
    _dimensionsInner.topLeft.y += _padding;
    _dimensionsInner.bottomRight.x -= 2*_padding;
    _dimensionsInner.bottomRight.y -= 2*_padding;
}

void UIContainer::addUIContainer(UIContainer* container)
{
    UIContainerDetails_t details;
    details.container = container;
    _container.push_back(details);
}

void UIContainer::addUIElement(UIElement* element)
{
    UIElementDetails_t  newDetails;
    UIDimensions_t      dimensions = element->getDimensions();
    UIDimensions_t      tmpDimensions;
    uint16_t            size = 0;

    // to calculate the orientation bounds we need to know if the size of all elements
    for(uint8_t i = 0; i <= _elements.size(); i++)
    {
        if(i < _elements.size())
        {
            tmpDimensions = _elements[i].element->getDimensions();
        }
        else
        {
            tmpDimensions = element->getDimensions();
            size -= _padding;
        }

        switch(_alignment)
        {
            case ALIGNMENT_VERTICAL:
                size += tmpDimensions.bottomRight.y + _padding;
                break;
            case ALIGNMENT_HORIZONTAL:
                size += tmpDimensions.bottomRight.x + _padding;
                break;
        }
    }

    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            if(size > (_dimensions.bottomRight.y + (2*_padding)))
            {
                dimensions.topLeft.y = _padding;
            }
            else
            {
                dimensions.topLeft.y = _padding+((_dimensions.bottomRight.y-size)/2);
            }
            break;
        case ALIGNMENT_HORIZONTAL:
            if(size > (_dimensions.bottomRight.x + (2*_padding)))
            {
                dimensions.topLeft.x = 0;
            }
            else
            {
                dimensions.topLeft.x = _padding+((_dimensions.bottomRight.x-size)/2);
            }
            break;
    }

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        tmpDimensions = _elements[i].element->getDimensions();
        switch(_alignment)
        {
            case ALIGNMENT_VERTICAL:
                tmpDimensions.topLeft.y =  dimensions.topLeft.y;
                dimensions.topLeft.y    += tmpDimensions.bottomRight.y + 1;
                break;
            case ALIGNMENT_HORIZONTAL:
                tmpDimensions.topLeft.x =  dimensions.topLeft.x;
                dimensions.topLeft.x    += tmpDimensions.bottomRight.x + 1;
                break;
        }
        _elements[i].element->setDimensions(tmpDimensions);
    }

    element->setDimensions(dimensions);
    newDetails.element      = element;
    newDetails.dimensions   = dimensions;
    
    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            dimensions.topLeft.y += tmpDimensions.bottomRight.y;
            break;
        case ALIGNMENT_HORIZONTAL:
            dimensions.topLeft.x += tmpDimensions.bottomRight.x + 1;
            break;

    }
    _elements.push_back(newDetails);
}

UIDimensions_t UIContainer::getContainerDimensions(UIContainer* container)
{
    UIDimensions_t fallback;

    for(uint8_t i = 0; i < _container.size(); i++)
    {
        if(_container[i].container == container)
        {
            return _container[i].dimensions;
        }
    }

    fallback.topLeft.x = fallback.topLeft.y = fallback.bottomRight.x = fallback.bottomRight.y -1;

    return fallback;
}

UIDimensions_t UIContainer::getElementDimensions(UIElement* element)
{
    UIDimensions_t fallback;

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        if(_elements[i].element == element)
        {
            return _elements[i].dimensions;
        }
    }

    fallback.topLeft.x = fallback.topLeft.y = fallback.bottomRight.x = fallback.bottomRight.y -1;

    return fallback;
}

void UIContainer::draw(bool task)
{
    //container have priority in processing
    if(_container.size()>0)
    {
        for(uint8_t container = 0; container < _container.size(); container++)
        {

        }
    } else if(_elements.size()>0)
    {
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element].element->draw();
        }
    }
}

void UIContainer::reDraw()
{

}

void UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    bool eventDone = false;
    UIDimensions_t dim;

    for(uint8_t i = 0; i < _container.size(); i++)
    {
        dim = _container[i].dimensions;
        if(
            !eventDone
            && lastX >= dim.topLeft.x
            && lastX <= dim.topLeft.x + dim.bottomRight.x
            && lastY >= dim.topLeft.y
            && lastY <= dim.topLeft.y + dim.bottomRight.y
        )
        {
            _container[i].container->touchAction(lastX, lastY, deltaX, deltaY, touchType);
        }
    }

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        dim = _elements[i].dimensions;
        if(
            !eventDone
            && lastX >= dim.topLeft.x
            && lastX <= dim.topLeft.x + dim.bottomRight.x
            && lastY >= dim.topLeft.y
            && lastY <= dim.topLeft.y + dim.bottomRight.y
        )
        {
            _elements[i].element->touchAction(lastX, lastY, deltaX, deltaY, touchType);
        }
    }
}