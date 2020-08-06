#include "UIContainer.h"
#include "UIElement.h"
#include "GUI.h"

UIContainer::UIContainer(UIContainer* parent, UIEAlignment_t alignment, UIESize_t sizeX, UIESize_t sizeY, UIDimensions_t sizeGap)
{
    _parent     = parent;
    _alignment  = alignment;
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

    dimensions.topLeft.x = dimensions.topLeft.y = dimensions.bottomRight.x = 0;

    for(uint8_t i = 0; i < _element.size(); i++)
    {
        tmpDimensions = _element[i].element->getDimensions();
        tmpDimensions.topLeft.y = dimensions.topLeft.y;
        _element[i].element->setDimensions(tmpDimensions);
        dimensions.topLeft.y += tmpDimensions.bottomRight.y + 1;
    }
    element->setDimensions(dimensions);
    newDetails.element      = element;
    newDetails.dimensions   = dimensions;
    dimensions.topLeft.y += tmpDimensions.bottomRight.y;
    _element.push_back(newDetails);
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

    for(uint8_t i = 0; i < _element.size(); i++)
    {
        if(_element[i].element == element)
        {
            return _element[i].dimensions;
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
    } else if(_element.size()>0)
    {
        for(uint8_t element = 0; element < _element.size(); element++)
        {
            _element[element].element->draw();
        }
    }
}

void UIContainer::reDraw()
{

}
