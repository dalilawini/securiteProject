#ifndef WLAN_H_
#define WLAN_H_
#include "Fota.h"


//#include "Oled.h"

#include <Arduino.h>




class Wlan
{

private:
    const char* ssid     = "TOPNET_8CD0";
    const char* password = "7loaqeb4nu";
    ESP8266WiFiClass* WiFi;
    Oled* Display ;
public:

    Wlan(ESP8266WiFiClass* Wifi_Instance,Oled* Display_Instance);
    ~Wlan(); 
    bool connect();

};
#endif 