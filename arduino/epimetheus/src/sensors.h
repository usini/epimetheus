// Sensors calculator computed on Core 0 - https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/

#include <Wire.h>              // I²C Manager
#include <Adafruit_Sensor.h>   // Adafruit Sensor Manager
#include "sensors/constants.h" // Constants (and variables) for sensors
#include "sensors/i2c_ds3231.h"    // DS3231 processing
#include "sensors/i2c_bme680.h"    // BME680 processing
#include "sensors/i2c_tsl2561.h"   // TSL2561 processing
#include "sensors/i2c_bme280.h"

int nb_sensors = 0;
bool sensor_changed = false;
bool clock_active = false;

// For each sensor check I²C address and make it enable
void refresh_sensors(bool enable, byte address) {

  switch (address) {
    case TSL2561_0_ADDR:
      if(enable) {
        if(!sensors_tsl2561_enable[0]) {
          sensors_tsl2561_enable[0] = true;
          setup_tsl2561(0);
          nb_sensors++;
        } 
      } else {
        if(sensors_tsl2561_enable[0]) {
          sensors_tsl2561_enable[0] = false;
        }
      }
    break;

    case TSL2561_1_ADDR:
       if(enable) {
        if(!sensors_tsl2561_enable[1]) {
          sensors_tsl2561_enable[1] = true;
          setup_tsl2561(1);
          nb_sensors++;
        } 
      } else {
        if(sensors_tsl2561_enable[1]) {
          sensors_tsl2561_enable[1] = false;
        }
      }
    break;

    case TSL2561_2_ADDR:
       if(enable) {
        if(!sensors_tsl2561_enable[2]) {
          sensors_tsl2561_enable[2] = true;
          setup_tsl2561(0);
          nb_sensors++;
        }  
      } else {
        if(sensors_tsl2561_enable[2]) {
          sensors_tsl2561_enable[2] = false;
        }
      }
    break;

    case DS3231_ADDR:
      if(enable) {
        if(!sensors_ds3231_enable) {
          sensors_ds3231_enable = true;
          clock_active = true;
        }
      } else {
        if(sensors_ds3231_enable) {
          sensors_ds3231_enable = false;
        }
      }
    break;

    case BME680_0_ADDR:
      if(enable) {
        if((!sensors_bme680_enable[0]) && (!sensors_bme280_enable[0])) {   
          if(setup_bme680(0)) {
            sensors_bme680_enable[0] = true;
            nb_sensors++;
          } else {
            sensors_bme280_enable[0] = true;
            setup_bme280(0);
            nb_sensors++;
          }
        }
      } else {
        if(sensors_bme680_enable[0]) {
          Serial.println("DEACTIVATED BME680");
          sensors_bme680_enable[0] = false;
        }
        if(sensors_bme280_enable[0]) {
          Serial.println("DEACTIVATED BME280");
          sensors_bme280_enable[0] = false;
        }
      }
    break;

    case BME680_1_ADDR:
       if(enable) {
        if((!sensors_bme680_enable[1]) && (!sensors_bme280_enable[1])) {   
          if(setup_bme680(1)) {
            sensors_bme680_enable[1] = true;
            nb_sensors++;
          } else {
            sensors_bme280_enable[1] = true;
            setup_bme280(1);
            nb_sensors++;
          }
        }
      } else {
        if(sensors_bme680_enable[1]) {
          sensors_bme680_enable[1] = false;
        } else {
          sensors_bme280_enable[1] = false;
        }
      }
    break;
    
    default:
      if(enable) {
        Serial.print("[0x");
        Serial.print(address, HEX);
        Serial.println("] Unknown I²C device");
      }
    break;
  }
}

// Scan I²C and if a device is found refresh sensors list
void scan_sensors() {
  byte error, address;
  int last_nb_sensors = nb_sensors;
  nb_sensors = 0;
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if ((error == 0) || (error == 4)) {
      refresh_sensors(true, address);
    } else {
      refresh_sensors(false, address);
    }
  }
  if(nb_sensors != last_nb_sensors) {
    Serial.println(LANG_SENSOR_CHANGED);
    sensor_changed = true;
  }
}

// Get value from sensors
void update_sensors() {
      update_tsl2561();
      update_bme680();
      update_bme280();
      update_clock();
}

// Basic I²C setup / sensors update on CORE 0
// TODO manage multiples I²C port / Change I²C pins
void setup_sensors() {
  Wire.begin(); // As for now I²C based sensors are the only one managed.
}