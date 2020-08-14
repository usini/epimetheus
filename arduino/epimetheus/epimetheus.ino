#define WIFI_AP          false
#define WIFI_SSID        ""
#define WIFI_PASSWORD    ""
#define MQTT             true
#define MQTT_SERVER      "192.168.0."
#define MQTT_SERVERPORT  1883                   // use 8883 for SSL
#define MQTT_USERNAME    ""
#define MQTT_KEY         ""

// https://randomnerdtutorials.com/esp32-bme680-web-server-arduino/

#include "debug.h"
#include "web.h"
#include "bme680.h"
#include "tsl2561.h"
#include "st7789.h"
//#include "fan.h"
//#include "motor.h"

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;  // send readings timer

void setup() {
  debug_start();
  setup_bme680();
  setup_st7789(5);
  wifi_setup("Epimetheus");
  debug_println(" ~~ Epimetheus ~~ ");
}

void loop() {
  wifi_update();
  if ((millis() - lastTime) > timerDelay) {
    update_bme680();
    update_tsl_2561();

    debug_println(" --------------- ");

    debug_print("Température : ");
    debug_print(String(temp));
    debug_println(" °C");

    debug_print("Humidité : ");
    debug_print(String(humidity));
    debug_println(" %");

    debug_print("Pression atmosphérique : ");
    debug_print(String(pressure));
    debug_println(" hPA");

    debug_print("Gaz : ");
    debug_print(String(gas));
    debug_println(" KOhms");

    debug_print("Luminosité : ");
    debug_print(String(lux));
    debug_println(" Lux");

    debug_println(" --------------- ");

    int temp_color = TFT_RED;
    if (temp < 60) {
      if (temp > 40) {
        temp_color = TFT_GREEN;
      }
    }

    tft.fillScreen(TFT_BLACK);
    drawBar(0, temp_color, map(temp, 0, 85, 0, 240));
    drawBar(1, TFT_BLUE, map(humidity, 0, 100, 0, 240));
    drawBar(2, TFT_ORANGE, map(lux, 0, 40000, 0, 240));
    drawBar(3, TFT_DARKGREY, map(gas, 500, 0, 0, 240));
    drawBar(4, TFT_PURPLE, map(pressure, 900, 1100, 0, 240));

    drawValue(0, String(temp), "°C");
    drawValue(1, String(humidity), "%");
    drawValue(2, String(lux), "Lux");
    drawValue(3, String(gas), "Kohm");
    drawValue(4, String(pressure), "hPa");
    webSocket.broadcastTXT("{ \"temp\": " + String(temp) + ", \"hum\": " + String(humidity) + ", \"pressure\": " + String(pressure) + ", \"gas\": " + String(gas) + ", \"lux\": " + String(lux) + "}");
    
    if (MQTT) {
      mqtt_temp.publish(temp);
      mqtt_humidity.publish(humidity);
      mqtt_pressure.publish(lux);
      mqtt_gas.publish(gas);
      mqtt_lux.publish(pressure);
    }
    lastTime = millis();
  }
}
