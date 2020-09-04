#include "config.h"
#include "LilyGoWatch.h"

#include "UIScreenTesting.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIElementSwitch.h"
#include "UIElementTextInput.h"
#include "UIElementCheckbox.h"
#include "UIElementButton.h"

UIScreenTesting::UIScreenTesting():UIScreen("Testing")
{
    Serial.println("Init UIScreenTesting");
    _screenContainer->setBackgroundColor(FLAT_UI_V1_POMEGRANATE);
    _contentContainer->setBackgroundColor(FLAT_UI_V1_PUMPKIN);
    
    UIElementLabel* label1 = new UIElementLabel("Test1", &FreeSansBold9pt7b, _contentContainer,ORIENTATION_LEFT);
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    _contentContainer->addUIElement(label1);
    
    Serial.println("Create switches");
    UIElementSwitch* switch1 = new UIElementSwitch("TestSwitch1", &FreeSansBold9pt7b, _contentContainer, ORIENTATION_RIGHT);
    switch1->setTextColor(FLAT_UI_V1_CLOUDS);
    switch1->setEnabled(false);
    /*
    ui_event_data_t eventData;
    eventData.screen = this;
    eventData.source = switch1;
    switch1->setEventData(&eventData);
    switch1->setEventCallback(GUI::handleEventCallback);
    */
    _contentContainer->addUIElement(switch1);
    
    Serial.println("Create text input");
    UIElementTextInput* input1 = new UIElementTextInput("ssid", &FreeSansBold9pt7b, _contentContainer);
    _contentContainer->addUIElement(input1);
    
    Serial.println("Create checkbox");
    UIElementCheckbox* checkbox1 = new UIElementCheckbox("checkbox1", &FreeSansBold9pt7b, _contentContainer, ORIENTATION_RIGHT);
    _contentContainer->addUIElement(checkbox1);

    /*
    UIContainer* modal = new UIContainer(this);
    modal->setPadding(10);
    modal->setBackgroundColor(FLAT_UI_V1_CLOUDS);
    */
    
    Serial.println("Creating buttonContainer");
    UIContainer* buttonContainer = new UIContainer(_contentContainer, SIZE_ELEMENT, ALIGNMENT_HORIZONTAL_FILL);
    
    _contentContainer->addUIElement(buttonContainer);
    buttonContainer->setBackgroundColor(FLAT_UI_V1_MIDNIGHT_BLUE);

    Serial.println("Create horizontal buttons");
    UIElementButton* button1 = new UIElementButton("click me", &FreeSansBold9pt7b, buttonContainer, SIZE_ELEMENT);
    
    //eventData.screen    = this;
    //eventData.source    = button1;
    //eventData.event     = EVENT_OPEN_MODAL;
    //button1->setEventData(&eventData);
    //button1->setEventCallback(GUI::handleEventCallback);
    
    buttonContainer->addUIElement(button1);
    
    UIElementButton* button2 = new UIElementButton("click me 2", &FreeSansBold9pt7b, buttonContainer, SIZE_ELEMENT);
    buttonContainer->addUIElement(button2);
    
    UIElementButton* button3 = new UIElementButton("click me 3", &FreeSansBold9pt7b, buttonContainer, SIZE_ELEMENT);
    buttonContainer->addUIElement(button3);
    
    UIElementButton* button4 = new UIElementButton("click me 4", &FreeSansBold9pt7b, buttonContainer, SIZE_ELEMENT);
    buttonContainer->addUIElement(button4);


    Serial.println("Create vertical buttons");
    UIElementButton* button5 = new UIElementButton("click me", &FreeSansBold9pt7b, _contentContainer, SIZE_ELEMENT);
    _contentContainer->addUIElement(button5);
    
    UIElementButton* button6 = new UIElementButton("click me 2", &FreeSansBold9pt7b, _contentContainer, SIZE_ELEMENT);
    _contentContainer->addUIElement(button6);
    
    UIElementButton* button7 = new UIElementButton("click me 3", &FreeSansBold9pt7b, _contentContainer, SIZE_ELEMENT);
    _contentContainer->addUIElement(button7);
    /*
    UIElementButton* button8 = new UIElementButton("click me 4", &FreeSansBold9pt7b, _contentContainer, SIZE_ELEMENT);
    _contentContainer->addUIElement(button8);
    
    UIElementButton* button9 = new UIElementButton("click me 5", &FreeSansBold9pt7b, _contentContainer, SIZE_ELEMENT);
    _contentContainer->addUIElement(button9);
    
    UIElementButton* button10 = new UIElementButton("click me 6", &FreeSansBold9pt7b, _contentContainer, SIZE_ELEMENT);
    _contentContainer->addUIElement(button10);
    */
    Serial.println("Init UIScreenTesting done");
}

void UIScreenTesting::draw(bool init, bool task)
{
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
    _screenContainer->touchAction(lastX, lastY, deltaX, deltaY, touchType);
    /*
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
    case TouchMetrics::TOUCH_RELEASE:
        _screenContainer->touchAction(lastX, lastY, deltaX, deltaY, TouchMetrics::TOUCH_RELEASE);
        break;
    default:
        break;
    }
    */
}

void UIScreenTesting::elementEventHandler(ui_event_data_t* eventData)
{
    
}
