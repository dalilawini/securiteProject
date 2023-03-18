#include "Wlan.h"


 Wlan::Wlan(MENU* menu)
{
this->menu=menu;
}

char* Wlan::getSsid()
    {
     return this->ssid;
    }


void Wlan::setSsid(char *ssid)
    {
        this->ssid = ssid;
    }


char* Wlan::getPassword()
    {
        return this->password;
    }

void Wlan::setPassword(char *password)
    {
        this->password = password;
    }
  

bool Wlan::connect()
 { 
  WiFi.mode(WIFI_STA);
  this->LoadWifiDesvices();
  WiFi.begin(ssid, password);

  //this->wifi_init();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //this->wifi_connect();

  return true;
 }

 
void Wlan::LoadWifiDesvices()
{
  
uint8_t DevicesNumber = WiFi.scanNetworks();
menu->CONNECTION.AvaibleDevices=DevicesNumber;
for(int i=0;i<DevicesNumber;i++)
{

menu->CONNECTION.Wifi[i].DeviceName=WiFi.SSID(i);
menu->CONNECTION.Wifi[i].Mac=WiFi.BSSIDstr(i);
menu->CONNECTION.Wifi[i].SignalStrength=WiFi.RSSI(i);
}

}





