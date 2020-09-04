#include "config.h"
#include "LilyGoWatch.h"

#include "UIScreenMain.h"

#include "GUI.h"


UIScreenMain::UIScreenMain():UIScreen("Main", false)
{
    Serial.println("UIScreenMain constructor");
    _iconSizeX      = _iconSizeY = 2;
    _iconsMax       = 4;
    
    _iconAreaWidth  = TFT_WIDTH - (2*_padding);
    _iconAreaHeight = TFT_HEIGHT - (2*_padding);
    _iconW          = (_iconAreaWidth - ((_iconsMax-1)*2))/_iconsMax;
    _iconH          = (_iconAreaHeight - ((_iconsMax-1)*2))/_iconsMax;

    Serial.println("Setting icon positions");
    // setup screens
    _setScreenIcon(SCREEN_CALENDAR, 0, 0);
    _setScreenIcon(SCREEN_SETTINGS, 2, 0);
    _setScreenIcon(SCREEN_TESTING, 3, 0);
    Serial.println("UIScreenMain constructor done");
}

void UIScreenMain::_setScreenIcon(screens_t screen, uint8_t posX, uint8_t posY)
{
    Serial.println("UIScreenMain::_setScreenIcon()");
    Serial.println("UIScreenMain::_setScreenIcon: getting icons width/height");
    uint8_t iconsX  = _gui->getUIScreenIconWidth(screen);
    uint8_t iconsY  = _gui->getUIScreenIconHeight(screen);
    
    Serial.println("UIScreenMain::_setScreenIcon: checking available height icon space");
    while(_displayIcons.size() < (posY + iconsY)){
        std::vector<screens_t> row;
        while(row.size() < _iconsMax){
            row.push_back(SCREEN_NONE);
        }
        _displayIcons.push_back(row);
    }

    uint8_t iconsAvailableX = _displayIcons[posY].size();

    if((iconsAvailableX < posX) && (iconsAvailableX < (posX + iconsX)))
    {
        // icon will be too wide but starts within visible area - shorten icon to remaining space
        iconsX = iconsAvailableX - posX;
        // TODO: set icon background to red to notify of wrong assignment?
    }
    
    Serial.println("UIScreenMain::_setScreenIcon: setting icons");
    for(uint8_t y = posY; y < (posY + iconsY); y++)
    {
        for(uint8_t x = posX; x < (posX + iconsX); x++)
        {
            _displayIcons[y][x] = screen;
        }
    }
    
    Serial.println("UIScreenMain::_setScreenIcon: done");
}

void UIScreenMain::draw(bool init, bool task)
{
    if(!task)
    {
        uint8_t     iconSizeScreenW = 0;
        uint8_t     iconSizeScreenH = 0;

        _tft->fillScreen(_backgroundColor);
    
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
}

void UIScreenMain::drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    
}

void UIScreenMain::touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType)
{
    if(touchType == TouchMetrics::TOUCH_RELEASE)
    {
        uint8_t x = (lastX-_padding)/(_iconW+2);
        uint8_t y = (lastY-_padding)/(_iconH+2);
        
        if(_displayIcons.size()-1 >= y && _displayIcons[y][x] != SCREEN_NONE)
        {
            _gui->setScreen(_displayIcons[y][x], true);
        }
    }
    else if (touchType == TouchMetrics::SWIPE_LEFT)
    {
        // go forth in navigation
        /*
        if(_page < _pageMax-1)
        {
            _page++;
            draw();
        }
        */
    }
    else if (touchType == TouchMetrics::SWIPE_RIGHT)
    {
        /*
        // go back in navigation
        if(_page > 0)
        {
            _page--;
            draw();
        }
        */
    }
}
