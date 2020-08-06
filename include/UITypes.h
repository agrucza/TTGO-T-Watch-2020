/**
    This is the UITypes definition
    @file UITypes.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UITYPES_H
#define __UITYPES_H

#include <Arduino.h>
class UIElement;
class UIContainer;

enum UIEAlignment_t : uint8_t {
    ALIGNMENT_HORIZONTAL,
    ALIGNMENT_VERTICAL
};

enum UIEOrientation_t : uint8_t {
    LEFT_TOP,
    LEFT_CENTER,
    LEFT_BOTTOM,
    CENTER_TOP,
    CENTER_CENTER,
    CENTER_BOTTOM,
    RIGHT_TOP,
    RIGHT_CENTER,
    RIGHT_BOTTOM
};

enum UIESize_t : uint8_t {
    ELEMENT,                // this is only the required space by the element
    FULL,                   // this is the full size vertical/horizontal
    FULL_GAP_LEFT_TOP,      // this will require an extra parameter dimension
    FULL_GAP_BOTTOM_RIGHT,  // this will require an extra parameter dimension
    FULL_GAP_BOTH,          // this will require an extra parameter dimension
    FIXED_PIXEL,            // this will require an extra parameter dimension
};

struct UIPoint_t{
    int16_t x;
    int16_t y;
};

struct UIDimensions_t{
    UIPoint_t   topLeft;
    UIPoint_t   bottomRight;
};

struct UIColor_t{
    int16_t r;
    int16_t g;
    int16_t b;
};

struct UIElementDetails_t{
    UIElement*      element;
    UIDimensions_t  dimensions;
};

struct UIContainerDetails_t{
    UIContainer*    container;
    UIDimensions_t  dimensions;
};

#endif /*__UITYPES_H */
