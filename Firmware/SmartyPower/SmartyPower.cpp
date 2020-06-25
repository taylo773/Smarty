#include "SmartyPower.h"

/* Variable Types
 * uint8_t = unsigned 8 bit integer [0,255]
 * uint16_t = unsigned 16 bit integer [0,65355]
 * int8_t = signed 8 bit integer [-127,127]
 * int16_t = signed 16 bit integer [-32768, 32767]
 */

//Global Variables to .cpp File
const uint8_t chrgPin = 27;
const uint8_t battPin = A4;
const uint8_t gpsPwrPin = 2;
const uint16_t VDD = 3300; //Analog Reference Voltage
const uint16_t adcResolution = 1023; 

//Scope resoultion operator = SmartyPower::
SmartyPower::SmartyPower()
{ 
}

void SmartyPower::begin()
{
  pinMode(chrgPin, INPUT);
  pinMode(gpsPwrPin, OUTPUT);
}

//Returns whether or not the battery is charging
bool SmartyPower::isCharging()
{
  return !digitalRead(chrgPin); //Return 0 if Charging, 1 if Not Charging
}

uint16_t SmartyPower::getBatteryVoltage()
{
  //Voltage Divider: Vlipo*(R8/(R8+R7)) where R7=R8
  uint16_t val = analogRead(battPin); //10-bit ADC, Return a Number between 0(0V) and 1023(3.3V)
  uint16_t voltage = VDD * (val / (float)adcResolution); //Floating Point Math
  return 2*voltage; //Voltage Division?
}

void SmartyPower::enableGPS()
{
  digitalWrite(gpsPwrPin, HIGH); //Enables regulator, turning ON GPS Circuit
}

void SmartyPower::disableGPS()
{
  digitalWrite(gpsPwrPin, LOW); //Enables regulator, turning OFF GPS Circuit
}

void SmartyPower::enableMP3()
{

}

void SmartyPower::disableMP3()
{

}
