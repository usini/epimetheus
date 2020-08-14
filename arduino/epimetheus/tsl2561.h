#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup_tsl_2561(){
  tsl.setGain(TSL2561_GAIN_1X); 
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);
  if(!tsl.begin()) {
    debug_println("Capteur luminosité déconnecté");
    while(1);
  }
}

void update_tsl_2561(){
  sensors_event_t event;
  tsl.getEvent(&event);
  if (event.light)
  {
    lux = event.light;
  } else {
    debug_println("Capteur luminosité en surcharge");
  }
}
