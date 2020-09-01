#include "UIScreenTesting.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIElementSwitch.h"
#include "UIElementTextInput.h"
#include "UIElementCheckbox.h"

UIScreenTesting::UIScreenTesting():UIScreen("Testing")
{
    Serial.println("Init UIScreenTesting");
    
    UIElementLabel* label1 = new UIElementLabel("Test1", &FreeSansBold9pt7b, _contentContainer,ORIENTATION_LEFT);
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    _contentContainer->addUIElement(label1);
    
    Serial.println("Create switches");
    UIElementSwitch* switch1 = new UIElementSwitch("TestSwitch1", &FreeSansBold9pt7b, _contentContainer, ORIENTATION_LEFT);
    switch1->setTextColor(FLAT_UI_V1_CLOUDS);
    switch1->setEnabled(false);
    ui_event_data_t eventData;
    eventData.screen = this;
    eventData.source = switch1;
    switch1->setEventData(&eventData);
    switch1->setEventCallback(GUI::handleEventCallback);
    _contentContainer->addUIElement(switch1);

    UIElementSwitch* switch2 = new UIElementSwitch("TestSwitch1", &FreeSansBold9pt7b, _contentContainer, ORIENTATION_RIGHT);
    switch2->setTextColor(FLAT_UI_V1_CLOUDS);
    switch2->setEnabled(false);
    _contentContainer->addUIElement(switch2);
    
    Serial.println("Create text input");
    UIElementTextInput* input1 = new UIElementTextInput("ssid", &FreeSansBold9pt7b, _contentContainer);
    _contentContainer->addUIElement(input1);
    
    Serial.println("Create checkbox");
    UIElementCheckbox* checkbox1 = new UIElementCheckbox("checkbox1", &FreeSansBold9pt7b, _contentContainer, ORIENTATION_LEFT);
    _contentContainer->addUIElement(checkbox1);
    
    Serial.println("Create checkbox");
    UIElementCheckbox* checkbox2 = new UIElementCheckbox("checkbox2", &FreeSansBold9pt7b, _contentContainer, ORIENTATION_RIGHT);
    _contentContainer->addUIElement(checkbox2);
        
    Serial.println("Init UIScreenTesting done");
}

void UIScreenTesting::draw(bool init, bool task)
{
    char buf[50];
    if(!task)
    {
        _tft->fillScreen(_backgroundColor);
    }
    _screenContainer->draw(task);
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
