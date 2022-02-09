/*
  BH1750 Light Sensor
  Informations : https://www.adafruit.com/product/4681
  Library  : SparkFun_MAX3010x_Sensor_Library
*/

#include <hp_BH1750.h>

hp_BH1750 sensors_bh1750[2];

void setup_bh1750(int id) {
    byte address = 0x00;
    if(id == 0) {
        address = BH1750_0_ADDR;
    } else {
        address = BH1750_1_ADDR;
    }

    sensors_bh1750[id].begin(address);
}

void update_bh1750() {
    for(int id = 0; id < 2; id++) {
        if(sensors_bh1750_enable[id]) {
            sensors_bh1750[id].start();
            sensors_bh1750_lux[id] = sensors_bh1750[id].getLux();
        }
    }
}