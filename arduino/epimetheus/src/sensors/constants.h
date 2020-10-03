/* TSL2561 Digital Luminosity/Lux/Light Sensor - https://www.adafruit.com/product/439 */
const byte TSL2561_0_ADDR = 0x29;
const byte TSL2561_1_ADDR = 0x39;
const byte TSL2561_2_ADDR = 0x49;
const String TSL2561_LINK = "https://www.adafruit.com/product/439";

bool sensors_tsl2561_enable[3] = {false, false, false};
volatile int sensors_tsl2561_lux[3];

/* BME280 - Temperature, Humidity, Pressure Sensor https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout */ 
const byte BME280_0_ADDR = 0x76;
const byte BME280_1_ADDR = 0x77;
const String BME280_LINK = "https://www.adafruit.com/product/2652";

bool sensors_bme280_enable[2] = {false, false};
volatile float sensors_bme280_temp[2];
volatile float sensors_bme280_hum[2];
volatile float sensors_bme280_pressure[2];

/* BME680 - Temperature, Humidity, Pressure and Gas Sensor https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas */
const byte BME680_0_ADDR = 0x76;
const byte BME680_1_ADDR = 0x77;
const String BME680_LINK = "https://www.adafruit.com/product/3660";

bool sensors_bme680_enable[2] = {false, false};
volatile float sensors_bme680_temp[2];
volatile float sensors_bme680_hum[2];
volatile float sensors_bme680_pressure[2];
uint32_t sensors_bme680_gas[2];

/* DS3231 - DS3231 Precision RTC Breakout - https://www.adafruit.com/product/3013 */
const byte DS3231_ADDR = 0x68;
const String DS3231_LINK = "https://www.adafruit.com/product/3013";
bool sensors_ds3231_enable = false;
