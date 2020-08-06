#include "UITypes.h"
#include "UIElement.h"
#include "config.h"
#include "LilyGoWatch.h"

UIElement::UIElement(UIContainer* parent, UIEOrientation_t orientation, UIESize_t sizeX, UIESize_t sizeY, UIDimensions_t sizeGap)
{
    _parent = parent;
    _orientation = orientation;
    _sizeX = sizeX;
    _sizeGap = sizeGap;

    UIDimensions_t parentDimensions;

    if(_parent != NULL)
    {
        parentDimensions = _parent->getDimensions();
    }
    else
    {
        parentDimensions.topLeft.x      = parentDimensions.topLeft.y = 0;
        parentDimensions.bottomRight.x  = TFT_WIDTH;
        parentDimensions.bottomRight.y  = TFT_HEIGHT;
    }

    if(sizeX == FULL)
    {
        _dimensions.topLeft.x = parentDimensions.topLeft.x;
        _dimensions.bottomRight.x = parentDimensions.bottomRight.x;
    }
}
