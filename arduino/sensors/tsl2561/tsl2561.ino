#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

byte id_1 = 0x39;
byte id_2 = 0x29;
byte id_3 = 0x49;

byte id_select = id_1;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(id_select, 12345);

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Light Sensor Test"); Serial.println("");
  Wire.begin(21, 22);
  if(!tsl.begin())
  {
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); 
  Serial.println("");
}

void loop(void) 
{  
  /* Get a new sensor event */ 
  sensors_event_t event;
  tsl.getEvent(&event);
 
  /* Display the results (light is measured in lux) */
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" lux");
  }
  else
  {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  delay(250);
}
