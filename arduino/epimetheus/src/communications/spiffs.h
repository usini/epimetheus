
// TODO 
void scan_local_storage() {
    File file = SPIFFS.open("/data.csv", FILE_APPEND);
    file.println();

    file.print(LANG_DATE + DATA_SEPARATOR);
    // TSL2561
    for(int i = 0; i<3; i++) {
        if(sensors_tsl2561_enable[i]){
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
    file.println();
    file.close();
}

// TODO
void update_local_storage() {
    File file = SPIFFS.open("/data.csv", FILE_APPEND);

    //DS3231
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

    //TSL2561
    for(int i = 0; i<3; i++) {
        if(sensors_tsl2561_enable[i]) {
            file.print(sensors_tsl2561_lux[i] + DATA_SEPARATOR);
        }
    }

    //BME680
     for(int i = 0; i<2; i++) {
        if(sensors_bme680_enable[i]) {
            file.print(sensors_bme680_temp[i] + DATA_SEPARATOR);
            file.print(sensors_bme680_hum[i] + DATA_SEPARATOR);
            file.print(sensors_bme680_pressure[i] + DATA_SEPARATOR);
            file.print(sensors_bme680_gas[i] + DATA_SEPARATOR);
        }
    }
    file.println();
}