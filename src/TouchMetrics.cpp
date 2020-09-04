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
        touchBlockedBy = TOUCH_NONE;
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
    // <- negative is back
    // -> positive is next

    /*
     * HORIZONTAL SWIPING
     */
    if(swipeX && (abs(deltaX) > (TFT_WIDTH/_swipeTolerance)))
    {
        // we need to block swiping directions otherwise we will confuse the GUI
        if(touchBlockedBy == TOUCH_NONE || touchBlockedBy == SWIPING_HORIZONTAL)
        {
            touchBlockedBy = SWIPING_HORIZONTAL;

            // check for left swipe
            if(deltaX>0)
            {
                GUI::touchAction(
                    _lastX,
                    _lastY,
                    deltaX,
                    0,
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
                    0,
                    // check for left screen edge
                    (
                        _lastX<_swipeEdgeDetection
                        ?(_touch?touch_t::SWIPING_LEFT_EDGE:touch_t::SWIPE_LEFT_EDGE)
                        :(_touch?touch_t::SWIPING_RIGHT:touch_t::SWIPE_RIGHT)
                    )
                );
            }
        }
    }
    /*
     * VERTICAL SWIPING
     */
    else if(!swipeX && (abs(deltaY) > (TFT_HEIGHT/_swipeTolerance)))
    {
        // we need to block swiping directions otherwise we will confuse the GUI
        if(touchBlockedBy == TOUCH_NONE || touchBlockedBy == SWIPING_VERTICAL)
        {
            touchBlockedBy = SWIPING_VERTICAL;
            // check for up swipe
            if(deltaY>0)
            {
                GUI::touchAction(
                    _lastX,
                    _lastY,
                    0,
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
                    0,
                    deltaY,
                    (
                        _lastY<_swipeEdgeDetection
                        ?(_touch?touch_t::SWIPING_TOP_EDGE:touch_t::SWIPE_TOP_EDGE)
                        :(_touch?touch_t::SWIPING_BOTTOM:touch_t::SWIPE_BOTTOM)
                    )
                );
            }
        }
    }
    else
    {
        GUI::touchAction(_lastX, _lastY, deltaX, deltaY, (_touch?touch_t::TOUCHING:touch_t::TOUCH_RELEASE));
    }
}
