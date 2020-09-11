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
        _dimensions.topLeft     = _parent->getNextElementPosition();
        _dimensions.bottomRight = {_padding,_padding};

        switch(_parent->_alignment)
        {
            case ALIGNMENT_HORIZONTAL:
                switch(_size)
                {
                    case SIZE_ELEMENT:
                        _dimensions.bottomRight.x = _padding;
                        if(_elements.size()>0)
                        {
                            calculateSize();
                        }
                        break;
                    case SIZE_FULL:
                        _dimensions.bottomRight.x =  _parent->_dimensions.bottomRight.x;
                        _dimensions.bottomRight.x -= 2*_parent->getPadding();
                        _dimensions.bottomRight.x -= _dimensions.topLeft.x;
                        break;
                    
                }
                _dimensions.bottomRight.y =  _parent->_dimensions.bottomRight.y;
                _dimensions.bottomRight.y -= 2*_parent->getPadding();
                break;
            case ALIGNMENT_VERTICAL:
                switch(_size)
                {
                    case SIZE_ELEMENT:
                        _dimensions.bottomRight.y = _padding;
                        if(_elements.size()>0)
                        {
                            calculateSize();
                        }
                        break;
                    case SIZE_FULL:
                        _dimensions.bottomRight.y =  _parent->_dimensions.bottomRight.y;
                        _dimensions.bottomRight.y -= 2*_parent->getPadding();
                        _dimensions.bottomRight.y -= _dimensions.topLeft.y;
                        break;
                    
                }
                _dimensions.bottomRight.x =  _parent->_dimensions.bottomRight.x;
                _dimensions.bottomRight.x -= 2*_parent->getPadding();
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
    UIDimensions_t dimensions       = element->getDimensions();
    dimensions.topLeft              = getNextElementPosition();

    element->setDimensions(dimensions);
    _elements.push_back(element);
    calculateSize();
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
            if(_elementSize.y > _dimensions.bottomRight.y)
            {
                return true;
            }
            break;
        case TouchMetrics::SWIPE_HORIZONTAL_STARTED:
        case TouchMetrics::SWIPING_RIGHT:
        case TouchMetrics::SWIPING_LEFT:
            if(_elementSize.x > _dimensions.bottomRight.x)
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

UIPoint_t UIContainer::getNextElementPosition()
{
    UIPoint_t pos = {_padding,_padding};

    for(uint8_t i = 0; i<_elements.size(); i++)
    {
        switch (_alignment)
        {
        case ALIGNMENT_VERTICAL:
            pos.y += _padding + _elements[i]->getDimensions().bottomRight.y;
            pos.x =  _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            pos.x += _padding + _elements[i]->getDimensions().bottomRight.x;
            pos.y =  _padding;
            break;
        }
    }

    return pos;
}


void UIContainer::calculateSize()
{
    _elementSize = {0,0};

    for(uint8_t i = 0; i < _elements.size(); i++)
    {
        switch(_alignment)
        {
            case ALIGNMENT_VERTICAL:
                if(_elementSize.x < _elements[i]->getDimensions().bottomRight.x + 2*_padding)
                {
                    _elementSize.x              =  2*_padding;
                    _elementSize.x              += _elements[i]->getDimensions().bottomRight.x;
                }
                if(_dimensions.bottomRight.x < _elementSize.x)
                {
                    _dimensions.bottomRight.x   =  _elementSize.x;
                }
                _elementSize.y += _padding;
                _elementSize.y += _elements[i]->getDimensions().bottomRight.y;
                break;
            case ALIGNMENT_HORIZONTAL:
            case ALIGNMENT_HORIZONTAL_FILL:
                if(_elementSize.y < _elements[i]->getDimensions().bottomRight.y + 2*_padding)
                {
                    _elementSize.y              =  2*_padding;
                    _elementSize.y              += _elements[i]->getDimensions().bottomRight.y;
                }
                if(_dimensions.bottomRight.y < _elementSize.y)
                {
                    _dimensions.bottomRight.y   =  _elementSize.y;
                }
                _elementSize.x +=  _padding;
                _elementSize.x += _elements[i]->getDimensions().bottomRight.x;
                break;
        }
    }
    
    switch(_alignment)
    {
        case ALIGNMENT_VERTICAL:
            _elementSize.y += _padding;
            break;
        case ALIGNMENT_HORIZONTAL:
        case ALIGNMENT_HORIZONTAL_FILL:
            _elementSize.x += _padding;
            break;
    }
}

bool UIContainer::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    // check if container is using a sprite
    // we cant say for sure if guesture is for this container or a child container
    if(_sprite.created())
    {
        // setting up max sprite scrolling
        _spritePosMax.x = (_elementSize.x - 2*_padding) - _sprite.width();
        _spritePosMax.y = (_elementSize.y - 2*_padding) - _sprite.height() + _spriteBottomSafety;

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
        if(_parent)
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
        else if(_screen && _bgColor > 0 &&(_bgColor != _screen->_bgColor))
        {
            _tft->fillRect(absPos.x,absPos.y,_dimensions.bottomRight.x,_dimensions.bottomRight.y,_bgColor);
        }
        
        for(uint8_t element = 0; element < _elements.size(); element++)
        {
            _elements[element]->draw(task);
            yield();
        }

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

        // background
        if(_padding > 0)
        {
            sprite->fillRect(
                pos.x - _padding,
                pos.y - _padding,
                _dimensions.bottomRight.x,
                _dimensions.bottomRight.y,
                _bgColor
            );
        }

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
        pos = getTopPosition();
        pos.x += _padding;
        pos.y += _padding;

        uint16_t dh = 0;
        
        while(dh < _sprite.height()-_spriteBottomSafety) {
            // Push to TFT 1 line at a time
            _tft->pushImage(pos.x, pos.y + dh, _sprite.width(), 1, _spriteData + (dh * _sprite.width()));
            dh++;
            yield();
        }
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