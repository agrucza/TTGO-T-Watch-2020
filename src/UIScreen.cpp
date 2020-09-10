#include "config.h"
#include "LilyGoWatch.h"

#include "UIScreen.h"

#include "GUI.h"
#include "UIContainer.h"
#include "UIElementLabel.h"
#include "UIColors.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup18pt7b.h"

extern GUI* gui;

UIScreen::UIScreen(String label, bool showHeader)
{
    _gui                = gui;
    _tft                = _gui->getTTGO()->tft;
    _label              = label;
    _showHeader         = showHeader;

    //_screenContainer = new UIContainer(this);
    Serial.println("Creating screenContainer");
    _screenContainer = new UIContainer(this, SIZE_ELEMENT, ALIGNMENT_HORIZONTAL);
    _screenContainer->setPadding(0);
    //create a screen sprite
    TFT_eSprite* sprite = _screenContainer->getSprite();

    Serial.println("Creating menuContainer");
    _menuContainer = new UIContainer(_screenContainer);

    Serial.println("Adding menuContainer to screenContainer");
    _screenContainer->addUIElement(_menuContainer);
    _menuContainer->setPadding(0);

    Serial.print("MenuContainer dim: ");
    Serial.print(_menuContainer->_dimensions.topLeft.x);
    Serial.print(":");
    Serial.print(_menuContainer->_dimensions.topLeft.y);
    Serial.print(":");
    Serial.print(_menuContainer->_dimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(_menuContainer->_dimensions.bottomRight.y);

    Serial.println("Adding label to menuContainer");
    UIElementLabel* labelMenu1 = new UIElementLabel(UIICON_SUP_WRENCH, &IconsFontsSup18pt7b, _menuContainer);
    _menuContainer->addUIElement(labelMenu1);
    
    UIElementLabel* labelMenu2 = new UIElementLabel(UIICON_SUP_TRASH_BIN, &IconsFontsSup18pt7b, _menuContainer);
    _menuContainer->addUIElement(labelMenu2);
    /*
    if(_showHeader)
    {
        UIElementLabel* labelHead = new UIElementLabel(_label, &FreeSansBold9pt7b, _screenContainer, ORIENTATION_RIGHT);
        labelHead->setTextColor(FLAT_UI_V1_CLOUDS);
        labelHead->showLine(true, ORIENTATION_RIGHT);
        _screenContainer->addUIElement(labelHead);
    }
    */

    Serial.print("MenuContainer dim: ");
    Serial.print(_menuContainer->_dimensions.topLeft.x);
    Serial.print(":");
    Serial.print(_menuContainer->_dimensions.topLeft.y);
    Serial.print(":");
    Serial.print(_menuContainer->_dimensions.bottomRight.x);
    Serial.print(":");
    Serial.println(_menuContainer->_dimensions.bottomRight.y);
    
    Serial.println("Creating contentContainer");
    _contentContainer = new UIContainer(_screenContainer, SIZE_FULL);
    Serial.println("Adding contentContainer to screenContainer");
    _screenContainer->addUIElement(_contentContainer);
    
    // setting contentcontainer to have the remaining space of the screencontainer
    //_contentContainer->_dimensions.bottomRight.y = _screenContainer->_dimensions.bottomRight.y - _contentContainer->_dimensions.topLeft.y;
    /*
    Serial.println("Adding label to contentContainer");
    UIElementLabel* labelTest1 = new UIElementLabel("Test", &FreeSansBold9pt7b, _contentContainer);
    _contentContainer->addUIElement(labelTest1);
    */
}

void UIScreen::clean()
{
    _screenContainer->clean();
};