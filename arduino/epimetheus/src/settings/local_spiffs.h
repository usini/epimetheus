#include "SPIFFS.h"
#include <ArduinoJson.h>

const String DATA_SEPARATOR = ";";
const String DATA_POINT = ",";

String esp_name; // Name (will be generate / can be change)
String wifi1_name;
String wifi1_pass;
String wifi2_name;
String wifi2_pass;
bool save_flash = false;

int spiffs_space = 0;

// Get SPIFFS memory available and save it as a percent
void get_spiffs_space() {
    long spiffs_used = (long)SPIFFS.usedBytes();
    long spiffs_total = (long)SPIFFS.totalBytes();
    long spiffs_left = spiffs_total - spiffs_used;
    spiffs_space = spiffs_left * 100 / spiffs_total;
}

// Get name from name.txt (if not available generate it from chipid)
void get_name_local_storage() {
     if (SPIFFS.exists("/name.txt")) {
        Serial.print(LANG_FLASH_NAME_DEFINED + ": ");
        File file = SPIFFS.open("/name.txt", FILE_READ);
        while(file.available()) {
            esp_name = file.readStringUntil('\n');
        }
        file.close();
    } else {
        Serial.print(LANG_FLASH_NAME_UNDEFINED + " : ");
        uint64_t chipid = ESP.getEfuseMac();
        uint16_t chip = (uint16_t)(chipid >> 32);
        esp_name = "epi_" + String(chip);
        File file = SPIFFS.open("/name.txt", FILE_WRITE);
        file.print(esp_name);
        file.close();
    }
    Serial.println(esp_name);
}

// Init settings to default
void init_settings_local_storage() {
    Serial.println(LANG_FLASH_SETTINGS_UNDEFINED);
    StaticJsonDocument<512> doc;
    doc["wifi1_name"] = "";
    doc["wifi1_pass"] = "";
    doc["wifi2_name"] = "";
    doc["wifi2_pass"] = "";
    File file = SPIFFS.open("/settings.json", FILE_WRITE);
    serializeJson(doc, file);
    file.close();
}

// Get settings from SPIFFS if corrupt or not available 
void get_settings_local_storage() {
    if(SPIFFS.exists("/settings.json")) {
        Serial.println(LANG_FLASH_SETTINGS_DEFINED);
        File file = SPIFFS.open("/settings.json", FILE_READ);
        StaticJsonDocument<1024> doc;
        String settings_text = file.readStringUntil('\n');
        DeserializationError error = deserializeJson(doc, settings_text);
        if(error) {
            Serial.println(LANG_FLASH_SETTINGS_JSON_ERROR);
            init_settings_local_storage();
        } else {
            //https://arduinojson.org/v6/example/config/
            wifi1_name = doc["wifi1_name"].as<String>();
            wifi1_pass = doc["wifi1_pass"].as<String>();
            wifi2_name = doc["wifi2_name"].as<String>();
            wifi2_pass = doc["wifi2_pass"].as<String>();
        }
    } else {
        init_settings_local_storage();
    }
}

// Setup SPIFFS to save settings
void setup_local_storage() {
    if(SPIFFS.begin(true)) {
        Serial.print(LANG_FLASH_STATE_OK);
        get_spiffs_space();
        Serial.print(" - ");
        Serial.print(spiffs_space);
        Serial.println(" %");
    } else {
        Serial.println(LANG_FLASH_STATE_ERR);
        return;
    }
    get_name_local_storage();
    get_settings_local_storage();
}

