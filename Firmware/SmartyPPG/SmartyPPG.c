
#include "Smarty.h"

const uint8_t LEDPin = 30;
const uint8_t PPGPin = A4;
const uint8_t TIAPin = A5;
const uint8_t AD5171_address = 0x2D;


SmartyPPG::SmartyPPG()                 //Default Constructer
{

}

void SmartyPPG::begin()                //Function to Initialize Variables
{
    pinMode(LEDPin, OUTPUT);
    analogReadResolution(12); //12 bits: Returns Number between 0-495
}

//This is Complete
void SmartyPPG::turnLEDOn() const       //Turn LED ON
{
    digitalWrite(LEDPin, HIGH);
}

//This is Complete
void SmartyPPG::turnLEDOff() const      //Turn LED OFF
{
    digitalWrite(LEDPin, LOW);
}

void SmartyPPG::setLEDCurrent()         //Control LED Brightness, AD5171
{
    wire.beginTransmission(AD5171_addres); //Device Address is specified in datasheet
    wire.write(byte(0x00));     //Sends Instruction Byte
    wire.write(val);            //Sends Potentiometer Value byte
    wire.endTransmission();     //Stop Transmitting

    value; //Increment Value
    if (val == 64) //If Reached 64th Position (max)
        val = 0; //Start Over from Lowest Value
    delay(500);
}

uint8_t SmartyPPG::getLEDCurrent() const
{

}

void SmartyPPG::setTIAGain()            //Control Gain of Transimpedance Amplifier (TIA)
{

}

uint8_t SmartyPPG::getTIAGain() const
{

}

void SmartyPPG::setBPFGain()            //Control Gain of Bandpass Filter (PPG)
{

}

uint8_t SmartyPPG::getBPFGain() const
{

}

//This is Complete
uint16_t SmartyPPG::getTIA()            //TIA Voltage
{
    return analogRead(TIAPin);
}

//This is Complete
uint16_t SmartyPPG::getBPF()            //BPF and PPG Voltage
{
    return analogRead(PPGPin);
}

