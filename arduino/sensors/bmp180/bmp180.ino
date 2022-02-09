#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

byte id_1 = 0x77;

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10180);

void setup() {
  Serial.begin(115200);
  Serial.println("Pressure Sensor Test"); Serial.println("");
  Wire.begin(21, 22);
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    Serial.print("Ooops, no BMP180 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

void loop() 
{
  sensors_event_t event;
  bmp.getEvent(&event);
 
  if (event.pressure) {
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure)); 
    Serial.println(" m");
    Serial.println("");
  } else {
    Serial.println("Sensor error");
  }
}
