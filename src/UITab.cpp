#include "config.h"
#include "LilyGoWatch.h"

#include "UITab.h"
#include "UIElementLabel.h"
#include "UIIcons.h"
#include "fonts/IconsFontsSup18pt7b.h"

UITab::UITab(UIContainer* parent, UIEAlignment_t alignment)
:UIContainer::UIContainer(parent, SIZE_FULL, (alignment == ALIGNMENT_HORIZONTAL?ALIGNMENT_VERTICAL:ALIGNMENT_HORIZONTAL))
{
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
    
    UIElementLabel* labelMenu1 = new UIElementLabel(UIICON_SUP_GEAR, &IconsFontsSup18pt7b, this);
    this->addUIElement(labelMenu1);
}