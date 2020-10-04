#include "AppLauncher.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

AppLauncher::AppLauncher():App("Launcher", false)
{
    _container = lv_page_create(lv_scr_act(), NULL);
    lv_cont_set_layout(lv_page_get_scrollable(_container), LV_LAYOUT_GRID);
    lv_obj_set_size(_container, TFT_WIDTH, TFT_HEIGHT);
    
    lv_obj_set_hidden(_container, true);
    lv_obj_move_background(_container);

    lv_obj_add_style(_container, LV_CONT_PART_MAIN, &GUI::styleBorderless);

    lv_obj_set_style_local_pad_all(_container, LV_PAGE_PART_BG, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_pad_top(_container, LV_PAGE_PART_BG, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(_container, LV_PAGE_PART_BG, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_bottom(_container, LV_PAGE_PART_BG, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_left(_container, LV_PAGE_PART_BG, LV_STATE_DEFAULT, 0);

    std::vector<App*> apps = _gui->getAppsForLauncher();

    for(uint8_t i = 0; i < apps.size(); i++) {
        lv_obj_t * holder = lv_cont_create(_container, NULL);
        
        _callbackData = new AppCallback(this, CALLBACK_SWITCH_APP, apps[i]);
        lv_obj_set_user_data(holder, _callbackData);
        lv_obj_set_event_cb(holder, GUI::appEventCallback);
        
        lv_obj_add_style(holder, LV_CONT_PART_MAIN, &GUI::styleBorderless);
        lv_obj_set_style_local_radius(holder, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);
        lv_obj_set_style_local_bg_color(holder, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAGENTA);

        lv_obj_set_size(
            holder,
            lv_obj_get_width_grid(lv_page_get_scrollable(_container), 4, 2),
            lv_obj_get_width_grid(lv_page_get_scrollable(_container), 4, 2)
        );
        
        lv_cont_set_layout(holder, LV_LAYOUT_PRETTY_MID);

        lv_obj_t * label = lv_label_create(holder, NULL);
        lv_label_set_text(label, apps[i]->getLabel().c_str());
    }
}

void AppLauncher::eventCallback(lv_obj_t* obj, lv_obj_t* ext, lv_event_t event, AppCallback* callback)
{
    
}

void AppLauncher::updateTask(struct _lv_task_t* data)
{

}
