#include "Wlan.h"


 Wlan::Wlan(ESP8266WiFiClass* Wifi_Instance,Oled* Display_Instance)
{
  WiFi=Wifi_Instance;
  Display=Display_Instance;
}

bool Wlan::connect()
 { 
  WiFi->mode(WIFI_STA);
  WiFi->begin(ssid, password);

  Display->wifi_init(WiFi);

  while (WiFi->status() != WL_CONNECTED) {
    delay(500);
  }

  Display->wifi_connect();

  return true;
 }
  






