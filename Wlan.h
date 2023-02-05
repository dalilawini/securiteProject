#include "Fota.h"


//#include "Oled.h"

#include <Arduino.h>

#ifndef WLAN_H_
#define WLAN_H_
#endif 

class Wlan
{

private:
    const char* ssid     = "dali";
    const char* password = "123456789";
    ESP8266WiFiClass* WiFi;
    Oled* Display ;
public:


    Wlan(ESP8266WiFiClass* Wifi_Instance,Oled* Display_Instance);
    ~Wlan(); 
    bool connect();

};
