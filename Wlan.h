#ifndef WLAN_H_
#define WLAN_H_

#include "tools.h"
#include <ESP8266WiFi.h>
#include <Arduino.h>



class Wlan
{

private:
     char *ssid ;
     char *password;
     MENU* menu;


public:

    Wlan(MENU* menu);
    ~Wlan();
     
    bool connect();
    void LoadWifiDesvices();

    char* getSsid();
    void setSsid(char *ssid);
    char* getPassword();
    void setPassword(char *password);
};
#endif 