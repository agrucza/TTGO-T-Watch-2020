/**
    This is the energy class
    @file energy.h
    @author Alexander Grucza
    @version 0.1 7/17/2020
*/

#ifndef __ENERGY_H
#define __ENERGY_H

class TTGOClass;
class GUI;

class Energy {
    static TTGOClass*   _ttgo;
    static GUI*         _gui;
    static bool         _lowEnergy;
    
    public:
        static void     setup(TTGOClass* ttgo, GUI* gui);
        static void     setupAXPIRQ();
        static void     setupIRQ();
        static void     disableUnusedPower();
        static void     network();
        static void     lowEnergy();
        static void     checkIRQ();
        static void     getWakeup();
        static void     setSleep();
};

#endif /*__ENERGY_H */