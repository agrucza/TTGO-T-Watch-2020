#include <Arduino.h>
#include "WiFi.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "Event.h"

QueueHandle_t       Event::queueHandle  = xQueueCreate(20, sizeof(uint8_t));
EventGroupHandle_t  Event::groupHandle  = xEventGroupCreate();
EventGroupHandle_t  Event::isrGroup     = xEventGroupCreate();