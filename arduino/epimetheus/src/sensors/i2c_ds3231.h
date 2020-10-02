/*
  DS3231 Precision RTC Breakout
  Informations : https://www.adafruit.com/product/3013
  Library  : RTCLib
*/

#include "RTClib.h"

RTC_DS3231 rtc;
DateTime now;

void setup_clock() {
    if(sensors_ds3231_enable) {
        if(! rtc.begin()) {
            Serial.println(LANG_DS3231_ERROR);
        } else {
            Serial.println(LANG_DS3231_OK);
        }
    }
}

void update_clock() {
    if(sensors_ds3231_enable) {
        now = rtc.now();
    }
}
