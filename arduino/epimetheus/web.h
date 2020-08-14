#include "web/html_index.h"
#include "web/css_style.h"
#include "web/css_charts.h"
#include "web/js_index.h"
#include "web/js_charts.h"

#include <WiFi.h> // WiFi Functions
#include <WebServer.h> // WebServer Functions
#include <WebSocketsServer.h>
#include <ESPmDNS.h>
#include <NetBIOS.h>


float temp = 0;
float humidity = 0;
float pressure = 0;
float gas = 0;
int lux = 0;

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            debug_println(String(num) + " déconnecté");
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                debug_println(String(num) + "connecté" + "ip: " + String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]));
            }
            break;
        case WStype_TEXT:
            debug_println("Message reçu : " + String((char *)payload));
            break;
      break;
    }
}

// Start WiFi access point and setup webserver
void wifi_setup(char* id) {
  debug_print("WIFI -- ");
  debug_println(id);
  //WiFi.softAP(id);
  WiFi.mode(WIFI_STA);
  WiFi.begin("", "");
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  MDNS.begin(id);
  MDNS.addService("http", "tcp", 80);
  NBNS.begin(id);

  server.on("/", []() {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/html", HTML_INDEX, sizeof(HTML_INDEX));
  });

  server.on("/index.js", []() {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "application/javascript", JS_INDEX, sizeof(JS_INDEX));
  });

  server.on("/style.css", []() {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/css", CSS_STYLE, sizeof(CSS_STYLE));
  });  

 server.on("/charts.js", []() {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "application/javascript", JS_CHARTS, sizeof(JS_CHARTS));
  });

  server.on("/charts.css", []() {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/css", CSS_CHARTS, sizeof(CSS_CHARTS));
  });  

  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}



void wifi_update(){
  server.handleClient();
  webSocket.loop();
}
