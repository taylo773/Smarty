#include "SmartyPower.h"

SmartyPower pwr; //Instantiate Object 1


void setup() 
{
  pwr.begin();
}

void loop() 
{
  bool chrgStatus = pwr.isCharging();
  uint16_t battVoltage = pwr.getBatteryVoltage();
  //Print information to watch screen
}
