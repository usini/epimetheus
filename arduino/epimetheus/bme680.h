#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme; // I2C (22 SDA / 21 SCL)

void setup_bme680() {
  if (!bme.begin()) {
    debug_println("Capteur Météo hors ligne");
    while (1);
  }

  bme.setTemperatureOversampling(BME680_OS_16X);
  bme.setHumidityOversampling(BME680_OS_16X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void update_bme680() {
  unsigned long endTime = bme.beginReading();

  //Serial.print(F("Reading started at "));
  //Serial.print(millis());
  //Serial.print(F(" and will finish at "));
  //Serial.println(endTime);


  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }

  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  temp = bme.temperature;
  humidity = bme.humidity;
  pressure = bme.pressure / 100.0;
  gas = bme.gas_resistance / 1000.0;
  
}
