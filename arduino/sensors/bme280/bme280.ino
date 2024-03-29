#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

byte id_1 = 0x76;
byte id_2 = 0x77;

byte id_select = id_1;
bool status = false;
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  status = bme.begin(id_select);  
  if (!status) {
    Serial.println("ERROR");
    delay(100);
    while(1);
  }
}

void loop() {
  Serial.print(bme.readTemperature());
  Serial.print(",");
  Serial.print(bme.readHumidity());
  Serial.print(",");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println();
}
