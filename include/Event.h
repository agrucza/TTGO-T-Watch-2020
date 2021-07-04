/**
    This is the energy class
    @file energy.h
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/

#ifndef __EVENT_H
#define __EVENT_H

typedef void* QueueHandle_t;
typedef void* EventGroupHandle_t;

class Event
{
    public:
        static QueueHandle_t        queueHandle;
        static EventGroupHandle_t   groupHandle;
        static EventGroupHandle_t   isrGroup;
};

#endif /*__EVENT_H */
