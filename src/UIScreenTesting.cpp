#include "UIScreenTesting.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

UIScreenTesting::UIScreenTesting(){
    _gui            = gui;
    _tft            = _gui->getTFT();
    _label          = "Testing";
    _padding        = 5;

    LV_IMG_DECLARE(bg);
    LV_FONT_DECLARE(Ubuntu);
    
    /*Create a screen*/
    _screen = lv_obj_create(NULL, NULL);
    lv_scr_load(_screen);          /*Load the screen*/

    //Create wallpaper
    void *images[] = {(void *) &bg};
    lv_obj_t *scr = lv_scr_act();
    lv_obj_t *img_bin = lv_img_create(scr, NULL);  /*Create an image object*/
    lv_img_set_src(img_bin, images[0]);
    lv_obj_align(img_bin, NULL, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_t *timeLabel = nullptr;
    
    //! main
    lv_style_t mainStyle;
    lv_style_init(&mainStyle);
    
    lv_style_set_radius(&mainStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color(&mainStyle, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&mainStyle, LV_OBJ_PART_MAIN, LV_OPA_0);
    lv_style_set_border_width(&mainStyle, LV_OBJ_PART_MAIN, 0);
    lv_style_set_text_color(&mainStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    lv_style_set_image_recolor(&mainStyle, LV_OBJ_PART_MAIN, LV_COLOR_WHITE);
    
    //! Time
    static lv_style_t timeStyle;
    lv_style_copy(&timeStyle, &mainStyle);
    lv_style_set_text_font(&timeStyle, LV_STATE_DEFAULT, &Ubuntu);

    timeLabel = lv_label_create(_screen, NULL);
    lv_obj_add_style(timeLabel, LV_OBJ_PART_MAIN, &timeStyle);
    GUI::updateTime(timeLabel);
    /*
    // Create 2 buttons
    lv_obj_t * btn1 = lv_btn_create(_screen, NULL);     // Create a button on the screen
    lv_btn_set_fit(btn1, true);                         // Enable to automatically set the size according to the content
    lv_obj_set_pos(btn1, 60, 40);              	        // Set the position of the button

    lv_obj_t * btn2 = lv_btn_create(_screen, btn1);     // Copy the first button
    lv_obj_set_pos(btn2, 180, 80);                      // Set the position of the button

    // Add labels to the buttons
    lv_obj_t * label1 = lv_label_create(btn1, NULL);	// Create a label on the first button
    lv_label_set_text(label1, "Button 1");          	// Set the text of the label

    lv_obj_t * label2 = lv_label_create(btn2, NULL);  	// Create a label on the second button
    lv_label_set_text(label2, "Button 2");            	// Set the text of the label

    // Delete the second label
    lv_obj_del(label2);
    */
    /*
    _container      = new UIContainer(NULL); 

    UILabel* label1 = new UILabel("Test1", &FreeSansBold9pt7b, _container);
    UILabel* label2 = new UILabel("Test2", &FreeSansBold12pt7b, _container);
    UILabel* label3 = new UILabel("Test3", &FreeSansBold18pt7b, _container);
    UILabel* label4 = new UILabel("Test4", &FreeSansBold24pt7b, _container);

    label1->setTextColor(255,255,255);
    label2->setTextColor(255,255,255);
    label3->setTextColor(255,255,255);
    label4->setTextColor(255,255,255);

    _container->addUIElement(label1);
    _container->addUIElement(label2);
    _container->addUIElement(label3);
    _container->addUIElement(label4);
    */
}

void UIScreenTesting::draw(bool init, bool task)
{
    if(!task)
    {
        //_tft->fillScreen(TFT_BLACK);
    }
    //_container->draw();
    lv_scr_load(_screen);          /*Load the screen*/
}

void UIScreenTesting::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void UIScreenTesting::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    switch (touchType)
    {
    case TouchMetrics::SWIPE_BOTTOM:
        break;
    case TouchMetrics::SWIPE_BOTTOM_EDGE:
        break;
    case TouchMetrics::SWIPE_LEFT:
        break;
    case TouchMetrics::SWIPE_LEFT_EDGE:
        break;
    case TouchMetrics::SWIPE_RIGHT:
        break;
    case TouchMetrics::SWIPE_RIGHT_EDGE:
        break;
    case TouchMetrics::SWIPE_TOP:
        break;
    case TouchMetrics::SWIPE_TOP_EDGE:
        break;
    case TouchMetrics::TOUCH:
        //_container->touchAction(lastX, lastY, deltaX, deltaY, touchType);
        break;    
    default:
        break;
    }
}
