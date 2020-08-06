/*
Copyright (c) 2019 lewis he
This is just a demonstration. Most of the functions are not implemented.
The main implementation is low-power standby.
The off-screen standby (not deep sleep) current is about 4mA.
Select standard motherboard and standard backplane for testing.
Created by Lewis he on October 10, 2019.
*/

// Please select the model you want to use in config.h
#include "config.h"
#include <FS.h>
#include <SPI.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include <soc/rtc.h>
#include "esp_wifi.h"
#include "esp_sleep.h"
#include <WiFi.h>

#include "GUI.h"
#include "Energy.h"

#define DEFAULT_SCREEN_TIMEOUT  30*1000

TTGOClass *ttgo;
GUI *gui;

void setup()
{
    Serial.begin(115200);
    
    if (!SPIFFS.begin())
    {
        Serial.println("SPIFFS initialisation failed!");
        while (1) yield(); // Stay here twiddling thumbs waiting
    }
    
    ttgo = TTGOClass::getWatch();

    //Initialize TWatch
    ttgo->begin();

    Energy::setup(ttgo, gui);

    // Turn on the IRQ used
    Energy::setupAXPIRQ();

    // Turn off unused power
    Energy::disableUnusedPower();

    Energy::setupIRQ();

    //Check if the RTC clock matches, if not, use compile time
    ttgo->rtc->check();

    //Synchronize time to system time
    ttgo->rtc->syncToSystem();

    //Setting up the network
    Energy::network();

    //Execute your own GUI interface
    gui->setTTGO(ttgo);
    gui->init();
}

void loop()
{
    Energy::checkIRQ();
    GUI::checkTouchScreen();
    
    if (ttgo->bl->isOn() && GUI::getInactivityTime() > DEFAULT_SCREEN_TIMEOUT) {
        Energy::lowEnergy();
    }
    
    delay(50);
}