
#include <Adafruit_BME280.h>

Adafruit_BME280 sensors_bme280[2];

void setup_bme280(int id) {
    byte address = 0x00;
    if(id == 0){
        address = BME280_0_ADDR;
    } else {
        address = BME280_1_ADDR;
    }

    sensors_bme280[id].begin(address);
}

void update_bme280() {
    for(int id = 0; id < 2; id++) {
        if(sensors_bme280_enable[id]){
            sensors_bme280_temp[id] = sensors_bme280[id].readTemperature();
            sensors_bme280_pressure[id] = sensors_bme280[id].readPressure() / 10;
            sensors_bme280_hum[id] = sensors_bme280[id].readHumidity();
        }
    }
}
