#include <Arduino.h>
// #define LANG_EN  // English Version
#define LANG_FR     // Version française

#define WIFI_ENABLE // Enable WiFi
#define WEB_ENABLE  // Enable WebInterface / WebSocket
#define NEOMATRIX_ENABLE // Enable Neopixel matrix on M5 Atom Matrix

const bool SCANNER = true;

const int SDA_PIN = 21;
const int SCL_PIN = 22;

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

const String ACC_UNIT = "m/s^2";
const String ACC_TYPE = "acc";
const String ACC_X_COLOR = "#669966";
const String ACC_Y_COLOR = "#cccc33";
const String ACC_Z_COLOR = "#6600cc";

const String GYRO_UNIT = "rad/s";
const String GYRO_TYPE = "gyro";
const String GYRO_X_COLOR = "#172012";
const String GYRO_Y_COLOR = "#3d3d0f";
const String GYRO_Z_COLOR = "#140028";
