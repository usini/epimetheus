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

    if(sensors_ds3231_enable){
        // DS3231
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
            Serial.println("] " + TSL2561_FULLNAME + " - " + TSL2561_LINK);
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
            Serial.println("] " + BME680_FULLNAME + " - " + BME680_LINK);
        }
    }

    if(sensors_ds3231_enable) {
        Serial.print("[0x");
        Serial.print(DS3231_ADDR, HEX);
        Serial.println("] " + DS3231_FULLNAME + " - " + DS3231_LINK);
    }
}

