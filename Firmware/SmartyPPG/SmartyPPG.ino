#include "SmartyPPG.h"

SmartyPPG ppg;

uint8_t LEDCurrent;
uint8_t LEDStatus;
uint8_t TIAGain;

void setup()
{
  Serial.begin(9600);
  ppg.begin(); //Sets LED Resistance to 63

  //Set LED Current
  ppg.setLEDCurrent(50); //Number between 0 (Low Resistance) - 63 (High Resistance)
}

void loop()
{
  
  //Turn LED ON
  ppg.turnLEDOn();
  delay(2000);

  //Get LED Status
  LEDStatus = ppg.getLEDStatus();
  Serial.print("LED Status: ");
  Serial.println(LEDStatus);

  //Get Current Values
  LEDCurrent = ppg.getLEDCurrent();
  Serial.print("LED Current: ");
  Serial.println(LEDCurrent);
  TIAGain = ppg.getTIAGain();
  Serial.print("TIA Gain: ");
  Serial.println(TIAGain);

  //Turn LED OFF
  ppg.turnLEDOff();
  delay(2000);

  //Get LED Status
  LEDStatus = ppg.getLEDStatus();
  Serial.print("LED Status: ");
  Serial.println(LEDStatus);

  //Get Current Values
  LEDCurrent = ppg.getLEDCurrent();
  Serial.print("LED Current: ");
  Serial.println(LEDCurrent);
  TIAGain = ppg.getTIAGain();
  Serial.print("TIA Gain: ");
  Serial.println(TIAGain);

  //Start Sampling PPG Circuit?

}
