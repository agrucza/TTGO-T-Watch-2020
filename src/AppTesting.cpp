#include "config.h"
#include "LilyGoWatch.h"

#include "AppTesting.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementTab.h"
#include "UIElementLabel.h"
#include "UIElementSwitch.h"
#include "UIElementTextInput.h"
#include "UIElementCheckbox.h"
#include "UIElementButton.h"

AppTesting::AppTesting():App("Testing")
{
    Serial.println("#######################");
    Serial.println("#   Init AppTesting   #");
    Serial.println("#######################");

    UIElementTab* tab = (UIElementTab*)_contentContainer;
    UIContainer* tabContentHome = tab->getTabContent("Home");
    Serial.println("Create label");
    UIElementLabel* label1 = new UIElementLabel("Test1", &FreeSansBold9pt7b, tabContentHome, ORIENTATION_LEFT);
    label1->setTextColor(FLAT_UI_V1_CLOUDS);
    tab->addElementToTabContent("Home", label1);
    
    Serial.println("Create switches");
    UIElementSwitch* switch1 = new UIElementSwitch("TestSwitch1", &FreeSansBold9pt7b, tabContentHome, ORIENTATION_RIGHT);
    switch1->setTextColor(FLAT_UI_V1_CLOUDS);
    switch1->setEnabled(false);
    
    //ui_event_data_t eventData;
    //eventData.screen = this;
    //eventData.source = switch1;
    //switch1->setEventData(&eventData);
    //switch1->setEventCallback(GUI::handleEventCallback);
    
    tab->addElementToTabContent("Home", switch1);

    UIElementSwitch* switch2 = new UIElementSwitch("TestSwitch2", &FreeSansBold9pt7b, tabContentHome, ORIENTATION_RIGHT);
    switch2->setTextColor(FLAT_UI_V1_CLOUDS);
    switch2->setEnabled(true);
    tab->addElementToTabContent("Home", switch2);
    
    Serial.println("Create text input");
    UIElementTextInput* input1 = new UIElementTextInput("ssid", &FreeSansBold9pt7b, tabContentHome);
    tab->addElementToTabContent("Home", input1);
    
    Serial.println("Create checkbox");
    UIElementCheckbox* checkbox1 = new UIElementCheckbox("checkbox1", &FreeSansBold9pt7b, tabContentHome, ORIENTATION_RIGHT);
    tab->addElementToTabContent("Home", checkbox1);

    //UIContainer* modal = new UIContainer(this);
    //modal->setPadding(10);
    //modal->setBackgroundColor(FLAT_UI_V1_CLOUDS);
    
    Serial.println("Creating buttonContainer");
    UIContainer* buttonContainer = new UIContainer(tabContentHome, SIZE_ELEMENT, ALIGNMENT_HORIZONTAL_FILL);
    //buttonContainer->setBackgroundColor(FLAT_UI_V1_CARROT);
    tab->addElementToTabContent("Home", buttonContainer);

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
    UIElementButton* button5 = new UIElementButton("click me", &FreeSansBold9pt7b, tabContentHome, SIZE_FULL);
    tab->addElementToTabContent("Home", button5);
    
    UIElementButton* button6 = new UIElementButton("click me 2", &FreeSansBold9pt7b, tabContentHome, SIZE_ELEMENT);
    tab->addElementToTabContent("Home", button6);
    
    UIElementButton* button7 = new UIElementButton("click me 3", &FreeSansBold9pt7b, tabContentHome, SIZE_ELEMENT);
    tab->addElementToTabContent("Home", button7);
    
    UIElementButton* button8 = new UIElementButton("click me 4", &FreeSansBold9pt7b, tabContentHome, SIZE_ELEMENT);
    tab->addElementToTabContent("Home", button8);
    
    UIElementButton* button9 = new UIElementButton("click me 5", &FreeSansBold9pt7b, tabContentHome, SIZE_ELEMENT);
    tab->addElementToTabContent("Home", button9);
    
    UIElementButton* button10 = new UIElementButton("click me 6", &FreeSansBold9pt7b, tabContentHome, SIZE_ELEMENT);
    tab->addElementToTabContent("Home", button10);
    
    Serial.println("Init AppTesting done");
}

void AppTesting::draw(bool init, bool task)
{
    if(!task)
    {
        _tft->fillScreen(_bgColor);
    }
    _appContainer->draw(task);
}

void AppTesting::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    _tft->fillRect(x,y,w,h, _iconColor);
    _tft->setFreeFont(&FreeSansBold9pt7b);
    _tft->drawString(
        "TEST",
        x + (w/2),
        y + (h/2)
    );
}

void AppTesting::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    _appContainer->touchAction(lastX, lastY, deltaX, deltaY, touchType);
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
        _appContainer->touchAction(lastX, lastY, deltaX, deltaY, TouchMetrics::TOUCH_RELEASE);
        break;
    default:
        break;
    }
    */
}

void AppTesting::elementEventHandler(ui_event_data_t* eventData)
{
    
}
