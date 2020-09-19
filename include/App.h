/**
    This is the UI class
    @file gui.h
    @author Alexander Grucza
    @version 0.1 7/24/2020
*/

#ifndef __APP_H
#define __APP_H

#include <Arduino.h>

#include "TouchMetrics.h"
#include "UIColors.h"
#include "UITypes.h"

class GUI;
class TFT_eSPI;
class UIContainer;

class App{
    protected:
        GUI*            _gui;
        TFT_eSPI*       _tft;
        String          _label;
        bool            _showHeader         = true;
        bool            _acceptsGlobalTouch = true;
        bool            _showInLauncher     = true;
        uint16_t        _textColor          = FLAT_UI_V1_CLOUDS;
        uint16_t        _bgColor            = FLAT_UI_V1_WET_ASPHALT;
        uint16_t        _iconColor          = FLAT_UI_V1_PETER_RIVER;
        uint8_t         _iconSizeX          = 1;
        uint8_t         _iconSizeY          = 1;
        uint8_t         _padding            = 5;
        UIContainer*    _appContainer       = nullptr;
        UIContainer*    _menuContainer      = nullptr;
        UIContainer*    _contentContainer   = nullptr;
        
    public:
        App(String label, bool showHeader = true);
        bool            acceptsGlobalTouch(){return _acceptsGlobalTouch;};
        bool            getShowInLauncher(){return _showInLauncher;};
        uint8_t         getIconSizeX(){return _iconSizeX;};
        uint8_t         getIconSizeY(){return _iconSizeY;};
        String          getLabel(){return _label;};
        bool            getShowHeader(){return _showHeader;};
        void            clean();
        uint16_t        getBackgroundColor(){return _bgColor;};
        
        virtual void    draw(bool init = false, bool task = false) = 0;
        virtual void    drawIcon(uint16_t x, uint16_t y, uint16_t w, uint16_t h) = 0;
        virtual void    touchAction(int16_t lastX, int16_t lastY, int16_t deltaX, int16_t deltaY, TouchMetrics::touch_t touchType) = 0;
        virtual void    elementEventHandler(ui_event_data_t* eventData) = 0;
        virtual void    backgroundTaskHandler() = 0;
};

#endif /*__APP_H */