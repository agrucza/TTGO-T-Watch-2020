#include "config.h"
#include "LilyGoWatch.h"

#include "UIContainer.h"

#include "GUI.h"
#include "UIElement.h"
#include "UIElementLabel.h"

UIContainer::UIContainer(UIContainer* parent, UIESize_t size, UIEAlignment_t alignment)
:UIElement(parent)
{
    _size       = size;
    _alignment  = alignment;
    
    if(_parent)
    {
        // the parents dimensions plus padding will be the bounds of the new container
        // depending on the parents alignment we will set the width and height
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

        // setting background color
        _bgColor = _parent->_bgColor;
    }
    else
    {
        _dimensions                 = defaultUIDimensions;
        _dimensions.bottomRight.x   = TFT_WIDTH;
        _dimensions.bottomRight.y   = TFT_HEIGHT;
    }
}

UIContainer::UIContainer(UIScreen* screen, UIESize_t size, UIEAlignment_t alignment)
:UIContainer()
{
    _screen     = screen;
    _size       = size;
    _alignment  = alignment;

    // setting background color
    _bgColor = _screen->_bgColor;
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
            fullSize = dimensions.bottomRight.y;
            dimensions.bottomRight.y = _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
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
            _fullSize = dimensions.bottomRight;
            dimensions.bottomRight.y = fullSize;
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
        (x >= _dimensions.topLeft.x && x <= _dimensions.topLeft.x + _dimensions.bottomRight.x)
        && (y >= _dimensions.topLeft.y && y <= _dimensions.topLeft.y + _dimensions.bottomRight.y)
    ){
        return true;
    }
    return false;
};

bool UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    // check if container is using a sprite
    // we cant say for sure if guesture is for this container or a child container
    if(_sprite.created())
    {
        _spritePosMax.x = _fullSize.x - _dimensions.bottomRight.x;
        _spritePosMax.y = _fullSize.y - _dimensions.bottomRight.y;

        // check for swipe gestures - those will only be for containers by now
        // (and maybe special elements in the future)
        // normal elements should not accept guestures
        for(uint8_t i = 0; i < _elements.size(); i++)
        {
            UIContainer* container = nullptr;
            if(UIContainer* tmp = dynamic_cast<UIContainer*>(_elements[i]))
            {
                container = tmp;
            }
            else
            {
                yield();
                continue;
            }

            if(
                container->isWithinDimensions(lastX + _spritePos.x, lastY + _spritePos.y)
                //&& container->isWithinDimensions(lastX + deltaX + _spritePos.x, lastY + deltaY + _spritePos.y)
                && container->hasActiveSprite()
            )
            {
                // found a container which dimensions will cover the complete gesture and has a created sprite
                return container->touchAction(
                    lastX + _spritePos.x - container->_dimensions.topLeft.x,
                    lastY + _spritePos.y - container->_dimensions.topLeft.y,
                    deltaX,
                    deltaY,
                    touchType
                );
            }
            yield();
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
                _spritePosOld       = _spritePos;
                gesture             = false;
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
            _spritePos.x = (_spritePosOld.x + deltaX > 0?(_spritePosOld.x + deltaX < _spritePosMax.x?_spritePosOld.x + deltaX:_spritePosMax.x):0);
            _spritePos.y = (_spritePosOld.y + deltaY > 0?(_spritePosOld.y + deltaY < _spritePosMax.y?_spritePosOld.y + deltaY:_spritePosMax.y):0);

            if(!(_spritePosMaxReached.x && _spritePosMaxReached.y)){
                reDraw(true);
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
                // for sprites
                reDraw(true);
                return true;
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

    if(!task)
    {
        // check if sprite is used
        if((_dimensions.bottomRight.x < _fullSize.x) || (_dimensions.bottomRight.y < _fullSize.y))
        {
            if(!_sprite.created())
            {
                // no sprite - creating
                // we will add a safety buffer 
                _spriteData = (uint16_t*)_sprite.createSprite(
                    _dimensions.bottomRight.x - 2*_padding,
                    _dimensions.bottomRight.y - 2*_padding + _spriteBottomSafety
                );
                _sprite.setTextDatum(MC_DATUM);
            }
            Serial.print("Sprite created with bgColor: ");
            Serial.print(_bgColor);
            if(_parent)
            {
                Serial.print(" parent got: ");
            } else {
                Serial.print(" screen got: ");
            }
            Serial.println((_parent?_parent->_bgColor:_screen->_bgColor));

            _sprite.fillScreen((_bgColor>0?_bgColor:TFT_GREENYELLOW));
        }
        else if(_bgColor > 0)
        {
            //_tft->fillRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,_bgColor);
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
            Serial.println("Drawing sprite...");
            reDraw();
            Serial.println("Sprite should be on tft");
        }
    }
}

void UIContainer::_pushSprite()
{
    Serial.println("Inside _pushSprite ...");
    UIPoint_t pos;

    if(_parent->getSprite()->created())
    {
        Serial.println("Parent has sprite - getting parents sprite to use instead of tft");
        
        TFT_eSprite* sprite =  _parent->getSprite();
        pos     =  _dimensions.topLeft;
        pos.x   -= _parent->getSpritePos().x;
        pos.y   -= _parent->getSpritePos().y;
        //target->fillScreen(TFT_BLACK);
        uint16_t dh = 0;

        while(dh < _sprite.height()-_spriteBottomSafety) {
            // Push to TFT 1 line at a time
            sprite->pushImage(pos.x, pos.y + dh, _sprite.width(), 1, _spriteData + (dh * _sprite.width()));
            dh++;
            yield();
        }
    }
    else
    {
        Serial.println("Parent has no sprite - using tft");
        TFT_eSprite* sprite = getSprite();
        pos = getTopPosition();
        pos.x += _padding;
        pos.y += _padding;
        sprite->pushSprite(pos.x, pos.y,TFT_GREENYELLOW);
    }
    Serial.println("_pushSprite: finished");
}

void UIContainer::reDraw( bool recursive)
{
    if(_sprite.created()){
        _pushSprite();
        if(recursive && _parent->hasActiveSprite())
        {
            _parent->reDraw(recursive);
        }
    }
    else
    {
        draw();
    }
}