/**
    This is the UIElementTab class
    @file UITab.h
    @author Alexander Grucza
    @version 0.1 9/19/2020
*/

#ifndef __UIELEMENTTAB_H
#define __UIELEMENTTAB_H

#include <Arduino.h>

#include "UITypes.h"
#include "UIContainer.h"

class UIElementTab : public UIContainer{
    UIContainer* _tabIcons      = nullptr;
    UIContainer* _tabContent    = nullptr;
    
    public:
        UIElementTab(UIContainer* parent, UIEAlignment_t alignment);
        void            addTab(String tabName, String icon);
        UIContainer*    getTabContent(String name){return (UIContainer*)_tabContent->getElementByName(name);};
        void            setTabContent(String name);
        void            addElementToTabContent(String tabName, UIElement* element);
};

#endif /*__UIELEMENTTAB_H */
