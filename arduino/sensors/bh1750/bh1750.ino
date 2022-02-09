#include <Wire.h>
#include <hp_BH1750.h>  //  include the library
hp_BH1750 BH1750;       //  create the sensor

void setup()
{
  Wire.begin(21, 22);
  Serial.begin(115200);
  bool avail = BH1750.begin(BH1750_TO_GROUND);// init the sensor with address pin connected to ground
                                              // result (bool) wil be be "false" if no sensor found
}

void loop()
{
  BH1750.start();   //starts a measurement
  float lux=BH1750.getLux();  //  waits until a conversion finished
  Serial.println(lux);        
}
