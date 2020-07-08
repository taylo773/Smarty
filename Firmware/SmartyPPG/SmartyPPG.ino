#include "SmartyPPG.h"

SmartyPPG ppg;

void setup()
{
  Serial.begin(9600);
  ppg.begin();
}

void loop()
{
}
