#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

byte id_1 = 0x53;
byte id_2 = 0x1D;
byte id_select = id_1;

bool state = false;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if(!accel.begin(id_select)) {
    Serial.println("ERROR");
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.print(event.acceleration.x); Serial.print(",");
  Serial.print(event.acceleration.y); Serial.print(",");
  Serial.print(event.acceleration.z); Serial.println("");
  delay(50);
}
