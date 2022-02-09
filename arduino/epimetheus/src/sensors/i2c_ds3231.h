/*
  DS3231 Precision RTC Breakout
  Informations : https://www.adafruit.com/product/3013
  Library  : RTCLib
*/

#include "RTClib.h"

RTC_DS3231 rtc;
DateTime now;

void setup_ds3231() {
    rtc.begin();
}

void update_ds3231() {
    if(sensors_ds3231_enable) {
        now = rtc.now();
    }
}
