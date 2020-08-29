#include "config.h"
#include "LilyGoWatch.h"
#include "UIContainer.h"
#include "UIElement.h"
#include "GUI.h"

UIContainer::UIContainer(UIElement* parent, UIEAlignment_t alignment)
:UIElement(parent)
{
    Serial.println("UIContainer constructor");
    _type = UIETYPE_CONTAINER;
    _alignment  = alignment;

    Serial.println("Setting container dimensions");
    if(_parent == nullptr)
    {
        Serial.println("Container has no parent");
        Serial.println("Dimensions will be screen dimensions");
        _dimensions.topLeft.x       = _dimensions.topLeft.y = 0;
        _dimensions.bottomRight.x   = TFT_WIDTH;
        _dimensions.bottomRight.y   = TFT_HEIGHT;
    }
    else
    {
        Serial.println("Container has parent");
        Serial.println("Dimensions will be parents inner dimensions");
        UIDimensions_t dim          = _parent->getDimensions();
        _dimensions.topLeft.x       = dim.topLeft.x + _padding;
        _dimensions.topLeft.y       = dim.topLeft.y + _padding;
        _dimensions.bottomRight.x   = dim.bottomRight.x - 2*_padding;
        _dimensions.bottomRight.y   = dim.bottomRight.y - 2*_padding;
    }
    
    Serial.println("Setting containers inner dimensions");
    _dimensionsInner = _dimensions;
    _dimensionsInner.topLeft.x += _padding;
    _dimensionsInner.topLeft.y += _padding;
    _dimensionsInner.bottomRight.x -= 2*_padding;
    _dimensionsInner.bottomRight.y -= 2*_padding;
    Serial.println("UIContainer constructor done");
}

void UIContainer::addUIElement(UIElement* element)
{
    UIDimensions_t      dimensions = element->getDimensions();
    UIDimensions_t      tmpDimensions;
    uint16_t            size = 0;

    // to calculate the orientation bounds we need to know if the size of all elements
    for(uint8_t i = 0; i <= _elements.size(); i++)
    {
        if(i < _elements.size())
        {
            tmpDimensions = _elements[i]->getDimensions();
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
        tmpDimensions = _elements[i]->getDimensions();
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
        _elements[i]->setDimensions(tmpDimensions);
    }

    element->setDimensions(dimensions);
    
    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            dimensions.topLeft.y += tmpDimensions.bottomRight.y;
            break;
        case ALIGNMENT_HORIZONTAL:
            dimensions.topLeft.x += tmpDimensions.bottomRight.x + 1;
            break;

    }
    _elements.push_back(element);
}

UIDimensions_t UIContainer::getElementDimensions(UIElement* element)
{
    UIDimensions_t fallback;

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        if(_elements[i] == element)
        {
            return _elements[i]->getDimensions();
        }
    }

    fallback.topLeft.x = fallback.topLeft.y = fallback.bottomRight.x = fallback.bottomRight.y -1;

    return fallback;
}

void UIContainer::draw(bool task)
{
    //container have priority in processing
    if(_elements.size()>0)
    {
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element]->draw(task);
        }
    }
}

void UIContainer::reDraw()
{

}

bool UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    UIDimensions_t dim;

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        dim = _elements[i]->getDimensions();
        if(
            lastX >= dim.topLeft.x
            && lastX <= dim.topLeft.x + dim.bottomRight.x
            && lastY >= dim.topLeft.y
            && lastY <= dim.topLeft.y + dim.bottomRight.y
        )
        {
            return _elements[i]->touchAction(lastX, lastY, deltaX, deltaY, touchType);
        }
    }

    // if we are here we have a container touch
    return true;
}