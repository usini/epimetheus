// Tutorial Web from Spiffs - https://randomnerdtutorials.com/esp32-web-server-spiffs-spi-flash-file-system/
// Content Type - https://developer.mozilla.org/fr/docs/Web/HTTP/Headers/Content-Type
// Websocket - https://techtutorialsx.com/2018/08/14/esp32-async-http-web-server-websockets-introduction/
// Library - https://github.com/me-no-dev/ESPAsyncWebServer
// Arduino JSON - https://github.com/bblanchon/ArduinoJson
// https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonGeneratorExample/JsonGeneratorExample.ino
#include "ESPAsyncWebServer.h"

const int SERVER_PORT = 80;

AsyncWebServer server(SERVER_PORT); // Create Async WebServer on Server Port
AsyncWebSocket ws("/websocket"); //Create Async WebSocket 
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);

// Serve file from SPIFFS on Webserver
void setup_web() {
        Serial.println("~--- Web ---~");
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/index.html", "text/html");
        });

        server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/settings.html", "text/html");
        });
        
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/style.css","text/css");
        });

        server.on("/charts.css", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/charts.css","text/css");
        });
        
        server.on("/slider.css", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/slider.css","text/css");
        });

        server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/script.js","application/javascript");
        });

        server.on("/settings.js", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/settings.js","application/javascript");
        });


        server.on("/charts.js", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/charts.js","application/javascript");
        });

        server.on("/hammerjs.js", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/hammerjs.js","application/javascript");
        });

        server.on("/toast.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/toast.min.js","application/javascript");
        });

        server.on("/chartjs-plugin-zoom.js", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/chartjs-plugin-zoom.js","application/javascript");
        });

        server.on("/radio.svg", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/radio.svg","image/svg+xml");
        });

        server.on("/labsud.svg", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/labsud.svg","image/svg+xml");
        });

        server.on("/save.svg", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/save.svg","image/svg+xml");
        });

        server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/data.csv", "application/octet-stream");
        });

        #if defined(LANG_FR)
          server.on("/lang.js", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/lang_fr.js","application/javascript");
          });
        #endif

        #if defined(LANG_EN)
          server.on("/lang.js", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/lang.js","application/javascript");
          });
        #endif

        ws.onEvent(onWsEvent);
        server.addHandler(&ws);
        server.begin();
}

// Display all founded sensors on websocket
void scan_websocket(AsyncWebSocketClient * client) {
    int id = 0;
    char buffer_websocket[4096];
    String sensor_name = "";
    for(int i = 0; i<3; i++) {
      if(sensors_tsl2561_enable[i]) {
        StaticJsonDocument<512> tsl2561;
        tsl2561["msg"] = "list";
        tsl2561["result"] = true;
        tsl2561["id"] = id;
        sensor_name = "TSL2561_" + String(i);
        tsl2561["sensor"] = sensor_name;
        tsl2561["text"] = LANG_LIGHT;
        tsl2561["unit"] = LUX_UNIT;
        tsl2561["color"] = LUX_COLOR;
        tsl2561["type"] = LUX_TYPE;
        id++;
        serializeJson(tsl2561, buffer_websocket);
        client->text(buffer_websocket);
      }
    }
  
    for(int i = 0; i<2; i++) {
       if(sensors_bme680_enable[i]) {
        sensor_name = "BME680_" + String(i);
        StaticJsonDocument<512> bme680_temp;  
        bme680_temp["msg"] = "list";
        bme680_temp["result"] = true;
        bme680_temp["id"] = id;
        bme680_temp["sensor"] = sensor_name;
        bme680_temp["text"] = LANG_TEMPERATURE;
        bme680_temp["unit"] = TEMP_UNIT;
        bme680_temp["color"] = TEMP_COLOR;
        bme680_temp["type"] = TEMP_TYPE;
        serializeJson(bme680_temp, buffer_websocket);
        client->text(buffer_websocket);
        id++;

        StaticJsonDocument<512> bme680_humidity;  
        bme680_humidity["msg"] = "list";
        bme680_humidity["result"] = true;
        bme680_humidity["id"] = id;
        bme680_humidity["sensor"] = sensor_name;
        bme680_humidity["text"] = LANG_HUMIDITY;
        bme680_humidity["unit"] = HUMIDITY_UNIT;
        bme680_humidity["color"] = HUMIDITY_COLOR;
        bme680_humidity["type"] = HUMIDITY_TYPE;
        serializeJson(bme680_humidity, buffer_websocket);
        client->text(buffer_websocket);
        id++;

        StaticJsonDocument<512> bme680_pressure;  
        bme680_pressure["msg"] = "list";
        bme680_pressure["result"] = true;
        bme680_pressure["id"] = id;
        bme680_pressure["sensor"] = sensor_name;
        bme680_pressure["text"] = LANG_PRESSURE;
        bme680_pressure["unit"] = PRESSURE_UNIT;
        bme680_pressure["color"] = PRESSURE_COLOR;
        bme680_pressure["type"] = PRESSURE_TYPE;
        serializeJson(bme680_pressure, buffer_websocket);
        client->text(buffer_websocket);
        id++;

        StaticJsonDocument<512> bme680_gas;  
        bme680_gas["msg"] = "list";
        bme680_gas["result"] = true;
        bme680_gas["id"] = id;
        bme680_gas["sensor"] = sensor_name;
        bme680_gas["text"] = LANG_GAS;
        bme680_gas["unit"] = GAS_UNIT;
        bme680_gas["color"] = GAS_COLOR;
        bme680_gas["type"] = GAS_TYPE;
        serializeJson(bme680_gas, buffer_websocket);
        client->text(buffer_websocket);
        id++;
       }
    }

    for(int i = 0; i<2; i++) {
       if(sensors_bme280_enable[i]) {
        sensor_name = "BME280_" + String(i);
        StaticJsonDocument<512> bme280_temp;  
        bme280_temp["msg"] = "list";
        bme280_temp["result"] = true;
        bme280_temp["id"] = id;
        bme280_temp["sensor"] = sensor_name;
        bme280_temp["text"] = LANG_TEMPERATURE;
        bme280_temp["unit"] = TEMP_UNIT;
        bme280_temp["color"] = TEMP_COLOR;
        bme280_temp["type"] = TEMP_TYPE;
        serializeJson(bme280_temp, buffer_websocket);
        client->text(buffer_websocket);
        id++;

        StaticJsonDocument<512> bme280_humidity;  
        bme280_humidity["msg"] = "list";
        bme280_humidity["result"] = true;
        bme280_humidity["id"] = id;
        bme280_humidity["sensor"] = sensor_name;
        bme280_humidity["text"] = LANG_HUMIDITY;
        bme280_humidity["unit"] = HUMIDITY_UNIT;
        bme280_humidity["color"] = HUMIDITY_COLOR;
        bme280_humidity["type"] = HUMIDITY_TYPE;
        serializeJson(bme280_humidity, buffer_websocket);
        client->text(buffer_websocket);
        id++;

        StaticJsonDocument<512> bme280_pressure;  
        bme280_pressure["msg"] = "list";
        bme280_pressure["result"] = true;
        bme280_pressure["id"] = id;
        bme280_pressure["sensor"] = sensor_name;
        bme280_pressure["text"] = LANG_PRESSURE;
        bme280_pressure["unit"] = PRESSURE_UNIT;
        bme280_pressure["color"] = PRESSURE_COLOR;
        bme280_pressure["type"] = PRESSURE_TYPE;
        serializeJson(bme280_pressure, buffer_websocket);
        client->text(buffer_websocket);
        id++;
       }
    }
  
}

// Send Data from sensors (not JSON to improve performance)
String update_websocket() {
   String data = "";
   for(int i = 0; i<3; i++) {
     if(sensors_tsl2561_enable[i]){
       data = data + sensors_tsl2561_lux[i] + ";";
     }
   }
   for(int i = 0; i<2; i++) {
      if(sensors_bme680_enable[i]){
        data = data + sensors_bme680_temp[i] + ";";
        data = data + sensors_bme680_hum[i] + ";";
        data = data + sensors_bme680_pressure[i] + ";";
        data = data + sensors_bme680_gas[i] + ";";
      }
   }
   for(int i = 0; i<2; i++) {
      if(sensors_bme280_enable[i]){
        data = data + sensors_bme680_temp[i] + ";";
        data = data + sensors_bme680_hum[i] + ";";
        data = data + sensors_bme680_pressure[i] + ";";
        data = data + sensors_bme680_gas[i] + ";";
      }
   }

   data.remove(data.length() -1 , data.length());
   return data;
}

// Scan Available Network and send it to websocket
void wifi_scan(AsyncWebSocketClient * client) {
  StaticJsonDocument<512> doc; 
  char buffer_websocket[4096];
  Serial.println("~---" + LANG_WIFI_SCAN + "---~");
  doc["msg"] = "wifi_scan";
  int n = WiFi.scanNetworks();

  if (n == 0) {
        doc["result"] = false;
        Serial.println(LANG_WIFI_NO_NETWORK);
    } else {
        doc["result"] = true;
        Serial.print(n);
        Serial.println(LANG_WIFI_NETWORK);
        JsonArray value = doc.createNestedArray("value");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            value.add(WiFi.SSID(i));
        }
    }
    serializeJson(doc, buffer_websocket);
    client->text(buffer_websocket);
  Serial.println("~----------------~");
}

// Open Settings saved on Global Variable
void web_open_settings(AsyncWebSocketClient * client) {
  StaticJsonDocument<512> doc; 
  char buffer_websocket[512];
  doc["msg"] = "open_settings";
  doc["result"] = true;
  doc["wifi1_name"] = wifi1_name;
  doc["wifi2_name"] = wifi2_name;
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);
}

// Save settings on SPIFFS (settings.json)
void web_save_settings(AsyncWebSocketClient * client){
  File file = SPIFFS.open("/settings.json", FILE_WRITE);
  StaticJsonDocument<512> doc; 
  doc["wifi1_name"] = wifi1_name;
  doc["wifi1_pass"] = wifi1_pass;
  doc["wifi2_name"] = wifi2_name;
  doc["wifi2_pass"] = wifi2_pass;
  serializeJson(doc, file);
  StaticJsonDocument<128> doc2;
  char buffer_websocket[128];
  doc2["msg"] = "save_settings";
  doc2["result"] = true;
  serializeJson(doc2, buffer_websocket);
  client->text(buffer_websocket);
  file.close();
}

// Save name on SPIFFS (name.txt)
void web_set_name(AsyncWebSocketClient * client) {
  File file = SPIFFS.open("/name.txt", FILE_WRITE);
  file.print(esp_name);

  StaticJsonDocument<128> doc;
  char buffer_websocket[128];
  doc["msg"] = "save_settings";
  doc["result"] = true;
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);
  file.close();
}

// Get name and send it to websocket
void web_get_name(AsyncWebSocketClient * client) {
  StaticJsonDocument<128> doc;
  char buffer_websocket[128];
  doc["msg"] = "name";
  doc["result"] = true;
  doc["value"] = esp_name;
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);
}

// Get if data is saved on flash
void web_get_flash(AsyncWebSocketClient * client) {
  StaticJsonDocument<128> doc;
  char buffer_websocket[128];
  doc["msg"] = "flash";
  doc["result"] = true;
  doc["value"] = save_flash;
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);
}

// Set if data is saved on flash
void web_set_flash(AsyncWebSocketClient * client) {
  StaticJsonDocument<128> doc;
  if(save_flash) {
    File file = SPIFFS.open("/flash", FILE_WRITE);
    file.print("");
    file.close();
    scan_local_storage();
  } else {
    if (SPIFFS.exists("/flash")) {
      SPIFFS.remove("/flash");
    }
  }
  char buffer_websocket[128];
  doc["msg"] = "save_flash";
  doc["result"] = true;
  doc["value"] = save_flash;
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);
}

// Set clock from websocket
void web_set_clock(AsyncWebSocketClient * client) {
  StaticJsonDocument<128> doc;
  char buffer_websocket[128];
  doc["msg"] = "set_clock";
  doc["result"] = true;
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);
}

// Get clock from RTC
void web_get_clock(AsyncWebSocketClient * client) {
  StaticJsonDocument<128> doc;
  char buffer_websocket[128];
  doc["msg"] = "get_clock";
  doc["result"] = true;
  doc["value"] = String(now.year()) + "/" + String(now.month()) + "/" + String(now.day()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  serializeJson(doc, buffer_websocket);
  client->text(buffer_websocket);  
}

// Event from Websocket (Mostly used to receive order from websocket)
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
  
  // When a client is connected
  if(type == WS_EVT_CONNECT) {
    Serial.println(client->id() + " " + LANG_CONNECTED);
  }

  // When a client is disconnect
  if(type == WS_EVT_DISCONNECT) {
      Serial.println(client->id() + " " + LANG_DISCONNECT);
  }

  // When an error happen
  if(type == WS_EVT_ERROR){
      Serial.println(LANG_WEBSOCKET_ERROR);
  }

  // When a message is received
  if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len){
        //We only manage TEXT data
        if(info->opcode == WS_TEXT) {

        data[len] = 0;
        // Transform JSON text to JSON object
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, data);
        
        if(!error) {
          String message = doc["msg"];
          Serial.println(LANG_RECEIVED_MESSAGE + message);
              
              //If msg:"list" scan
              if(message.equals("list")) {
                  scan_websocket(client);
              }
              //If msg:"update" display data
              else if(message.equals("update")) {
                client->text(update_websocket().c_str());
              }
              //If msg:"wifi_scan" scan wifi
              else if(message.equals("wifi_scan")) {
                Serial.println("Wifi Scan");
                wifi_scan(client);
              }
              //If msg:"open_settings" get settings
              else if(message.equals("open_settings")) {
                web_open_settings(client);
              }
              // If msg:"save_settings" save settings on global variable + store it
              else if(message.equals("save_settings")) {
                wifi1_name = doc["wifi1_name"].as<String>();
                wifi1_pass = doc["wifi1_pass"].as<String>();
                wifi2_name = doc["wifi2_name"].as<String>();
                wifi2_pass = doc["wifi2_pass"].as<String>();
                web_save_settings(client);
              }
              // If msg:"name" show name
              else if(message.equals("name")) {
                web_get_name(client);
              }
              // If msg:"change_name" save name
              else if(message.equals("change_name")) {
                esp_name = doc["value"].as<String>();
                web_set_name(client);
              }
              // If msg:"save_flash" change save to SPIFFS state
              else if(message.equals("save_flash")) {
                save_flash = doc["value"].as<bool>();
                Serial.print(LANG_FLASH_STATE);
                Serial.println(save_flash);
                web_set_flash(client);
              }
              // If msg:"flash" get state of save
              else if(message.equals("flash")) {
                web_get_flash(client);
              } 
              // If msg:"set_clock" set clock
              else if(message.equals("set_clock")){
                rtc.adjust(DateTime(doc["year"], doc["month"], doc["day"], doc["hour"], doc["minute"], doc["second"]));
                web_set_clock(client);
              }
              // If msg:"get_clock" get local clock
              else if(message.equals("get_clock")){
                web_get_clock(client);
              }
              else {
                Serial.println(LANG_WEBSOCKET_INVALID_COMMAND);
              }
          }
          else {
            Serial.println(LANG_WEBSOCKET_INVALID_JSON);
          }
        }
    }
  }
}






