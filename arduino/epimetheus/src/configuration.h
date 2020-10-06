#include <Arduino.h>
// #define LANG_EN  // English Version
#define LANG_FR     // Version française

#define WIFI_ENABLE // Enable WiFi
#define WEB_ENABLE  // Enable WebInterface / WebSocket

const bool SCANNER = true;

const bool SDA_PIN = 21;
const bool SCL_PIN = 22;

const String TEMP_UNIT = "°C";
const String TEMP_COLOR = "#e88f79";
const String TEMP_TYPE = "temp";

const String HUMIDITY_UNIT = "%";
const String HUMIDITY_COLOR = "#79a5d1";
const String HUMIDITY_TYPE = "humidity";

const String PRESSURE_UNIT = "hPA";
const String PRESSURE_COLOR = "#eb53ed";
const String PRESSURE_TYPE = "pressure";

const String GAS_UNIT = "KΩ";
const String GAS_COLOR = "#7f807a";
const String GAS_TYPE = "gas";

const String LUX_UNIT = "lux";
const String LUX_COLOR = "#effa7a";
const String LUX_TYPE = "lux";

const String BPM_UNIT = "bpm";
const String BPM_COLOR = "#841607";
const String BPM_TYPE = "bpm";