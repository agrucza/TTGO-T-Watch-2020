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
                _dimensions.bottomRight.x = _padding;
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
            dimensions.topLeft.y        = containerDimensions.bottomRight.y;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            dimensions.topLeft.x        = containerDimensions.bottomRight.x;
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
        yield();
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
            dimensions.bottomRight.y = _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            Serial.println("horizontal alignment container");
            fullSize = dimensions.bottomRight.x;
            dimensions.bottomRight.x = _padding;
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
        yield();
    }

    if(_parent && passToParent)
    {
        if(_alignment==ALIGNMENT_VERTICAL){
            //dimensions.bottomRight.y += _padding;
        }
        else
        {
            // restore fullsize?
            _fullSize = dimensions.bottomRight;
            dimensions.bottomRight.x = fullSize;
        }

        _dimensions =  dimensions;

        _parent->calculateContentSize(true);
    }

    return dimensions;
}

bool UIContainer::isWithinDimensions(int x, int y){
    if(
        (x >= _dimensions.topLeft.x + _spritePos.x && x <= _dimensions.topLeft.x + _dimensions.bottomRight.x)
        && (y >= _dimensions.topLeft.y && y <= _dimensions.topLeft.y + _dimensions.bottomRight.y)
    ){
        return true;
    }
    return false;
};

bool UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    char buf[50];

    // check if container is using a sprite
    // we cant say for sure if guesture is for this container or a child container
    if(_sprite.created())
    {
        _spritePosMax.x = _sprite.width() - (_dimensions.bottomRight.x - 2*_padding);
        _spritePosMax.y = _sprite.height() - (_dimensions.bottomRight.y - 2*_padding);
        // check for swipe gestures - those will only be for containers by now
        // (and maybe special elements in the future)
        // normal elements should not accept guestures
        for(uint8_t i = 0; i < _elements.size(); i++)
        {
            UIElement* element = _elements[i];
            if(
                element->isWithinDimensions(lastX, lastY)
                && element->isWithinDimensions(lastX + deltaX, lastY + deltaY)
                && element->hasActiveSprite()
            )
            {
                // found an element which dimensions will cover the complete gesture and has a created sprite
                return element->touchAction(lastX, lastY, deltaX, deltaY, touchType);
            }
        }

        bool gesture = false;
        bool gestureHorizontal;

        // if we land here we have no gesture compatible element setup so this should be the container guesture
        switch(touchType)
        {
            // by now only basic swipes will be considered
            
            /*
            case TouchMetrics::TOUCHING:
            case TouchMetrics::SWIPING_TOP_EDGE:
            case TouchMetrics::SWIPING_RIGHT_EDGE:
            case TouchMetrics::SWIPING_BOTTOM_EDGE:
            case TouchMetrics::SWIPING_LEFT_EDGE:
            */
            case TouchMetrics::TOUCH_START:
                _spritePosOld = _spritePos;
                break;
            case TouchMetrics::SWIPING_LEFT:
                // swiping from left to right
            case TouchMetrics::SWIPING_RIGHT:
                // swiping from right to left
                gesture             = true;
                gestureHorizontal   = true;
                break;
            case TouchMetrics::SWIPING_TOP:
                // swiping from top to bottom
            case TouchMetrics::SWIPING_BOTTOM:
                // swiping from bottom to top
                gesture             = true;
                gestureHorizontal   = false;
                break;
        }

        if(gesture)
        {
            // use spritePosOld for changing the position inside the sprite
            // boundary check for negative and overflow values between
            // _dimensions.bottomRight and _spritePosOld/_sprite.width()/_sprite.height()
            UIPoint_t absPos = getTopPosition();

            _spritePos.x = (_spritePosOld.x + deltaX > 0?(_spritePosOld.x + deltaX < _spritePosMax.x?_spritePosOld.x + deltaX:_spritePosMax.x):0);
            _spritePos.y = (_spritePosOld.y + deltaY > 0?(_spritePosOld.y + deltaY < _spritePosMax.y?_spritePosOld.y + deltaY:_spritePosMax.y):0);
            
            if(!(_spritePosMaxReached.x && _spritePosMaxReached.y)){
                _pushSpriteRect(
                    absPos.x + _padding,
                    absPos.y + _padding,
                    _spritePos.x,
                    _spritePos.y,
                    _dimensions.bottomRight.x - 2*_padding,
                    _dimensions.bottomRight.y - 2*_padding
                );
                sprintf(buf,"swipe (%d) in %d:%d for %d:%d",deltaX, _dimensions.topLeft.x, _dimensions.topLeft.y, lastX, lastY);
                Serial.println(buf);
            }

            // checking for max pos reached to prevent continuous drawing once 0 or max is reached
            _spritePosMaxReached.x = (_spritePos.x == 0 || _spritePos.x == _spritePosMax.x?true:(!gestureHorizontal?true:false));
            _spritePosMaxReached.y = (_spritePos.y == 0 || _spritePos.y == _spritePosMax.y?true:(gestureHorizontal?true:false));
            return true;
        }
    }

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        UIElement* element = _elements[i];
        if(element->isWithinDimensions(lastX + _spritePos.x, lastY + _spritePos.y))
        {
            if(_elements[i]->touchAction(lastX - element->_dimensions.topLeft.x, lastY - element->_dimensions.topLeft.y, deltaX, deltaY, touchType)){
                draw();
                break;
            }
        }
        yield();
    }

    // if we are here we have a container touch
    return true;
}

void UIContainer::draw(bool task)
{
    UIPoint_t absPos = getTopPosition();

    //Serial.println("Container draw method");

    if(!task)
    {
        // check if sprite is used
        if((_dimensions.bottomRight.x < _fullSize.x) || (_dimensions.bottomRight.y < _fullSize.y))
        {
            if(_sprite.created())
            {
                // check if container size has changed and is different from sprite size
                if(_fullSize.x != (_sprite.width() + 2*_padding) || _fullSize.y != (_sprite.height() + 2*_padding))
                {
                    // delete sprite and create new one
                    _sprite.deleteSprite();
                    _spriteData = nullptr;
                    _spriteData = (uint16_t*)_sprite.createSprite(_fullSize.x - 2*_padding,_fullSize.y - 2*_padding);
                    _sprite.fillRect(0, 0 ,_fullSize.x - 2*_padding, _fullSize.y - 2*_padding, (_bgColor>0?_bgColor:TFT_GREENYELLOW));
                }
            }
            else
            {
                // no sprite - creating
                _spriteData = (uint16_t*)_sprite.createSprite(_fullSize.x - 2*_padding,_fullSize.y - 2*_padding);
                _sprite.fillRect(0, 0 ,_fullSize.x - 2*_padding, _fullSize.y - 2*_padding, (_bgColor>0?_bgColor:TFT_GREENYELLOW));
            }
        }
        else if(_bgColor > 0)
        {
                _tft->fillRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,_bgColor);
        }
        
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element]->draw(task);
            yield();
        }

        // if a sprite has been created we need to draw this on screen
        // unless our parent also has a sprite -> we need to draw this onto this sprite then
        
        // first: draw sprite to screen
        if(_sprite.created())
        {
            _pushSpriteRect(
                absPos.x + _padding,
                absPos.y + _padding,
                _spritePos.x,
                _spritePos.y,
                _dimensions.bottomRight.x - 2*_padding,
                _dimensions.bottomRight.y - 2*_padding
            );
            //Serial.println("Sprite should be on tft");
        }
    }
    else
    {
        //Serial.println("Container draw method - TASK");
        /*
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element]->draw(task);
            yield();
        }

        // testing something
        if(_moveForeward){
            _spritePos.x++;
            if(_spritePos.x >= _fullSize.x - _dimensions.bottomRight.x)
            {
                _moveForeward = false;
            }
        } else {
            _spritePos.x--;
            if(_spritePos.x <= 0)
            {
                _moveForeward = true;
            }
        }
        
        if(_sprite.created())
        {
            //Serial.println("Sprite detected pushing sprite to tft");
            _pushSpriteRect(absPos.x, absPos.y, _spritePos.x, _spritePos.y, _dimensions.bottomRight.x, _dimensions.bottomRight.y);
            //Serial.println("Sprite should be on tft");
        }
        */
    }
}

void UIContainer::_pushSpriteRect(int16_t tftX, int16_t tftY, uint16_t spriteX, uint16_t spriteY, uint16_t spriteW, uint16_t spriteH)
{
    // Do nothing if any part of rectangle is outside sprite
    if(((spriteX + spriteW) > _sprite.width()) || ((spriteY + spriteH) > _sprite.height()))
    {
        return;
    }

    uint16_t dh = 0;

    while(dh < spriteH) {
        // Push to TFT 1 line at a time
        _tft->pushImage(tftX, tftY + dh, spriteW, 1, _spriteData + spriteX + ((spriteY + dh) * _sprite.width()),TFT_GREENYELLOW);
        dh++;
        yield();
    }
}

void UIContainer::reDraw()
{

}