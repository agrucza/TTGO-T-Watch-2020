#include "UIScreenMain.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

UIScreenMain::UIScreenMain():UIScreen()
{
    _label              = "Launcher";
    _showInLauncher     = false;
    
    // Create a container
    _container = lv_page_create(lv_scr_act(), NULL);

    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);
    
    lv_obj_set_size(_container, TFT_WIDTH, TFT_HEIGHT);
    lv_obj_align(_container, NULL, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_add_style(_container,LV_CONT_PART_MAIN,&GUI::borderlessStyle);

    lv_obj_t* cont = lv_page_get_scrl(_container);

    lv_cont_set_layout(cont,LV_LAYOUT_GRID);

    updateLauncherList();
}

void UIScreenMain::updateLauncherList()
{
    std::vector<screens_t> tmp = _gui->getUIScreensForLauncher();
    _callbackData.clear();
    _launcherIcons.clear();

    for(uint8_t i=0; i<tmp.size(); i++)
    {
        screens_t screen = static_cast<screens_t>(tmp[i]);
        icon_t icon;
        _callbackData.push_back(new ScreenCallback(this, CALLBACK_SWITCH_SCREEN,screen));

        _launcherIcons.push_back(icon);
        _launcherIcons[i].obj = lv_cont_create(_container,NULL);

        // setup callback event
        lv_obj_set_user_data(_launcherIcons[i].obj, _callbackData[i]);
        lv_obj_set_event_cb(_launcherIcons[i].obj,GUI::screenEventCallback);

        lv_cont_set_fit(_launcherIcons[i].obj, LV_FIT_TIGHT);
        lv_cont_set_layout(_launcherIcons[i].obj, LV_LAYOUT_ROW_TOP);
        //lv_obj_add_style(icons[i],LV_CONT_PART_MAIN,&GUI::borderlessStyle);
        lv_obj_t* iconLabel = lv_label_create(_launcherIcons[i].obj,NULL);
        lv_label_set_text(iconLabel, LV_SYMBOL_SETTINGS);
        
        _launcherIcons[i].label = _gui->getUIScreenLabel(tmp[i]);
        lv_obj_t* textLabel = lv_label_create(_launcherIcons[i].obj,NULL);
        lv_label_set_text(textLabel,_launcherIcons[i].label);
    }
}

void UIScreenMain::eventCallback(lv_obj_t* obj, lv_event_t event, ScreenCallback* callback)
{
    
}

void UIScreenMain::lvUpdateTask(struct _lv_task_t* data)
{
    if(_launcherIcons.size() < 1)
    {
        updateLauncherList();
    }
}
