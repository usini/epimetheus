/*
  BMP280 - Temperature, Pressure Sensor
  Informations : https://www.adafruit.com/product/2651
  Library  : Adafruit BMP280
*/

#include <Adafruit_BMP280.h>

Adafruit_BMP280 sensors_bmp280[2];

bool setup_bmp280(int id) {
    byte address = 0x00;
    if(id == 0) {
        address = BMP280_0_ADDR;
    } else {
        address = BMP280_1_ADDR;
    }

    bool check = false;
    check = sensors_bmp280[id].begin(address);
    return check;
}

void update_bmp280() {
    for(int id = 0; id < 2; id++) {
        if(sensors_bmp280_enable[id]) {
            sensors_bmp280_temp[id] = sensors_bmp280[id].readTemperature();
            sensors_bmp280_pressure[id] = sensors_bmp280[id].readPressure() / 10;
        }
    }
}
