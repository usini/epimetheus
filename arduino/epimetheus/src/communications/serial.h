void setup_serial(int baudrate) {
    Serial.begin(baudrate);
    Serial.println("");
    Serial.println("~~~~~~~~~~~~ EPIMETHEUS~~~~~~~~~");
}

void update_serial() {
    
    Serial.println("___________________________");

    if(save_flash) {
        Serial.println("[SPIFFS] " + LANG_SAVING);
    }

    // DS3231
    if(sensors_ds3231_enable) {
       
        Serial.print("[" + LANG_DS3231 +  "] " + LANG_DATE + ":");
        Serial.print(now.year(), DEC); 
        Serial.print('/');
        if(now.month() < 10) {
            Serial.print("0");
        }
        Serial.print(now.month(), DEC);
        Serial.print('/');
        if(now.day() < 10) {
            Serial.print("0");
        }
        Serial.print(now.day(), DEC);
        Serial.print(" ");
        if(now.hour() < 10) {
            Serial.print("0");
        }
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        if(now.minute() < 10) {
            Serial.print("0");
        }
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        if(now.second() < 10){
            Serial.print("0");
        }
        Serial.print(now.second(), DEC);
        Serial.println();
    }

    // TSL2561
    for(int i = 0; i<3; i++) {
        if(sensors_tsl2561_enable[i]){
            Serial.printf("[TSL2561_%d] ", i);
            Serial.print(LANG_LIGHT + " : ");
            Serial.print(sensors_tsl2561_lux[i]);
            Serial.println(" " + LUX_UNIT);
        }
    }

    // BMP280
    for(int i = 0; i<2; i++) {
        if(sensors_bmp280_enable[i]) {
            Serial.printf("[BMP280_%d] ", i);
            Serial.print(LANG_TEMPERATURE + ": ");
            Serial.print(sensors_bmp280_temp[i]);
            Serial.println( + " " + TEMP_UNIT);

            Serial.printf("[BMP280_%d] ",i);
            Serial.print(LANG_PRESSURE + ": ");
            Serial.print(sensors_bmp280_pressure[i]);
            Serial.println(" " + PRESSURE_UNIT);
        }
    }

    // BME280
    for(int i = 0; i<2; i++) {
        if(sensors_bme280_enable[i]) {
            Serial.printf("[BME280_%d] ", i);
            Serial.print(LANG_TEMPERATURE + ": ");
            Serial.print(sensors_bme280_temp[i]);
            Serial.println( + " " + TEMP_UNIT);

            Serial.printf("[BME280_%d] ", i);
            Serial.print(LANG_HUMIDITY + ": ");
            Serial.print(sensors_bme280_hum[i]);
            Serial.println(" " + HUMIDITY_UNIT);

            Serial.printf("[BME280_%d] ",i);
            Serial.print(LANG_PRESSURE + ": ");
            Serial.print(sensors_bme280_pressure[i]);
            Serial.println(" " + PRESSURE_UNIT);
        }
    }

    // BME680
    for(int i = 0; i<2; i++) {
        if(sensors_bme680_enable[i]) {
            Serial.printf("[BME680_%d] ", i);
            Serial.print(LANG_TEMPERATURE + ": ");
            Serial.print(sensors_bme680_temp[i]);
            Serial.println( + " " + TEMP_UNIT);

            Serial.printf("[BME680_%d] ", i);
            Serial.print(LANG_HUMIDITY + ": ");
            Serial.print(sensors_bme680_hum[i]);
            Serial.println(" " + HUMIDITY_UNIT);

            Serial.printf("[BME680_%d] ",i);
            Serial.print(LANG_PRESSURE + ": ");
            Serial.print(sensors_bme680_pressure[i]);
            Serial.println(" " + PRESSURE_UNIT);

            Serial.printf("[BME680_%d] ",i);
            Serial.print(LANG_GAS + ": ");
            Serial.print(sensors_bme680_gas[i]);
            Serial.println(" " + GAS_UNIT);
        }
    }

    // BH1750
    for(int i = 0; i<2; i++) {
        if(sensors_bh1750_enable[i]) {
            Serial.printf("[BH1750_%d] ", i);
            Serial.print(LANG_LIGHT + " : ");
            Serial.print(sensors_bh1750_lux[i]);
            Serial.println(" " + LUX_UNIT);
        }
    }

    // MAX30102
    if(sensors_max30102_enable) {
            Serial.printf("[MAX30102] ");
            Serial.print(LANG_BPM + " : ");
            Serial.print(sensors_max30102_bpm);
            Serial.println(" " + BPM_UNIT);
    }

    // MPU6050
    for(int i = 0; i<2; i++) {
        if(sensors_mpu6050_enable[i]) {
            Serial.printf("[MPU6050_%d] ", i);
            Serial.print(LANG_TEMPERATURE + ": ");
            Serial.print(sensors_mpu6050_temp[i]);
            Serial.println(" " + TEMP_UNIT);

            Serial.printf("[MPU6050_%d] ", i);
            Serial.print(LANG_ACC + " X : ");
            Serial.print(sensors_mpu6050_acc_x[i]);
            Serial.println(" " + ACC_UNIT);

            Serial.printf("[MPU6050_%d] ", i);
            Serial.print(LANG_ACC + " Y : ");
            Serial.print(sensors_mpu6050_acc_y[i]);
            Serial.println(" " + ACC_UNIT);

            Serial.printf("[MPU6050_%d] ",i);
            Serial.print(LANG_ACC + " Z : ");
            Serial.print(sensors_mpu6050_acc_z[i]);
            Serial.println(" " + ACC_UNIT);

            Serial.printf("[MPU6050_%d] ", i);
            Serial.print(LANG_GYRO + " X : ");
            Serial.print(sensors_mpu6050_gyro_x[i]);
            Serial.println(" " + GYRO_UNIT);

            Serial.printf("[MPU6050_%d] ", i);
            Serial.print(LANG_GYRO + " Y : ");
            Serial.print(sensors_mpu6050_gyro_y[i]);
            Serial.println(" " + GYRO_UNIT);

            Serial.printf("[MPU6050_%d] ",i);
            Serial.print(LANG_GYRO + " Z: ");
            Serial.print(sensors_mpu6050_gyro_z[i]);
            Serial.println(" " + GYRO_UNIT);
        }
    }

    Serial.println("___________________________");
}

void scan_serial() {
    Serial.println("[SENSORS]");
    // TSL2561
    for(int i = 0; i<3; i++) {
        if(sensors_tsl2561_enable[i]) {
            Serial.print("[0x");
            switch(i) {
                case 0:
                    Serial.print(TSL2561_0_ADDR, HEX);
                break;
                case 1:
                    Serial.print(TSL2561_1_ADDR, HEX);
                break;
                case 2:
                    Serial.print(TSL2561_2_ADDR, HEX);
                break;
            }
            Serial.println("] " + LANG_TSL2561_FULLNAME + " - " + TSL2561_LINK);
        }
    }

  
    // BMP280
    for(int i = 0; i<2; i++) {
        if(sensors_bmp280_enable[i]) {
            Serial.print("[0x");
            switch(i) {
                case 0:
                    Serial.print(BMP280_0_ADDR, HEX);
                break;
                case 1:
                    Serial.print(BMP280_1_ADDR, HEX);
                break;
            }
            Serial.println("] " + LANG_BMP280_FULLNAME + " - " + BMP280_LINK);
        }
    }  

    // BME280
    for(int i = 0; i<2; i++) {
        if(sensors_bme280_enable[i]) {
            Serial.print("[0x");
            switch(i) {
                case 0:
                    Serial.print(BME280_0_ADDR, HEX);
                break;
                case 1:
                    Serial.print(BME280_1_ADDR, HEX);
                break;
            }
            Serial.println("] " + LANG_BME280_FULLNAME + " - " + BME280_LINK);
        }
    }

    // BME680
    for(int i = 0; i<2; i++) {
        if(sensors_bme680_enable[i]) {
            Serial.print("[0x");
            switch(i) {
                case 0:
                    Serial.print(BME680_0_ADDR, HEX);
                break;
                case 1:
                    Serial.print(BME680_1_ADDR, HEX);
                break;
            }
            Serial.println("] " + LANG_BME680_FULLNAME + " - " + BME680_LINK);
        }
    }

    // BH1750
    for(int i = 0; i<2; i++) {
        if(sensors_bh1750_enable[i]) {
            Serial.print("[0x");
            switch(i) {
                case 0:
                    Serial.print(BH1750_0_ADDR, HEX);
                break;
                case 1:
                    Serial.print(BH1750_1_ADDR, HEX);
                break;
            }
            Serial.println("] " + LANG_BH1750_FULLNAME + " - " + BH1750_LINK);
        }
    }

    // MAX30102
    if(sensors_max30102_enable) {
        Serial.print("[0x");
        Serial.print(MAX30102_0_ADDR, HEX);
        Serial.println("] " + LANG_MAX30102_FULLNAME + " - " + MAX30102_LINK);
    }
    
    // DS3231
    if(sensors_ds3231_enable) {
        Serial.print("[0x");
        Serial.print(DS3231_ADDR, HEX);
        Serial.println("] " + LANG_DS3231_FULLNAME + " - " + DS3231_LINK);
    }

    // MPU6050
    for(int i = 0; i<2; i++) {
        if(sensors_mpu6050_enable[i]) {
            Serial.print("[0x");
            switch(i) {
                case 0:
                    Serial.print(MPU6050_0_ADDR, HEX);
                break;
                case 1:
                    Serial.print(MPU6050_1_ADDR, HEX);
                break;
            }
            Serial.println("] " + LANG_MPU6050_FULLNAME + " - " + MPU6050_LINK);
        }
    }

}

