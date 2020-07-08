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

    //Potentiometer to Control Gain of TIA and BPF
    AD5242 ad5245; 
    
    //Gain settings for Digital Potentiometers
    uint8_t R_LEDCurrent; 
    uint8_t R_TIAGain; 
    uint8_t R_PPGGain; 

    bool LEDState; //true = ON, false = OFF


public:

    SmartyPPG(); //Default Constructer- Must be called before setup in .ino code
    void begin(); //Must be called in setup in .ino code

    //Controls LED
    void turnLEDOn();       //Turn LED ON
    void turnLEDOff();      //Turn LED OFF
    bool getLEDStatus() const;
    void setLEDCurrent(uint8_t val);         //Control LED Brightness
    uint8_t getLEDCurrent() const;
    
    //Transimpedance Amplifier (TIA) Gain Control
    void setTIAGain(uint8_t gain);
    uint8_t getTIAGain() const;
    
    //Control Gain of Bandpass Filter (BPF)
    void setPPGGain(uint8_t gain);
    uint8_t getPPGGain() const;

    //Read voltage of PPG Circuit
    uint16_t getTIA() const;            //TIA Voltage
    uint16_t getPPG() const;            //PPG and BPF Voltage

};

#endif /*SmartyPPG_h*/
