/*
  TLS2561 - Digital Luminosity/Lux/Light Sensor
  Informations : https://www.adafruit.com/product/439
  Library  : Adafruit TSL2561
*/

// Digital I²c Light Sensor (TSL2561)
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_TSL2561_Unified sensors_tsl2561[3] = {
  Adafruit_TSL2561_Unified(0x29, 12345),
  Adafruit_TSL2561_Unified(0x39, 12345),
  Adafruit_TSL2561_Unified(0x49, 12345),
};

void setup_tsl2561(int sensor_id) {
  sensors_tsl2561_enable[sensor_id] = true;
  sensors_tsl2561[sensor_id].enableAutoRange(true);
  sensors_tsl2561[sensor_id].setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS); // Slow but better resolution
  sensors_tsl2561[sensor_id].begin();
}

void update_tsl2561() {
  for(int sensor = 0; sensor < 3; sensor++) {
    if(sensors_tsl2561_enable[sensor]) {
      sensors_event_t event; // Prepare event variable  
      sensors_tsl2561[sensor].getEvent(&event); // Read sensor and sent value to event variable
      if (event.light) {
        sensors_tsl2561_lux[sensor] = event.light; // Get light value from event
      }
    }
  }
}

