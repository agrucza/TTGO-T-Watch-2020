#include "TouchMetrics.h"

#include "config.h"
#include "LilyGoWatch.h"

#include "GUI.h"

extern TTGOClass *ttgo;

void TouchMetrics::checkTouch()
{
    int16_t touchX, touchY;
    if(_ttgo->getTouch(touchX, touchY))
    {
        setX(touchX);
        setY(touchY);

        if(!getTouch())
        {
            // this is the finger comming down
            setLastX(touchX);
            setLastY(touchY);
            setTouch(true);
            GUI::touchAction(_lastX, _lastY, 0, 0, touch_t::TOUCH_START);
        } else {
            // vector of touch?
            _sendTouchType();
        }
    }
    else if(getTouch())
    {
        setTouch(false);
        _sendTouchType();
    }
}

void TouchMetrics::_sendTouchType()
{
    // check for swipes?
    int16_t deltaX  = _lastX - _x;
    int16_t deltaY  = _lastY - _y;
    bool swipeX     = abs(deltaX) > abs(deltaY);

    // delta values can be added to scrolling
    // -> negative is back
    // -> posivive is next
    if(swipeX && (abs(deltaX) > (TFT_WIDTH/_swipeTolerance)))
    {
        // check for left swite
        if(deltaX>0)
        {
            GUI::touchAction(
                _lastX,
                _lastY,
                deltaX,
                deltaY,
                // check for right screen edge
                (
                    _lastX>(TFT_WIDTH - _swipeEdgeDetection)
                    ?(_touch?touch_t::SWIPING_RIGHT_EDGE:touch_t::SWIPE_RIGHT_EDGE)
                    :(_touch?touch_t::SWIPING_LEFT:touch_t::SWIPE_LEFT)
                )
            );
        }
        else
        {
            GUI::touchAction(
                _lastX,
                _lastY,
                deltaX,
                deltaY,
                // check for left screen edge
                (
                    _lastX<_swipeEdgeDetection
                    ?(_touch?touch_t::SWIPING_LEFT_EDGE:touch_t::SWIPE_LEFT_EDGE)
                    :(_touch?touch_t::SWIPING_RIGHT:touch_t::SWIPE_RIGHT)
                )
            );
        }
    }
    else if(!swipeX && (abs(deltaY) > (TFT_HEIGHT/_swipeTolerance)))
    {
        // check for up swipe
        if(deltaY>0)
        {
            GUI::touchAction(
                _lastX,
                _lastY,
                deltaX,
                deltaY,
                // check for top screen edge
                (
                    _lastY>(TFT_HEIGHT - _swipeEdgeDetection)
                    ?(_touch?touch_t::SWIPING_BOTTOM_EDGE:touch_t::SWIPE_BOTTOM_EDGE)
                    :(_touch?touch_t::SWIPING_TOP:touch_t::SWIPE_TOP)
                )
            );
        }
        else
        {
            // check for top screen edge
            GUI::touchAction(
                _lastX,
                _lastY,
                deltaX,
                deltaY,
                (
                    _lastY<_swipeEdgeDetection
                    ?(_touch?touch_t::SWIPING_TOP_EDGE:touch_t::SWIPE_TOP_EDGE)
                    :(_touch?touch_t::SWIPING_BOTTOM:touch_t::SWIPE_BOTTOM)
                )
            );
        }
    }
    else
    {
        GUI::touchAction(_lastX, _lastY, deltaX, deltaY, (_touch?touch_t::TOUCHING:touch_t::TOUCH_RELEASE));
    }
}
