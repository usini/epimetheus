
/*
  MAX30102 Heart-Rate Sensor - High-Sensitivity Pulse Oximeter
  Informations : https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library
  Library  : SparkFun_MAX3010x_Sensor_Library
*/

#include "MAX30105.h"
#include "heartRate.h"

MAX30105 sensors_max30102;

const byte MAX30102_RATE_SIZE = 5; //Increase this for more averaging. 4 is good.
byte max30102_rates[MAX30102_RATE_SIZE]; //Array of heart rates
byte max30102_rateSpot = 0;
long max30102_lastBeat = 0; //Time at which the last beat occurred
int max30102_reading = 0;
float max30102_beatsPerMinute;
int max30102_beatAvg;

void setup_max30102() {
    sensors_max30102.begin(Wire, I2C_SPEED_FAST);
    sensors_max30102.setup();
    sensors_max30102.setPulseAmplitudeRed(0x0A);
    sensors_max30102.setPulseAmplitudeGreen(0);
}

void update_max30102() {
    if(sensors_max30102_enable) {
        long irValue = sensors_max30102.getIR();
        if(checkForBeat(irValue) == true) {
            long delta = millis() - max30102_lastBeat;
            max30102_lastBeat = millis();

            max30102_beatsPerMinute = 60 / (delta / 1000.0);
            Serial.println(max30102_beatsPerMinute);
            //sensors_max30102_bpm = beatsPerMinute;
            if (max30102_beatsPerMinute < 200 && max30102_beatsPerMinute > 40)
            {
                max30102_rates[max30102_rateSpot++] = (byte)max30102_beatsPerMinute; //Store this reading in the array
                max30102_rateSpot %= MAX30102_RATE_SIZE; //Wrap variable
                max30102_reading++;
                if(max30102_reading == MAX30102_RATE_SIZE){
                    //Take average of readings
                    sensors_max30102_bpm = 0;
                    for (byte x = 0 ; x < MAX30102_RATE_SIZE ; x++)
                        sensors_max30102_bpm += max30102_rates[x];
                    sensors_max30102_bpm /= MAX30102_RATE_SIZE;
                    max30102_reading = 0;
                }
            }
        }
    }
}