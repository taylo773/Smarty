
#include "SmartyPPG.h"

const uint8_t LEDPin = 2; //Was Pin 30
const uint8_t PPGPin = A4;
const uint8_t TIAPin = A5;
const uint8_t AD5171_address = 0x2D;
const uint8_t AD5242_address = 0x2C;
const uint8_t TIA_upper_bound = 2250;
const uint8_t TIA_lower_bound = 1050;

//Must be called before setup in .ino code
//Default Constructer
SmartyPPG::SmartyPPG()
{
}

//Must be called before setup in .ino code
//Initializes functions, member variables and member objects of PPG Class
void SmartyPPG::begin()                
{
    pinMode(LEDPin, OUTPUT);
    turnLEDOff();
//    analogReadResolution(12); //12 bits: Returns Number between 0-495
//    setLEDCurrent(63); //Smallest LED Current (Largest Resistance)
    ad5242 = AD524X(AD5242_address);

}

//Turns on LED by writing HIGH to pin, LED is driven using NPN bipolar junction transistor (BJT)
void SmartyPPG::turnLEDOn()       //Turn LED ON
{
    digitalWrite(LEDPin, HIGH);
    LEDState = true;
    Serial.println("LED ON");
}

//Turns off LED by writing LOT to pin, LED is driven using NPN bipolar junction transistor (BJT)
void SmartyPPG::turnLEDOff()     //Turn LED OFF
{
    digitalWrite(LEDPin, LOW);
    LEDState = false;
    Serial.println("LED OFF");
}

//Returns whether or not LED is on (true) or off (false)
bool SmartyPPG::getLEDStatus() const
{
    return LEDState;
}

//val       value to write to AD5171, must be between 0 and 63
//
// *val* has an inverse relationship with LED Current
// As val increases, resistance increases, LED Current goes decreases
// As val decreases, resistance decreases, LED Current goes increases
void SmartyPPG::setLEDCurrent(uint8_t val)         //Control LED Brightness, AD5171
{
    if (val > 63) val = 63;

    Wire.beginTransmission(AD5171_address); //Device Address is specified in datasheet
    Wire.write(byte(0x00));     //Sends Instruction Byte
    Wire.write(val);            //Sends Potentiometer Value byte (between 0 and 63)
    Wire.endTransmission();     //Stop Transmitting

    R_LEDCurrent = val;
}

//Returns the setting of digital potentiometer controlling LED Current
uint8_t SmartyPPG::getLEDCurrent() const
{
    return R_LEDCurrent;
}

//Setting the digital potentiometer (AD5242) to decimal = 17, gives a resistance of 67kOhms.
//By doing so, the TIA gain can be modified in at least one order of magnitude in either 
//direcction, smaller (6.7kOhms) or larger (667kOhms). Then proceeds to adjust the LED 
//Brightness around a nominal TIA Gain.
void SmartyPPG::balanceLEDCurrent()
{
  setTIAGain(17); //Set to some nominal value
  delay(1); //Add delay for settling time, random number
  uint16_t VTIA = getTIA(); //Measure TIA output voltage

  //The bounds are about 10% of 1/2 of full ADC Scale
  //Adjust the LED current so the TIA fits these bounds
  while (VTIA > TIA_upper_bound || VTIA < TIA_lower_bound)
  {
    //if LED is too bright (voltage output of TIA is too large, then decrease LED brightness)
    if (VTIA > TIA_upper_bound && R_LEDCurrent > 0) setLEDCurrent(R_LEDCurrent - 1);
    //if LED is too dim (voltage output of TIA is too small, then increase LED brightness)
    else if(VTIA < TIA_lower_bound && R_LEDCurrent < 63) setLEDCurrent(R_LEDCurrent + 1);
    //if at min or max of LED Current, then adjust TIA Gain
    else balanceTIAGain();
    delay(1); //Add delay for settling time, random number
    VTIA = getTIA();
  }
}

//Sets gain of digital potentiometer connected to transimpedance amplifier.
//gain      value between 0 - 255 to set resistance of digital potentiometer
//
// As gain increases, resistance increases, gain of TIA increases, output voltage increases.
// As gain decreases, resistance decreases, gain of TIA decreases, output voltage decreases.
void SmartyPPG::setTIAGain(uint8_t gain)            //Control Gain of Transimpedance Amplifier (TIA)
{
    ad5242.write(0, gain);
    R_TIAGain = gain;

}

//Returns gain setting of digital potentiometer connected to transimpedance amplifier
uint8_t SmartyPPG::getTIAGain() const
{
    return R_TIAGain;
}

//Balances TIA Gain with the LED Current
//Since the PPG circuit has a "virtuial ground at 1/2 full ADC, setting the output of
//the TIA gives the PPG Circuit the lowest settling time and highest responsitivity
void SmartyPPG::balanceTIAGain()
{
  uint16_t VTIA = getTIA();//Measure TIA output voltage

  while (VTIA > TIA_upper_bound || VTIA < TIA_lower_bound)
  {
    //if voltage of TIA is too large, then decrease TIA Gain
    if (VTIA > TIA_upper_bound && R_TIAGain > 0) setTIAGain(R_TIAGain - 1);
    //if voltage of TIA is too small, then increase TIA Gain
    else if(VTIA < TIA_lower_bound && R_TIAGain < 255) setTIAGain(R_TIAGain + 1);
    //if at min or max of TIA Gain, then adjust LED Current
    else balanceLEDCurrent();
    delay(1); //Add delay for settling time, random number
    VTIA = getTIA();
  }
}

//Sets gain of digital potentiometer connected to bandpass filter in PPG Circuit
//gain      value between 0 - 255 to set resistance of digital potentiometer
//
// As gain increases, resistance increases, gain of bandpass filter increases, output voltage increases.
// As gain decreases, resistance decreases, gain of bandpass filter decreases, output voltage decreases.
void SmartyPPG::setPPGGain(uint8_t gain)            
{
    ad5242.write(1, gain);
    R_PPGGain = gain; 
}

//Returns gain setting of digital potentiometer connected to bandpass filter
uint8_t SmartyPPG::getPPGGain() const
{
    return R_PPGGain;
}

//Reads voltage of transimpedance amplifier
uint16_t SmartyPPG::getTIA() const       //TIA Voltage
{
    return analogRead(TIAPin);
}

//Reads voltage of bandpass filter of the PPG Circuit
uint16_t SmartyPPG::getPPG() const       //BPF and PPG Voltage
{
    return analogRead(PPGPin);
}
