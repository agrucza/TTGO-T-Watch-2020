/**
    This is the UISideMenu class
    @file UISideMenu.h
    @author Alexander Grucza
    @version 0.1 9/19/2020
*/

#ifndef __UISIDEMENU_H
#define __UISIDEMENU_H

#include <Arduino.h>

#include "UITypes.h"
#include "UIContainer.h"

class UISideMenu : public UIContainer{
    public:
        UISideMenu(UIContainer* parent);
};

#endif /*__UICONTAINER_H */
