/**
    This is the UITypes definition
    @file UITypes.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UITYPES_H
#define __UITYPES_H

#include <Arduino.h>

class UIScreen;
class UIElement;
class UIContainer;

enum UIElement_t : uint8_t{
    UIETYPE_ELEMENT,
    UIETYPE_CONTAINER
};

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
    SIZE_ELEMENT,           // this is only the required space by the element
    SIZE_FULL,              // this is the full size vertical/horizontal
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

typedef void *ui_event_void_t;

struct ui_event_data_t{
    UIElement*      source;
    UIScreen*       screen;
    ui_event_void_t event;
};

typedef void (*ui_event_cb_t)(ui_event_data_t* eventData);

#endif /*__UITYPES_H */
