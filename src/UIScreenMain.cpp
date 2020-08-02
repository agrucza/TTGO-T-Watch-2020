#include "UIScreenMain.h"
#include "GUI.h"
#include "config.h"
#include "LilyGoWatch.h"

extern GUI *gui;

UIScreenMain::UIScreenMain(){
    _gui            = gui;
    _tft            = _gui->getTFT();
    _label          = "Main";
    _iconSizeX      = _iconSizeY = 2;
    _iconsMax       = 4;
    _padding        = 5;
    
    _iconAreaWidth  = TFT_WIDTH - (2*_padding);
    _iconAreaHeight = TFT_HEIGHT - (2*_padding);
    _iconW          = (_iconAreaWidth - ((_iconsMax-1)*2))/_iconsMax;
    _iconH          = (_iconAreaHeight - ((_iconsMax-1)*2))/_iconsMax;

    // setup screens
    _setScreenIcon(SCREEN_CALENDAR, 0, 0);
    _setScreenIcon(SCREEN_SETTINGS, 2, 0);
}

void UIScreenMain::_setScreenIcon(screens_t screen, uint8_t posX, uint8_t posY)
{
    uint8_t iconsAvailableY = _displayIcons.size();
    
    uint8_t iconsX          = _gui->getUIScreenIconWidth(screen);
    uint8_t iconsY          = _gui->getUIScreenIconHeight(screen);
    
    if(iconsAvailableY < (posY + 1 + iconsY)){
        do{
            std::vector<screens_t> row;
            do{
                row.push_back(SCREEN_NONE);
            }while(row.size() < _iconsMax);
            _displayIcons.push_back(row);
        }while(_displayIcons.size() < (posY + 1 + iconsY));
    }

    uint8_t iconsAvailableX = _displayIcons[posX].size();
    
    if((iconsAvailableX <= (posX + 1)) && (iconsAvailableX < (posX + 1 + iconsX)))
    {
        // icon will be too wide but starts within visible area - shorten icon to remaining space
        iconsX = iconsAvailableX - posX;
        // TODO: set icon background to red to notify of wrong assignment?
    }
    
    for(uint8_t y = posY; y < (posY + iconsY); y++)
    {
        for(uint8_t x = posX; x < (posX + iconsX); x++)
        {
            _displayIcons[y][x] = screen;
        }
    }
}

void UIScreenMain::draw(bool init)
{
    uint8_t     iconSizeScreenW = 0;
    uint8_t     iconSizeScreenH = 0;
    char buf[50];

    _tft->fillScreen(TFT_BLACK);
    _tft->setFreeFont(&FreeSansBold9pt7b);
    
    for(uint8_t iconY = 0; iconY < _displayIcons.size(); iconY++)
    {
        std::vector<screens_t> row  = _displayIcons[iconY];
        for(uint8_t iconX = 0; iconX < row.size(); iconX++)
        {
            // check if a screens is set to display an icon
            if(row[iconX] != SCREEN_NONE)
            {
                iconSizeScreenW = _gui->getUIScreenIconWidth(row[iconX]);
                iconSizeScreenH = _gui->getUIScreenIconHeight(row[iconX]);

                // check if icon is bigger than 1x1 and check surrounding icon places
                if(
                    (iconSizeScreenW > 1 || iconSizeScreenH > 1)
                    && (
                        ((iconX>0) && (_displayIcons[iconY][iconX-1] == row[iconX]))
                        || ((iconY>0) && (_displayIcons[iconY-1][iconX] == row[iconX]))
                    )
                )
                {
                    continue;
                }
                
                _gui->drawUIScreenIcon(
                    row[iconX],
                    _padding + (iconX*(_iconW + 2)),
                    _padding + (iconY*(_iconH + 2)),
                    iconSizeScreenW * _iconW + ((iconSizeScreenW-1) * 2),
                    iconSizeScreenH * _iconH + ((iconSizeScreenH-1) * 2)
                );
            }
        }
    }
}

void UIScreenMain::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void UIScreenMain::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    if(touchType == TouchMetrics::TOUCH)
    {
        uint8_t x = (lastX-_padding)/(_iconW+2);
        uint8_t y = (lastY-_padding)/(_iconH+2);
        
        /*
        _tft->setFreeFont(&FreeSansBold9pt7b);
        char buf[20];
        sprintf(buf,"x: %d y: %d s: %d",x,y, _displayIcons[y][x]);
        _tft->drawString(buf,_padding, _padding);
        */
        if(_displayIcons[y][x] != SCREEN_NONE)
        {
            _gui->setScreen(_displayIcons[y][x],true);
        }
    }
    else if (touchType == TouchMetrics::SWIPE_LEFT)
    {
        // go forth in navigation
        /*
        if(_page < _pageMax-1){
            _page++;
            draw();
        }
        */
    }
    else if (touchType == TouchMetrics::SWIPE_RIGHT)
    {
        /*
        // go back in navigation
        if(_page > 0){
            _page--;
            draw();
        }
        */
    }
}
