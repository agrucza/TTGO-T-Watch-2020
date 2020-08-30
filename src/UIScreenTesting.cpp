#include "UIScreenTesting.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIElementSwitch.h"

UIScreenTesting::UIScreenTesting():UIScreen()
{
    Serial.println("Init UIScreenTesting");
    _label          = "Testing";
    _padding        = 5;
    
    Serial.println("Init container");
    _container      = new UIContainer();
    
    Serial.println("Init labels");
    UIElementLabel* label1 = new UIElementLabel("Test1", &FreeSansBold9pt7b, _container,LEFT_CENTER);
    UIElementLabel* label2 = new UIElementLabel("Test2", &FreeSansBold12pt7b, _container, CENTER_CENTER);
    UIElementLabel* label3 = new UIElementLabel("Test3", &FreeSansBold18pt7b, _container, RIGHT_CENTER);
    
    Serial.println("Set label color");
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    label2->setTextColor(FLAT_UI_V1_CLOUDS);
    label3->setTextColor(FLAT_UI_V1_CLOUDS);

    Serial.println("Add labels to container");
    _container->addUIElement(label1);
    _container->addUIElement(label2);
    _container->addUIElement(label3);

    Serial.println("Create switches");
    // test with new elements
    UIElementSwitch* switch1 = new UIElementSwitch("TestSwitch1", &FreeSans9pt7b, _container);
    UIElementSwitch* switch2 = new UIElementSwitch("TestSwitch2", &FreeSans12pt7b, _container);

    Serial.println("Switches text color");
    switch1->setTextColor(FLAT_UI_V1_CLOUDS);
    switch2->setTextColor(FLAT_UI_V1_CLOUDS);

    Serial.println("Switches enablement");
    switch1->setEnabled(false);
    switch2->setEnabled(true);

    Serial.println("switch1 event data");
    ui_event_data_t eventData;
    eventData.screen = this;
    eventData.source = switch1;
    Serial.println(eventData.screen->getLabel());
    Serial.println("switch1 set event data");
    switch1->setEventData(&eventData);

    Serial.println("switch1 set callback");
    switch1->setEventCallback(GUI::handleEventCallback);

    Serial.println("Add switches to container");
    _container->addUIElement(switch1);
    _container->addUIElement(switch2);

    Serial.println("Init UIScreenTesting done");
}

void UIScreenTesting::draw(bool init, bool task)
{
    if(!task)
    {
        _tft->fillScreen(_backgroundColor);
    }
    _container->draw(task);
}

void UIScreenTesting::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    _tft->fillRect(x,y,w,h, _iconColor);
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->drawString(
        "TEST",
        x + (w/2),
        y + (h/2)
    );
}

void UIScreenTesting::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch (touchType)
    {
    case TouchMetrics::SWIPE_BOTTOM:
        break;
    case TouchMetrics::SWIPE_BOTTOM_EDGE:
        break;
    case TouchMetrics::SWIPE_LEFT:
        break;
    case TouchMetrics::SWIPE_LEFT_EDGE:
        break;
    case TouchMetrics::SWIPE_RIGHT:
        break;
    case TouchMetrics::SWIPE_RIGHT_EDGE:
        break;
    case TouchMetrics::SWIPE_TOP:
        break;
    case TouchMetrics::SWIPE_TOP_EDGE:
        break;
    case TouchMetrics::TOUCH:
        _container->touchAction(lastX, lastY, deltaX, deltaY, TouchMetrics::TOUCH);
        break;
    default:
        break;
    }
}

void UIScreenTesting::elementEventHandler(ui_event_data_t* eventData)
{
    
}
