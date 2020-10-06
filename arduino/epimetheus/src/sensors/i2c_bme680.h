/*
  BME680 - Temperature, Humidity, Pressure and Gas Sensor
  Informations : https://www.adafruit.com/product/3660
  Library  : Adafruit BME680 
*/

#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 sensors_bme680[2];

bool setup_bme680(int id) {
  byte address = 0x00;
  if(id == 0) {
    address = BME680_0_ADDR;
  } else {
    address = BME680_1_ADDR;
  }

  bool check = false;
  check = sensors_bme680[id].begin(address);
 
  if(check) {
    sensors_bme680[id].setTemperatureOversampling(BME680_OS_16X);
    sensors_bme680[id].setHumidityOversampling(BME680_OS_16X);
    sensors_bme680[id].setPressureOversampling(BME680_OS_4X);
    sensors_bme680[id].setIIRFilterSize(BME680_FILTER_SIZE_3);
    sensors_bme680[id].setGasHeater(320, 150); // 320*C for 150 ms
  }
  return check;
}

void update_bme680() {
  for(int id = 0; id < 2; id++) {
    if(sensors_bme680_enable[id]) {
      sensors_bme680[id].performReading(); // Begin BME680 reading
      sensors_bme680_temp[id] = sensors_bme680[id].temperature;
      sensors_bme680_hum[id] = sensors_bme680[id].humidity;
      sensors_bme680_pressure[id] = sensors_bme680[id].pressure / 100.0;
      sensors_bme680_gas[id] = sensors_bme680[id].readGas() / 1000;
      }
    }
}
