/**
    This is the UITypes definition
    @file UITypes.h
    @author Alexander Grucza
    @version 0.1 8/03/2020
*/

#ifndef __UITYPES_H
#define __UITYPES_H

#include <Arduino.h>

class App;
class UIElement;
class UIContainer;

enum UIElement_t : uint8_t{
    UIETYPE_ELEMENT,
    UIETYPE_CONTAINER
};

enum UIEAlignment_t : uint8_t {
    ALIGNMENT_HORIZONTAL,
    ALIGNMENT_HORIZONTAL_FILL,
    ALIGNMENT_VERTICAL
};

enum UIEOrientation_t : uint8_t {
    ORIENTATION_LEFT,
    ORIENTATION_CENTER,
    ORIENTATION_RIGHT
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

enum ui_event_t : uint8_t {
    EVENT_OPEN_MODAL,
    EVENT_CLOSE_MODAL,
};

typedef void *ui_event_void_t;

struct ui_event_data_t{
    UIElement*      source;
    App*            app;
    ui_event_t      event;
    ui_event_void_t target;
};

typedef void (*ui_event_cb_t)(ui_event_data_t* eventData);

#endif /*__UITYPES_H */
