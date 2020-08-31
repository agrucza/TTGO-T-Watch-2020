#include "config.h"
#include "LilyGoWatch.h"
#include "UIContainer.h"
#include "UIElement.h"
#include "UIElementLabel.h"
#include "GUI.h"

UIContainer::UIContainer(UIElement* parent, UIESize_t size, UIEAlignment_t alignment)
:UIElement(parent)
{
    Serial.println("UIContainer constructor");
    _size       = size;
    _alignment  = alignment;
    
    //Serial.println("Setting container dimensions");
    if(_parent)
    {
        Serial.println("Container has parent");
        _dimensions = _parent->getRemainingSpace();
    }
    else
    {
        Serial.println("Container has no parent");
        _dimensions.topLeft.x       = _dimensions.topLeft.y = 0;
        _dimensions.bottomRight.x   = TFT_WIDTH;
        _dimensions.bottomRight.y   = TFT_HEIGHT;
    }

    //Serial.println("Setting containers remaining space");
    _remainingSpace = _dimensions;

    //Serial.println("Setting containers inner dimensions");
    _dimensionsInner = _dimensions;
    _dimensionsInner.topLeft.x += _padding;
    _dimensionsInner.topLeft.y += _padding;
    _dimensionsInner.bottomRight.x -= 2*_padding;
    _dimensionsInner.bottomRight.y -= 2*_padding;
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
    UIDimensions_t      dimensions = element->getDimensions();
    UIDimensions_t      tmpDimensions;

    char buf[50];

    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            dimensions.topLeft.y = _dimensions.topLeft.y + _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
            dimensions.topLeft.x = _dimensions.topLeft.x + _padding;
            break;
    }

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        tmpDimensions = _elements[i]->getDimensions();
        switch(_alignment)
        {
            case ALIGNMENT_VERTICAL:
                tmpDimensions.topLeft.y =  dimensions.topLeft.y;
                dimensions.topLeft.y    += tmpDimensions.bottomRight.y;
                break;
            case ALIGNMENT_HORIZONTAL:
                tmpDimensions.topLeft.x =  dimensions.topLeft.x;
                dimensions.topLeft.x    += tmpDimensions.bottomRight.x;
                break;
        }
        _elements[i]->setDimensions(tmpDimensions);
    }

    Serial.println("remaining before alignment adjustments");
    sprintf(
        buf,
        "remains: %d:%d/%d:%d",
        _remainingSpace.topLeft.x,
        _remainingSpace.topLeft.y,
        _remainingSpace.bottomRight.x,
        _remainingSpace.bottomRight.y
    );
    Serial.println(buf);
    sprintf(
        buf,
        "dimensions: %d:%d/%d:%d",
        dimensions.topLeft.x,
        dimensions.topLeft.y,
        dimensions.bottomRight.x,
        dimensions.bottomRight.y
    );
    Serial.println(buf);
    sprintf(
        buf,
        "_dimensions: %d:%d/%d:%d",
        _dimensions.topLeft.x,
        _dimensions.topLeft.y,
        _dimensions.bottomRight.x,
        _dimensions.bottomRight.y
    );
    Serial.println(buf);
    
    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            //_remainingSpace.topLeft.y       = dimensions.topLeft.y + dimensions.bottomRight.y;
            //_remainingSpace.bottomRight.y   = _dimensions.bottomRight.y - dimensions.bottomRight.y - size;
            _remainingSpace.topLeft.y      += dimensions.bottomRight.y;
            _remainingSpace.bottomRight.y  -= dimensions.bottomRight.y;
            break;
        case ALIGNMENT_HORIZONTAL:
            _remainingSpace.topLeft.x       += dimensions.bottomRight.x;
            _remainingSpace.bottomRight.x   -= dimensions.bottomRight.x;
            break;
    }

    Serial.println("remaining after alignment adjustments:");
    sprintf(
        buf,
        "remains: %d:%d/%d:%d",
        _remainingSpace.topLeft.x,
        _remainingSpace.topLeft.y,
        _remainingSpace.bottomRight.x,
        _remainingSpace.bottomRight.y
    );
    Serial.println(buf);

    element->setDimensions(dimensions);
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
    //_tft->fillRect(_dimensions.topLeft.x, _dimensions.topLeft.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y, _bgColor);
    
    for(uint8_t element = 0; element < _elements.size(); element++)
    {
        _elements[element]->draw(task);
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