#include "config.h"
#include "LilyGoWatch.h"

#include "UIContainer.h"

#include "GUI.h"
#include "UIElement.h"
#include "UIElementLabel.h"

UIContainer::UIContainer(UIContainer* parent, UIESize_t size, UIEAlignment_t alignment)
:UIElement(parent)
{
    Serial.println("UIContainer constructor");
    _size       = size;
    _alignment  = alignment;
    
    //Serial.println("Setting container dimensions");
    if(_parent)
    {
        Serial.println("Container has parent");
        // the parents dimensions plus padding will be the bounds of the new container
        // depending on the parens alignment we will set the width and height
        // vertical alignment will have full width but 0 height
        // horizontal alignment will have 0 width and full height
        _dimensions = _parent->getDimensions();
        _dimensions.topLeft.x += _parent->getPadding();
        _dimensions.topLeft.y += _parent->getPadding();
        _dimensions.bottomRight.x -= 2*_parent->getPadding();
        _dimensions.bottomRight.y -= 2*_parent->getPadding();

        switch(_parent->getAlignment())
        {
            case ALIGNMENT_VERTICAL:
                _dimensions.bottomRight.y = 2*_padding;
                break;
            case ALIGNMENT_HORIZONTAL:
            case ALIGNMENT_HORIZONTAL_FILL:
                _dimensions.bottomRight.x -= 2*_padding;
                break;
        }
    }
    else
    {
        Serial.println("Container has no parent");
        _dimensions.topLeft.x       = _dimensions.topLeft.y = 0;
        _dimensions.bottomRight.x   = TFT_WIDTH;
        _dimensions.bottomRight.y   = TFT_HEIGHT;
    }

    //Serial.println("UIContainer constructor done");
}

UIContainer::UIContainer(UIScreen* screen, UIESize_t size, UIEAlignment_t alignment)
:UIContainer()
{
    Serial.println("UIContainer with screen constructor");
    _screen     = screen;
    _size       = size;
    _alignment  = alignment;
}

void UIContainer::addUIElement(UIElement* element)
{
    UIDimensions_t      dimensions          = element->getDimensions();
    UIDimensions_t      containerDimensions = calculateContentSize();

    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            dimensions.topLeft.y        =  containerDimensions.topLeft.y + containerDimensions.bottomRight.y + _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            dimensions.topLeft.x        = containerDimensions.topLeft.x + containerDimensions.bottomRight.x + _padding;
            dimensions.topLeft.y        = containerDimensions.topLeft.y + _padding;
            break;
    }

    element->setDimensions(dimensions);
    _elements.push_back(element);

    calculateContentSize(true);
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

UIDimensions_t UIContainer::calculateContentSize(bool passToParent)
{
    UIDimensions_t tmpDimensions;
    UIDimensions_t dimensions   = _dimensions;
    uint8_t fullSize            = 0;

    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            dimensions.bottomRight.y = 0;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            Serial.println("horizontal alignment container");
            fullSize = dimensions.bottomRight.x;
            dimensions.bottomRight.x = 0;
            break;
    }

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        tmpDimensions = _elements[i]->getDimensions();
        switch(_alignment)
        {
            case ALIGNMENT_VERTICAL:
                dimensions.bottomRight.y    += tmpDimensions.bottomRight.y + _padding;
                break;
            case ALIGNMENT_HORIZONTAL:
            case ALIGNMENT_HORIZONTAL_FILL:
                dimensions.bottomRight.x    += tmpDimensions.bottomRight.x + _padding;
                if(dimensions.bottomRight.y < tmpDimensions.bottomRight.y + 2*_padding)
                {
                    dimensions.bottomRight.y = tmpDimensions.bottomRight.y + 2*_padding;
                }
                break;
        }
    }

    if(_parent && passToParent)
    {
        if(_alignment==ALIGNMENT_VERTICAL){
            dimensions.bottomRight.y += _padding;
        }
        else
        {
            // restore fullsize?
            dimensions.bottomRight.x = fullSize;
        }

        _dimensions =  dimensions;

        _parent->calculateContentSize(true);
    }

    return dimensions;
}

void UIContainer::draw(bool task)
{
    if(!task)
    {
        if(_bgColor > 0)
        {
            _tft->fillRect(_dimensions.topLeft.x, _dimensions.topLeft.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y, _bgColor);
        }
        
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element]->draw(task);
        }

        if(_largeContent)
        {
            if(_alignment == ALIGNMENT_VERTICAL)
            {
                _tft->drawLine(
                    _dimensions.topLeft.x,
                    _dimensions.topLeft.y + _dimensions.bottomRight.y -1,
                    _dimensions.bottomRight.x,
                    _dimensions.topLeft.y + _dimensions.bottomRight.y -1,
                    TFT_RED
                );
            }
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