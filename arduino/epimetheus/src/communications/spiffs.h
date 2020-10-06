
// TODO 
void scan_local_storage() {
    File file = SPIFFS.open("/data.csv", FILE_APPEND);
    file.println();

    file.print(LANG_DATE + DATA_SEPARATOR);
    // TSL2561
    for(int i = 0; i<3; i++) {
        if(sensors_tsl2561_enable[i]) {
            file.print(LANG_LIGHT + DATA_SEPARATOR);
        }
    }

    // BME680
     for(int i = 0; i<2; i++) {
        if(sensors_bme680_enable[i]) {
            file.print(LANG_TEMPERATURE + DATA_SEPARATOR);
            file.print(LANG_HUMIDITY + DATA_SEPARATOR);
            file.print(LANG_PRESSURE + DATA_SEPARATOR);
            file.print(LANG_GAS + DATA_SEPARATOR);
        }
    }

    // BME280
    for(int i = 0; i<2; i++) {
        if(sensors_bme280_enable[i]) {
            file.print(LANG_TEMPERATURE + DATA_SEPARATOR);
            file.print(LANG_HUMIDITY + DATA_SEPARATOR);
            file.print(LANG_PRESSURE + DATA_SEPARATOR);
        }
    }

    // BH1750
    for(int i = 0; i<2; i++) {
        if(sensors_bh1750_enable[i]) {
            file.print(LANG_LIGHT + DATA_SEPARATOR);
        }
    }

    // MAX30102
    if(sensors_max30102_enable) {
        file.print(LANG_BPM + DATA_SEPARATOR);
    }

    // MPU6050
    for(int i = 0; i<2; i++) {
        if(sensors_mpu6050_enable[i]) {
            file.print(LANG_TEMPERATURE + DATA_SEPARATOR);
            file.print(LANG_ACC + " X" + DATA_SEPARATOR);
            file.print(LANG_ACC + " Y" + DATA_SEPARATOR);
            file.print(LANG_ACC + " Z" + DATA_SEPARATOR);
            file.print(LANG_GYRO + " X" + DATA_SEPARATOR);
            file.print(LANG_GYRO + " Y" + DATA_SEPARATOR);
            file.print(LANG_GYRO + " Z" + DATA_SEPARATOR);
        }
    }

    file.println();
    file.close();
}

// TODO
void update_local_storage() {
    File file = SPIFFS.open("/data.csv", FILE_APPEND);

    // DS3231
    file.print(now.year(), DEC); 
    file.print('/');
    if(now.month() < 10) {
        file.print("0");
    }
    file.print(now.month(), DEC);
    file.print('/');
    if(now.day() < 10) {
        file.print("0");
    }
    file.print(now.day(), DEC);
    file.print(" ");
    if(now.hour() < 10) {
        file.print("0");
    }
    file.print(now.hour(), DEC);
    file.print(':');
    if(now.minute() < 10) {
        file.print("0");
    }
    file.print(now.minute(), DEC);
    file.print(':');
    if(now.second() < 10){
        file.print("0");
    }
    file.print(now.second(), DEC);
    file.print(DATA_SEPARATOR);

    // TSL2561
    for(int i = 0; i<3; i++) {
        if(sensors_tsl2561_enable[i]) {
            file.print(sensors_tsl2561_lux[i] + DATA_SEPARATOR);
        }
    }

    // BME680
    for(int i = 0; i<2; i++) {
        if(sensors_bme680_enable[i]) {
            file.print(sensors_bme680_temp[i] + DATA_SEPARATOR);
            file.print(sensors_bme680_hum[i] + DATA_SEPARATOR);
            file.print(sensors_bme680_pressure[i] + DATA_SEPARATOR);
            file.print(sensors_bme680_gas[i] + DATA_SEPARATOR);
        }
    }

    // BME280
    for(int i = 0; i<2; i++) {
        if(sensors_bme280_enable[i]) {
            file.print(sensors_bme280_temp[i] + DATA_SEPARATOR);
            file.print(sensors_bme280_hum[i] + DATA_SEPARATOR);
            file.print(sensors_bme280_pressure[i] + DATA_SEPARATOR);
        }
    }

    // BH1750
    for(int i = 0; i<3; i++) {
        if(sensors_bh1750_enable[i]) {
            file.print(sensors_bh1750_lux[i] + DATA_SEPARATOR);
        }
    }

    // MAX30102
    if(sensors_max30102_enable) {
        file.print(sensors_max30102_bpm + DATA_SEPARATOR);
    }

    // MPU6050
    for(int i = 0; i<2; i++) {
        if(sensors_mpu6050_enable[i]) {
            file.print(sensors_mpu6050_temp[i] + DATA_SEPARATOR);
            file.print(sensors_mpu6050_acc_x[i] + DATA_SEPARATOR);
            file.print(sensors_mpu6050_acc_y[i] + DATA_SEPARATOR);
            file.print(sensors_mpu6050_acc_z[i] + DATA_SEPARATOR);
            file.print(sensors_mpu6050_gyro_x[i] + DATA_SEPARATOR);
            file.print(sensors_mpu6050_gyro_y[i] + DATA_SEPARATOR);
            file.print(sensors_mpu6050_gyro_z[i] + DATA_SEPARATOR);
        }
    }

    file.println();
}