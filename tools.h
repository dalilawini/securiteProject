#ifndef TOOLS_H
#define TOOLS_H

#include <Arduino.h>
#include <IPAddress.h>

#define L_D 20    //lenght data 
//---------------ESP_NOw-----------------
enum EspNow_code{
empty=0x00,
pairingRequest=0x10,
pairingRefused,
pairingOK,
pairingIDL


};

// ------------PAGE--------------
struct ValueEspNow {
 char str[L_D];
 enum EspNow_code U8;
 uint8_t len;
};

struct DataEspNow {
struct ValueEspNow  Send;
struct ValueEspNow  Recive;
};
enum status_{
  failed=0,
  ready,
  paired,
  refused,
  IDL

};

struct Info1EspNow {
  uint8_t id;

  String Name ;
  enum EspNow_code Data_U8;
  int32_t RSSI;     // wifi Signal Strength Indicato
  enum status_ status=IDL;
  String BSSIDstr ; //mac
  uint8_t MacAddres[6]; 
  uint8_t channel ;
  uint8_t encrypt[6];           /**< ESPNOW peer local master key that is used to encrypt data */
  uint8_t encrypt_len ;      

};

struct Info2EspNow {
enum status_ status_paired;
String DeviceName ;
String DeviceMac;
enum EspNow_code PairData ;
uint8_t PairMac[6]; 

};

struct Info3EspNow {
uint8_t status;
String Name ;
uint8_t MacAddres[6];
};

struct Esp_Now{
struct DataEspNow Data;
struct Info3EspNow Info;
};


enum esp_now_Mode{
  idl=0,
  AvaibleDevices,
  PairedDevices,
  PairingMode
};

struct  esp_now{
const char* Name ="ESP_NOW";
const char* PageName[3]={"Avaible Devices","Paired Devices","Pairing Mode"};
enum esp_now_Mode Mode;
int8_t AvaibleDevices_id=-1;
struct Info1EspNow AvaibleDevices[20]= {};
struct Esp_Now P_Device[20];
struct Info2EspNow PairingMode;
uint8_t NumberOfAvaibleDevices;
};

struct  DataConnection{
String DeviceName;
IPAddress IP;
String Mac;
};

struct  DataWifi_1{
String DeviceName;
int  SignalStrength;
};

struct  DataWifi_2{
String DeviceName;
String Mac;
IPAddress ip;
int  SignalStrength;
};

struct WIFI {
const char* Name ="Wifi";
const char*PageName[3]={"Avaible networks","Network Info","Access Point"};
struct DataWifi_1 AvaibleNetworks[20];
uint8_t ScanResult;
struct DataWifi_2 NetworkInfo;
struct DataConnection  AccessPoint;
};




struct ir {
const char* Name ="IR";
int Data_send;
int Data_Reciv;
bool SecurityStatus;
};

struct battery{
const char* Name ="BATTERY";
int Voltage;
int ON_time;
int TimeLeft;
};

struct  InfoSystem  {
String DeviceName="InfraRedSecurity";
String Model="NouDa_V0";
String Bord="esp8266";
String Mac;
String Version="1.0.0.1";
String SN="N230896D10119500";
};

struct system {
const char* Name ="SYSTEM";
const char* PageName[2]={"About","Update"};
struct InfoSystem About;
String Update="Up To Date ";
};



typedef struct MENU {
struct esp_now ESP_NOW;
struct WIFI Wifi;
struct ir IR;
struct battery BATTERY;
struct system SYSTEM;
}MENU;


#endif
