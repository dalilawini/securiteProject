#ifndef WLAN_H_
#define WLAN_H_
#include "Fota.h"
#include "tools.h"


//#include "Oled.h"

#include <Arduino.h>



class Wlan
{

private:
     char *ssid ;
     char *password;



    ESP8266WiFiClass* WiFi;
    Oled* Display ;
public:

    Wlan(ESP8266WiFiClass* Wifi_Instance,Oled* Display_Instance);
    ~Wlan();
     
    bool connect();
    void LoadWifiDesvices();

    char* getSsid();
    void setSsid(char *ssid);
    char* getPassword();
    void setPassword(char *password);
};
#endif 