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
    public:
        UITab(UIContainer* parent, UIEAlignment_t alignment);
        void    addTab(String name, String icon);
        void    addElementToTabContent(String name, UIElement* element);
};

#endif /*__UITAB_H */
