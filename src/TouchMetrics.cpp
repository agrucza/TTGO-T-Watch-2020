#include "TouchMetrics.h"

#include "config.h"
#include "LilyGoWatch.h"
#include "GUI.h"

extern TTGOClass* ttgo;

TouchMetrics::TouchMetrics()
{
    _ttgo               = ttgo;
    _touch              = false;
    _swipeTolerance     = 10;
    _swipeEdgeDetection = 30;
    _x = _y             = -1;
    _lastX = _lastY     = -1;
}

void TouchMetrics::checkTouch()
{
    int16_t touchX, touchY;
    if(_ttgo->getTouch(touchX, touchY))
    {
        setX(touchX);
        setY(touchY);

        if(!getTouch()){
            // this is the finger comming down
            setLastX(touchX);
            setLastY(touchY);
            setTouch(true);
        } else {
            // vector of touch?
        }
    } else if(getTouch()){
        _touch = false;
        // no touch registered this will check if a previous touch was set
        // check for swipes?
        int16_t deltaX  = _lastX - _x;
        int16_t deltaY  = _lastY - _y;
        bool swipeX     = abs(deltaX) > abs(deltaY);

        //double thetaRadians = atan2(deltaY, deltaX);

        // delta values can be added to scrolling
        // -> negative is back
        // -> posivive is next
        if(swipeX && (abs(deltaX) > (TFT_WIDTH/_swipeTolerance)))
        {
            // check for left swite
            if(deltaX>0)
            {
                /*
                GUI::touchAction(
                    _lastX,
                    _lastY,
                    deltaX,
                    deltaY,
                    // check for right screen edge
                    (_lastX>(TFT_WIDTH - _swipeEdgeDetection)?touch_t::SWIPE_RIGHT_EDGE:touch_t::SWIPE_LEFT)
                );
                */
            }
            else
            {
                /*
                GUI::touchAction(
                    _lastX,
                    _lastY,
                    deltaX,
                    deltaY,
                    // check for left screen edge
                    ((_lastX<_swipeEdgeDetection)?touch_t::SWIPE_LEFT_EDGE:touch_t::SWIPE_RIGHT)
                );
                */
            }
        }
        else if(!swipeX && (abs(deltaY) > (TFT_HEIGHT/_swipeTolerance)))
        {
            // check for up swipe
            if(deltaY>0)
            {
                /*
                GUI::touchAction(
                    _lastX,
                    _lastY,
                    deltaX,
                    deltaY,
                    // check for top screen edge
                    (_lastY>(TFT_HEIGHT - _swipeEdgeDetection)?touch_t::SWIPE_BOTTOM_EDGE:touch_t::SWIPE_TOP)
                );
                */
            }
            else
            {
                /*
                // check for top screen edge
                GUI::touchAction(
                    _lastX,
                    _lastY,
                    deltaX,
                    deltaY,
                    (_lastY<_swipeEdgeDetection?touch_t::SWIPE_TOP_EDGE:touch_t::SWIPE_TOP)
                );
                */
            }
        }
        else
        {
            //GUI::touchAction(_lastX, _lastY, deltaX, deltaY, touch_t::TOUCH);
        }
    }
}
