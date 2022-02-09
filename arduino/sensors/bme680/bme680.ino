#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

byte id_1 = 0x77;
byte id_2 = 0x76;

byte id_select = id_1;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme; // I2C

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if(!bme.begin(id_select)) {
    Serial.println("ERROR");
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {
   if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
   }
   Serial.print(bme.temperature);
   Serial.print(",");
   Serial.print(bme.pressure / 100.0);
   Serial.print(",");
   Serial.print(bme.humidity);
   Serial.println();
}
