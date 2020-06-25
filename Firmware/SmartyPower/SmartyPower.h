/*
 * DESCRIPTION
 */

#ifndef SmartyPower_h
#define SmartyPower_h

#include <Arduino.h>

class SmartyPower {
  
  private: //Can be only accessed within Class Files (like .cpp)

  public: //Can be accessed outside Class (like Main Code File or Other Classes)

    SmartyPower();
    void begin();
    
    bool isCharging();
    uint16_t getBatteryVoltage();

    void enableGPS();
    void disableGPS();

    void enableMP3();
    void disableMP3();
    
};

#endif
