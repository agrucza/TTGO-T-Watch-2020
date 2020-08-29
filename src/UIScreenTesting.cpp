#include "UIScreenTesting.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"
#include "UIContainer.h"
#include "UILabel.h"

UIScreenTesting::UIScreenTesting():UIScreen()
{
    Serial.println("Init UIScreenTesting");
    _label          = "Testing";
    _padding        = 5;
    
    Serial.println("Init container");
    _container      = new UIContainer();
    
    Serial.println("Init labels");
    UILabel* label1 = new UILabel("Test1", &FreeSansBold9pt7b, _container);
    UILabel* label2 = new UILabel("Test2", &FreeSansBold12pt7b, _container, LEFT_CENTER);
    UILabel* label3 = new UILabel("Test3", &FreeSansBold18pt7b, _container, CENTER_CENTER);
    UILabel* label4 = new UILabel("Test4", &FreeSansBold24pt7b, _container, RIGHT_CENTER);
    
    Serial.println("Set label color");
    label1->setTextColor(255,255,255);
    label2->setTextColor(255,255,255);
    label3->setTextColor(255,255,255);
    label4->setTextColor(255,255,255);

    Serial.println("Add labels to container");
    _container->addUIElement(label1);
    _container->addUIElement(label2);
    _container->addUIElement(label3);
    _container->addUIElement(label4);
    
    Serial.println("Init UIScreenTesting done");
}

void UIScreenTesting::draw(bool init, bool task)
{
    if(!task)
    {
        _tft->fillScreen(_backgroundColor);
    }
    _container->draw();
}

void UIScreenTesting::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
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
