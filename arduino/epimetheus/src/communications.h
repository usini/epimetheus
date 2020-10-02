#include "communications/serial.h"
#include "communications/spiffs.h"

#if defined(WIFI_ENABLE)
    #include <WiFi.h>
    #include "communications/wifi.h"
    
    #if defined(WEB_ENABLE)
        #include "communications/web.h"
    #endif
#endif



