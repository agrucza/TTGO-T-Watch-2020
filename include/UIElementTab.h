/**
    This is the UITab class
    @file UITab.h
    @author Alexander Grucza
    @version 0.1 9/19/2020
*/

#ifndef __UITAB_H
#define __UITAB_H

#include <Arduino.h>

#include "UITypes.h"
#include "UIContainer.h"

class UITab : public UIContainer{
    UIContainer* _tabIcons      = nullptr;
    UIContainer* _tabContent    = nullptr;
    
    public:
        UITab(UIContainer* parent, UIEAlignment_t alignment);
        void            addTab(String tabName, String icon);
        UIContainer*    getTabContent(String name){return (UIContainer*)_tabContent->getElementByName(name);};
        void            addElementToTabContent(String tabName, UIElement* element);
};

#endif /*__UITAB_H */
