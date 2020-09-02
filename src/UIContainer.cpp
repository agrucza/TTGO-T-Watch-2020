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
        _dimensions                 = defaultUIDimensions;
        _dimensions.bottomRight.x   = TFT_WIDTH;
        _dimensions.bottomRight.y   = TFT_HEIGHT;
    }

    Serial.println("UIContainer constructor done");
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
            dimensions.topLeft.y        = containerDimensions.bottomRight.y + _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            dimensions.topLeft.x        = containerDimensions.bottomRight.x + _padding;
            dimensions.topLeft.y        = _padding;
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
            // test with sprites
            if(dimensions.bottomRight.x > fullSize)
            {
                Serial.println("Big content creating sprite");
                // create a sprite
                if(_sprite.created())
                {
                    Serial.println("Sprite already created - deleting");
                    _sprite.deleteSprite();
                }

                _spriteData = (uint16_t*)_sprite.createSprite(dimensions.bottomRight.x,dimensions.bottomRight.y);
                if(_sprite.created())
                {
                    Serial.println("Sprite created");
                }
                else
                {
                    Serial.println("SPRITE NOT CREATED");
                }                
            }
            // restore fullsize?
            dimensions.bottomRight.x = fullSize;
        }

        _dimensions =  dimensions;

        _parent->calculateContentSize(true);
    }

    return dimensions;
}

bool UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    UIDimensions_t  dim;
    UIPoint_t       absPos;

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        absPos  = _elements[i]->getTopPosition();
        dim     = _elements[i]->getDimensions();
        if(
                lastX >= absPos.x
            &&  lastX <= absPos.x + dim.bottomRight.x
            &&  lastY >= absPos.y
            &&  lastY <= absPos.y + dim.bottomRight.y
        )
        {
            if(_elements[i]->touchAction(lastX, lastY, deltaX, deltaY, touchType)){
                draw();
                break;
            }
        }
    }

    // if we are here we have a container touch
    return true;
}

void UIContainer::draw(bool task)
{
    UIPoint_t absPos = getTopPosition();

    if(!task)
    {
        if(_sprite.created())
        {
            if(_bgColor>0)
            {
                _sprite.fillScreen(_bgColor);
            }
            else
            {
                _sprite.fillScreen(TFT_GREENYELLOW);
            }
        }
        else if(_bgColor > 0)
        {
                _tft->fillRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,_bgColor);
        }
        
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element]->draw(task);
        }

        // if a sprite has been created we need to draw this on screen
        // unless our parent also has a sprite -> we need to draw this onto this sprite then
        
        // first: draw sprite to screen
        if(_sprite.created())
        {
            Serial.println("Sprite detected pushing sprite to tft");
            _pushSpriteRect(0, 0, _dimensions.bottomRight.x, _dimensions.bottomRight.y, absPos.x, absPos.y);
            Serial.println("Sprite should be on tft");
        }
    }
}

void UIContainer::_pushSpriteRect(uint16_t spriteX, uint16_t spriteY, uint16_t spriteW, uint16_t spriteH, int16_t tftX, int16_t tftY)
{
    // Do nothing if any part of rectangle is outside sprite
    if(
        ((spriteX + spriteW) > _sprite.width())
        || ((spriteY + spriteH) > _sprite.height())
    )
    {
        return;
    }

    uint16_t dh = 0;

    while(dh < spriteH) {
        // Push to TFT 1 line at a time
        _tft->pushImage(tftX, tftY + dh, spriteW, 1, _spriteData + spriteX + ((spriteY + dh) * _sprite.width()),TFT_GREENYELLOW);
        dh++;
    }
}

void UIContainer::reDraw()
{

}