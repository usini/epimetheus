#include <Arduino.h> // String failed if not include
// Sensors
const String LANG_DATE = "Date";
const String LANG_TEMPERATURE = "Temperature";
const String LANG_HUMIDITY = "Humidity";
const String LANG_PRESSURE = "Atmospheric Pressure";
const String LANG_GAS = "Gas";
const String LANG_LIGHT = "Luminosity";
const String LANG_BPM = "Beat per minute";
const String LANG_ACC = "Acceleration";
const String LANG_GYRO = "Gyroscope";

const String LANG_SENSOR_CHANGED = "[SENSOR] Sensors has changed...";

const String LANG_BMP280_FULLNAME = "BMP280 - Temperature, Pressure Sensor";
const String LANG_BME280_FULLNAME = "BME280 - Temperature, Humidity, Pressure Sensor";
const String LANG_BME680_FULLNAME = "BME680 - Temperature, Humidity, Pressure and Gas Sensor";
const String LANG_TSL2561_FULLNAME = "TSL2561 - Digital Luminosity/Lux/Light Sensor";
const String LANG_DS3231_FULLNAME = "DS3231 - Precision RTC Breakout";
const String LANG_BH1750_FULLNAME = "BH1750 - Light Sensor";
const String LANG_MAX30102_FULLNAME = "MAX30102 - Heartbeat Sensor";
const String LANG_MPU6050_FULLNAME = "MPU6050 - 6-DoF Acceleration and Gyroscope Sensor";

const String LANG_DS3231 = "DS3231";
const String LANG_DS3231_ERROR = "[CLOCK] Error, can't init internal clock";
const String LANG_DS3231_OK = "[CLOCK] Internal clock enable";
const String LANG_SAVING = "Save";

// Wifi

const String LANG_WIFI_CONNECTION = "[WIFI] Trying to connect";
const String LANG_WIFI_CONNECTION_ESTABLISHED = "[WIFI] Connection established : ";
const String LANG_WIFI_CONNECTION_FAILED = "[WIFI] Connection failed, Access point mode - ";

// Web
const String LANG_DISCONNECT = "Disconnected";
const String LANG_CONNECTED = "Connected";
const String LANG_RECEIVED_MESSAGE = "[WEBSOCKET] Message received : ";
const String LANG_WIFI_SCAN = "[WIFI] Wifi network scan";
const String LANG_WIFI_NO_NETWORK = "[WIFI] No WiFi network founded";
const String LANG_WIFI_NETWORK = "[WIFI] Wifi network founded";

// WebSocket
const String LANG_WEBSOCKET_ERROR = "[WEBSOCKET] Websocket error";
const String LANG_WEBSOCKET_INVALID_COMMAND = "[WEBSOCKET] Invalid command";
const String LANG_WEBSOCKET_INVALID_JSON = "[WEBSOCKET] Invalid JSON format";

// Flash Memory
const String LANG_FLASH_STATE_OK = "[FLASH] Internal Memory is functional";
const String LANG_FLASH_STATE_ERR = "[FLASH] Internal Memory can't be access";
const String LANG_FLASH_STATE = "[FLASH] Saving : ";
const String LANG_FLASH_NAME_DEFINED = "[FLASH] Name";
const String LANG_FLASH_NAME_UNDEFINED = "[FLASH] Create name";
const String LANG_FLASH_SETTINGS_DEFINED = "[FLASH] Loading settings";
const String LANG_FLASH_SETTINGS_JSON_ERROR = "[FLASH] Settings corrupt, reset";
const String LANG_FLASH_SETTINGS_UNDEFINED = "[FLASH] Settings reset";