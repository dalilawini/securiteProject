#include "Wlan.h"


 Wlan::Wlan(MENU* menu)
{
this->menu=menu;
menu->SYSTEM.About.Mac=WiFi.macAddress();
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


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  menu->Wifi.NetworkInfo.DeviceName=WiFi.SSID();
  menu->Wifi.NetworkInfo.ip=WiFi.localIP();
  menu->Wifi.NetworkInfo.SignalStrength=WiFi.RSSI();
  menu->Wifi.NetworkInfo.Mac=WiFi.BSSIDstr();
 // WiFi.BSSIDstr(i);



  return true;
 }

 
void Wlan::LoadWifiDesvices()
{
  
uint8_t DevicesNumber = WiFi.scanNetworks();
menu->Wifi.ScanResult=DevicesNumber;
for(int i=0;i<DevicesNumber;i++)
{

menu->Wifi.AvaibleNetworks[i].DeviceName=WiFi.SSID(i);
menu->Wifi.AvaibleNetworks[i].SignalStrength=WiFi.RSSI(i);
}

}





