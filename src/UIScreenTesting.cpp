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
    _screenContainer = new UIContainer(this);
    _screenContainer->setBackgroundColor(FLAT_UI_V1_CARROT);
    UIElementLabel* labelHead = new UIElementLabel(_label, &FreeSansBold9pt7b, _screenContainer,RIGHT_CENTER);
    labelHead->setTextColor(FLAT_UI_V1_CLOUDS);
    
    Serial.println("Add header to screenContainer");
    _screenContainer->addUIElement(labelHead);
    
    _contentContainer = new UIContainer(_screenContainer, SIZE_FULL);
    
    Serial.println("Add contentContainer to screenContainer");
    _screenContainer->addUIElement(_contentContainer);
    
    UIElementLabel* label1 = new UIElementLabel("Test1", &FreeSansBold9pt7b, _contentContainer,LEFT_CENTER);
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    Serial.println("Add element to contentContainer");
    _contentContainer->addUIElement(label1);
    
    UIElementLabel* label2 = new UIElementLabel("Test2", &FreeSansBold12pt7b, _contentContainer,CENTER_CENTER);
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    Serial.println("Add element to contentContainer");
    _contentContainer->addUIElement(label2);
    
    UIElementLabel* label3 = new UIElementLabel("Test3", &FreeSansBold18pt7b, _contentContainer,RIGHT_CENTER);
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    Serial.println("Add element to contentContainer");
    _contentContainer->addUIElement(label3);
    
    Serial.println("Create switches");
    // test with new elements
    UIElementSwitch* switch1 = new UIElementSwitch("TestSwitch1", &FreeSans9pt7b, _contentContainer);
    UIElementSwitch* switch2 = new UIElementSwitch("TestSwitch2", &FreeSans12pt7b, _contentContainer);

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
    _contentContainer->addUIElement(switch1);
    _contentContainer->addUIElement(switch2);
    
    Serial.println("Init UIScreenTesting done");
}

void UIScreenTesting::draw(bool init, bool task)
{
    char buf[50];
    if(!task)
    {
        _tft->fillScreen(_backgroundColor);
    }
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
        _screenContainer->touchAction(lastX, lastY, deltaX, deltaY, TouchMetrics::TOUCH);
        break;
    default:
        break;
    }
}

void UIScreenTesting::elementEventHandler(ui_event_data_t* eventData)
{
    
}
