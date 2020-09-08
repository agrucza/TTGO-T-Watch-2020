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
        UIDimensions_t parentContainerDimensions = _parent->calculateContentSize();
        Serial.print("Parent calculateContentSize: ");
        Serial.print(parentContainerDimensions.topLeft.x);
        Serial.print(":");
        Serial.print(parentContainerDimensions.topLeft.y);
        Serial.print(":");
        Serial.print(parentContainerDimensions.bottomRight.x);
        Serial.print(":");
        Serial.println(parentContainerDimensions.bottomRight.y);

        _dimensions = _parent->getDimensions();
        _dimensions.topLeft.x += _parent->getPadding();
        _dimensions.topLeft.y += _parent->getPadding();
        _dimensions.bottomRight.x -= 2*_parent->getPadding();
        _dimensions.bottomRight.y -= 2*_parent->getPadding();

        switch(_parent->getAlignment())
        {
            case ALIGNMENT_VERTICAL:
                Serial.println("Parent has vertical alignment");
                _dimensions.bottomRight.y = 2*_padding;
                break;
            case ALIGNMENT_HORIZONTAL:
            case ALIGNMENT_HORIZONTAL_FILL:
                Serial.println("Parent has horizontal alignment");
                _dimensions.bottomRight.x = _padding;
                break;
        }

        Serial.print("dimensions will be: ");
        Serial.print(_dimensions.topLeft.x);
        Serial.print(":");
        Serial.print(_dimensions.topLeft.y);
        Serial.print(":");
        Serial.print(_dimensions.bottomRight.x);
        Serial.print(":");
        Serial.println(_dimensions.bottomRight.y);

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

    Serial.print("Container calculateContentSize: ");
    Serial.print(containerDimensions.topLeft.x);
    Serial.print(":");
    Serial.print(containerDimensions.topLeft.y);
    Serial.print(":");
    Serial.print(containerDimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(containerDimensions.bottomRight.y);

    dimensions.topLeft = containerDimensions.bottomRight;

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

    Serial.print("Elements dimensions will be: ");
    Serial.print(dimensions.topLeft.x);
    Serial.print(":");
    Serial.print(dimensions.topLeft.y);
    Serial.print(":");
    Serial.print(dimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(dimensions.bottomRight.y);

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

    Serial.print("### calculateContentSize: container _dimensions are: ");
    Serial.print(dimensions.topLeft.x);
    Serial.print(":");
    Serial.print(dimensions.topLeft.y);
    Serial.print(":");
    Serial.print(dimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(dimensions.bottomRight.y);

    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            fullSize                    = dimensions.bottomRight.y;
            dimensions.bottomRight.y    = _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            fullSize                    = dimensions.bottomRight.x;
            dimensions.bottomRight.x    = _padding;
            break;
    }

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        tmpDimensions = _elements[i]->getDimensions();
        switch(_alignment)
        {
            case ALIGNMENT_VERTICAL:
                dimensions.bottomRight.y        += tmpDimensions.bottomRight.y + _padding;
                if(dimensions.bottomRight.x < tmpDimensions.bottomRight.x + 2*_padding)
                {
                    dimensions.bottomRight.x    = tmpDimensions.bottomRight.x + 2*_padding;
                }
                break;
            case ALIGNMENT_HORIZONTAL:
            case ALIGNMENT_HORIZONTAL_FILL:
                dimensions.bottomRight.x        += tmpDimensions.bottomRight.x + _padding;
                if(dimensions.bottomRight.y     < tmpDimensions.bottomRight.y + 2*_padding)
                {
                    dimensions.bottomRight.y    = tmpDimensions.bottomRight.y + 2*_padding;
                }
                break;
        }
        yield();
    }

    Serial.print("### calculateContentSize: before adjustment - dimensions are: ");
    Serial.print(dimensions.topLeft.x);
    Serial.print(":");
    Serial.print(dimensions.topLeft.y);
    Serial.print(":");
    Serial.print(dimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(dimensions.bottomRight.y);

    if(_alignment==ALIGNMENT_VERTICAL){
        _fullSize = dimensions.bottomRight;
        if(_parent && dimensions.bottomRight.y > _parent->_dimensions.bottomRight.y)
        {
            dimensions.bottomRight.y = _parent->_dimensions.bottomRight.y;
        }
    }
    else
    {
        // restore fullsize?
        _fullSize = dimensions.bottomRight;
        if(_parent && dimensions.bottomRight.x > _parent->_dimensions.bottomRight.x)
        {
            dimensions.bottomRight.x = _parent->_dimensions.bottomRight.y;
        }
    }

    Serial.print("### calculateContentSize: after adjustment - dimensions are: ");
    Serial.print(dimensions.topLeft.x);
    Serial.print(":");
    Serial.print(dimensions.topLeft.y);
    Serial.print(":");
    Serial.print(dimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(dimensions.bottomRight.y);

    _dimensions =  dimensions;

    if(_parent && passToParent)
    {
        _parent->calculateContentSize(true);
    }

    if(_alignment==ALIGNMENT_VERTICAL){
        dimensions.bottomRight.x = _padding;
    }
    else
    {
        dimensions.bottomRight.y = _padding;
    }

    return dimensions;
}

bool UIContainer::isWithinDimensions(int x, int y)
{
    if(
        (x >= _dimensions.topLeft.x && x <= _dimensions.topLeft.x + _dimensions.bottomRight.x)
        && (y >= _dimensions.topLeft.y && y <= _dimensions.topLeft.y + _dimensions.bottomRight.y)
    ){
        return true;
    }
    return false;
};

bool UIContainer::acceptsTouchType(TouchMetrics::touch_t touchType)
{
    switch(touchType)
    {
        case TouchMetrics::TOUCH_START:
        case TouchMetrics::TOUCH_RELEASE:
            // this is needed to pass through as the swipe will need this
            return true;
            break;
        case TouchMetrics::SWIPE_VERTICAL_STARTED:
        case TouchMetrics::SWIPING_TOP:
        case TouchMetrics::SWIPING_BOTTOM:
            if(_fullSize.y > _dimensions.bottomRight.y)
            {
                return true;
            }
            break;
        case TouchMetrics::SWIPE_HORIZONTAL_STARTED:
        case TouchMetrics::SWIPING_RIGHT:
        case TouchMetrics::SWIPING_LEFT:
            if(_fullSize.x > _dimensions.bottomRight.x)
            {
                return true;
            }
            break;
    }
    return false;
};

void UIContainer::clean()
{
    for(uint8_t i=0; i<_elements.size(); i++)
    {
        if(UIContainer* container = dynamic_cast<UIContainer*>(_elements[i]))
        {
            container->clean();
        }
    }
    if(_sprite.created())
    {
        _sprite.deleteSprite();
    }
}

bool UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    // check if container is using a sprite
    // we cant say for sure if guesture is for this container or a child container
    if(_sprite.created())
    {
        // setting up max sprite scrolling
        _spritePosMax.x = _fullSize.x - _dimensions.bottomRight.x;
        _spritePosMax.y = _fullSize.y - _dimensions.bottomRight.y;

        // check for swipe gestures - those will only be for containers by now
        // (and maybe special elements in the future)
        // normal elements should not accept guestures
        for(uint8_t i = 0; i < _elements.size(); i++)
        {
            UIContainer* container  = nullptr;
            UIElement* element      = _elements[i];
            if(UIContainer* tmp = dynamic_cast<UIContainer*>(_elements[i]))
            {
                container = tmp;
            }
            else if(
                element->isWithinDimensions(lastX + _spritePos.x, lastY + _spritePos.y)
                // add more element touch types like long touch for context menus or other stuff
                && (touchType == TouchMetrics::TOUCH_RELEASE || touchType == TouchMetrics::TOUCHING)
            )
            {
                // this part needs to be in here to register touches of the elements in the container
                return element->touchAction(lastX + _spritePos.x, lastY + _spritePos.y, deltaX, deltaY, touchType);
            }
            else
            {
                yield();
                continue;
            }

            if(
                container->isWithinDimensions(lastX + _spritePos.x, lastY + _spritePos.y)
                && container->acceptsTouchType(touchType)
                && container->hasActiveSprite()
            )
            {
                // found a container which dimensions will cover the gesture and has a created sprite
                return container->touchAction(
                    lastX + _spritePos.x - container->_dimensions.topLeft.x,
                    lastY + _spritePos.y - container->_dimensions.topLeft.y,
                    deltaX,
                    deltaY,
                    touchType
                );
                continue;
            }
            yield();
        }

        if(touchType == TouchMetrics::SWIPE_VERTICAL_STARTED || touchType == TouchMetrics::SWIPE_HORIZONTAL_STARTED)
        {
            _spritePosOld       = _spritePos;
        }

        // if we land here we have no gesture compatible element setup so this should be the container guesture
        if(
               touchType == TouchMetrics::SWIPING_LEFT
            || touchType == TouchMetrics::SWIPING_RIGHT
            || touchType == TouchMetrics::SWIPING_TOP
            || touchType == TouchMetrics::SWIPING_BOTTOM
        )
        {
            // use spritePosOld for changing the position inside the sprite
            // boundary check for negative and overflow values between
            // _dimensions.bottomRight and _spritePosOld/_sprite.width()/_sprite.height()
            _spritePos.x = (_spritePosOld.x + deltaX > 0?(_spritePosOld.x + deltaX < _spritePosMax.x?_spritePosOld.x + deltaX:_spritePosMax.x):0);
            _spritePos.y = (_spritePosOld.y + deltaY > 0?(_spritePosOld.y + deltaY < _spritePosMax.y?_spritePosOld.y + deltaY:_spritePosMax.y):0);

            // checking for max pos reached to prevent continuous drawing once 0 or max is reached
            _spritePosMaxReached.x = (
                _spritePos.x == 0 || _spritePos.x == _spritePosMax.x
                ?true
                :(touchType != TouchMetrics::SWIPING_LEFT && touchType != TouchMetrics::SWIPING_RIGHT?true:false)
            );

            _spritePosMaxReached.y = (
                _spritePos.y == 0 || _spritePos.y == _spritePosMax.y
                ?true
                :(touchType != TouchMetrics::SWIPING_TOP && touchType != TouchMetrics::SWIPING_BOTTOM?true:false)
            );

            if(!(_spritePosMaxReached.x && _spritePosMaxReached.y)){
                reDraw(true);
            }

            return true;
        }
    } else {
        for(uint8_t i = 0; i < _elements.size(); i++)
        {
            if(_elements[i]->isWithinDimensions(lastX, lastY))
            {
                if(_elements[i]->touchAction(lastX - _elements[i]->_dimensions.topLeft.x, lastY - _elements[i]->_dimensions.topLeft.y, deltaX, deltaY, touchType)){
                    // for sprites
                    reDraw();
                    return true;
                }
            }
            yield();
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
            _sprite.fillScreen((_bgColor>0?_bgColor:TFT_GREENYELLOW));
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
            reDraw();
        }
    }
}

void UIContainer::_pushSprite()
{
    UIPoint_t pos;

    if(_parent->getSprite()->created())
    {
        
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
        TFT_eSprite* sprite = getSprite();
        pos = getTopPosition();
        pos.x += _padding;
        pos.y += _padding;
        sprite->pushSprite(pos.x, pos.y,TFT_GREENYELLOW);
    }
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