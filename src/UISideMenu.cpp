#include "config.h"
#include "LilyGoWatch.h"

#include "UISideMenu.h"
#include "UIElementLabel.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup18pt7b.h"

UISideMenu::UISideMenu(UIContainer* parent)
:UIContainer::UIContainer(parent, SIZE_ELEMENT, ALIGNMENT_VERTICAL)
{
    _padding = 0;
    
    UIElementLabel* labelMenu1 = new UIElementLabel(UIICON_SUP_WRENCH, &IconsFontsSup18pt7b, this);
    this->addUIElement(labelMenu1);
}