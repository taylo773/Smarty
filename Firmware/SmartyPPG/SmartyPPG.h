//SmartyPPG.h

#ifndef SmartyPPG_h
#define SmartyPPG_h

//Standard Arduino Libraries
#include <Arduino.h>

//Custom External Libraries
#include <AD5242.h> //Linnes Lab Library- Need to Clone


class SmartyPPG
{

private:

    AD5242 ad5245; //Potentiometer to Control Gain of TIA and BPF

    uint8_t LEDCurrent; 
    uint8_t TIAGain; 
    uint8_t BPFGain; 


public:

    SmartyPPG(); //Default Constructer

    void turnLEDOn() const;       //Turn LED ON
    void turnLEDOff() const;      //Turn LED OFF
    void setLEDCurrent();         //Control LED Brightness
    uint8_t getLEDCurrent() const;
    
    void setTIAGain();            //Control Gain of Transimpedance Amplifier (TIA)
    uint8_t getTIAGain() const;
    
    void setBPFGain();            //Control Gain of Bandpass Filter
    uint8_t getBPFGain() const;

    uint16_t getTIA();            //TIA Voltage
    uint16_t getBPF();            //PPG and BPF Voltage

}

#endif /*SmartyPPG_h*/
