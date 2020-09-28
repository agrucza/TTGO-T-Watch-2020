#include "config.h"
#include "LilyGoWatch.h"

#include "UIElementTab.h"
#include "UIElementLabel.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup18pt7b.h"

UITab::UITab(UIContainer* parent, UIEAlignment_t alignment)
:UIContainer::UIContainer(parent, SIZE_FULL, alignment)
{
    Serial.println("Init UITab");
    _padding = 0;
    
    /*
     * TODO: construct two elements
     * - first element will be the container for the tab icons
     * - second element will be the container for the "tab page" container
     * 
     * The idea is:
     * 1. click on an icon will get its position
     * 2. the position of the icon clicked is used to draw the container of the same position
     * (i.e. second icon is clicked and second "container/element" and its content is drawn instead of all containers/elements)
     */
    
    // just create tabs straight ahead addTab will take care of container init
    // create first tab for apps main/home
    addTab("Home", UIICON_HOME);

    // create second tab for settings
    addTab("Settings", UIICON_SUP_GEAR);
}

void UITab::addTab(String tabName, String icon)
{
    Serial.println("Adding Tab");

    // check if we already have an icon container
    if(_tabIcons == nullptr)
    {
        Serial.println("No icons container - creating");
        // we assume we have no icon container
        // create tab icon container
        _tabIcons = new UIContainer(this, SIZE_ELEMENT, (_alignment == ALIGNMENT_HORIZONTAL?ALIGNMENT_VERTICAL:ALIGNMENT_HORIZONTAL));
        _tabIcons->setPadding(0);
        _tabIcons->setBackgroundColor(FLAT_UI_V1_MIDNIGHT_BLUE);
        Serial.println("Adding icons container to tab");
        addUIElement(_tabIcons);
    }

    // create icon for content
    UIElementLabel* labelIcon = new UIElementLabel(icon, &IconsFontsSup18pt7b, _tabIcons);
    labelIcon->setName(tabName);
    _tabIcons->addUIElement(labelIcon);
    
    // check if we already have a content container
    if(_tabContent == nullptr)
    {
        Serial.println("No content container - creating");
        // we assume we have no content container
        // create tab content container
        _tabContent = new UIContainer(this, SIZE_FULL);
        _tabContent->setPadding(0);
        Serial.println("Adding content container to tab");
        addUIElement(_tabContent);
    }

    // create tab content container
    UIContainer* newTabContent = new UIContainer(_tabContent);
    newTabContent->setName(tabName);
    _tabContent->addUIElement(newTabContent);
}

void UITab::addElementToTabContent(String tabName, UIElement* element)
{
    Serial.println("Adding element to tab");
    UIContainer* tabContent = (UIContainer*)_tabContent->getElementByName(tabName);
    if(tabContent != nullptr)
    {
        Serial.println("Tab content for " + tabName + " found");
        tabContent->addUIElement(element);
    }
}