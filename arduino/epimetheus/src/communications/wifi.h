#include <WiFiMulti.h>
#include <ESPmDNS.h>

WiFiMulti wifiMulti; // WiFiMulti is used to try to connect to multiples SSID
bool wifi_enable = true;
const int WIFI_TIMEOUT = 5000; //Time out for WiFi (in ms)

void setup_wifi() {
    Serial.println("~---- WIFI ----~"); 
    wifiMulti.addAP(wifi1_name.c_str(), wifi1_pass.c_str()); // Add WiFi1 (stored from settings)
    wifiMulti.addAP(wifi2_name.c_str(), wifi2_pass.c_str()); // Add WiFi2 (stored from settings)

    unsigned timer_wifi = millis();

    Serial.println(LANG_WIFI_CONNECTION);

    // Check if Wifi Connection is established for WIFI_TIMEOUT ms
    while(wifiMulti.run() != WL_CONNECTED) {
      if ((millis() - timer_wifi) > WIFI_TIMEOUT) {
        wifi_enable = false;
        break;   
      }
    }
    
    // If WiFi connection was established
    if(wifi_enable){
        // Display Connection name and IP on Serial
        Serial.print(LANG_WIFI_CONNECTION_ESTABLISHED);
        Serial.print(WiFi.SSID());
        MDNS.begin(esp_name.c_str()); // Create Bonjour Name (so you can connect using [esp_name].local)
        Serial.print("[IP] - http://");
        Serial.println(WiFi.localIP());
        Serial.println("[MDNS] - http://" + esp_name + ".local");
    } else { // If WiFi connection has failed go to AP mode
        Serial.print(LANG_WIFI_CONNECTION_FAILED);
        Serial.println(esp_name);
        WiFi.softAP(esp_name.c_str());
    }

}
