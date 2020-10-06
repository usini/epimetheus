#include "configuration.h" // Configuration <-- Modify this to setup epimetheus
#include "debug.h"
#include "language.h" // Languages
#include "settings.h" // Settings Manager
#include "sensors.h" // Sensors
#include "communications.h" // Communication and storage data

unsigned long lastTime_update = 0;
unsigned long timerDelay_update = 2000;  // readings timer

unsigned long lastTime_scan = 0;
unsigned long timerDelay_scan = 100;  // scan timer

void setup() {
  setup_serial(115200);
  /* Storage (web/data/settings) */
  setup_local_storage();

  /* Sensors */
  setup_sensors(); // get ready to use sensors
  scan_sensors();  // scan and add/remove sensors
  setup_clock();   // Setup Clock (Clock is considerated as a sensor)
  scan_serial();   // Display scan on Serial

  /* Communication */
  #if defined(WIFI_ENABLE)
    setup_wifi(); // Setup WiFi connection (hotspot or not)
  #endif

  #if defined(WEB_ENABLE)
    setup_web();  // Static Web / Websocket
  #endif
}

void loop() {
  // Webserver / Websocket is async not need to update in loop
  update_sensors(); //Get new values from sensors  
  
  //Each timerDelay_update update sensors
  if ((millis() - lastTime_update) > timerDelay_update) {
    debug_serial_start();
    scan_serial();
    update_serial();  //Display values on Serial
    
    if(save_flash) { // If save_flash is active
      if(sensor_changed) { // Recreate header if sensor change
        scan_local_storage(); 
        sensor_changed = false;
      }
      update_local_storage();
    }
    lastTime_update = millis();
    debug_serial_end("update");
  } 
  
  //Each timerDelay_scan check i²c
  if ((millis() - lastTime_scan) > timerDelay_scan) {
    scan_sensors();

    lastTime_scan = millis();
  }
}
