#ifndef TOOLS1_H
#define TOOLS1_H

#include <Arduino.h>

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
  enum status_ status=ready;
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



struct  esp_now{
const char* PageName ="ESP_NOW";
struct Esp_Now P_Device[20];
struct Info1EspNow AvaibleDevices[20]= {};
uint8_t NumberOfAvaibleDevices;
struct Info2EspNow PairingMode;
};

struct  DataConnection{
String DeviceName;
String IP;
int Mac;
};

struct  DataWifi{
String DeviceName;
String Mac;
int  SignalStrength;
};

struct Connection {
const char* PageName ="CONNECTION";
struct DataWifi Wifi[20];
uint8_t AvaibleDevices;
struct DataConnection  AccessPoint;
};




struct ir {
const char* PageName ="IR";
int Data_send;
int Data_Reciv;
bool SecurityStatus;
};

struct battery{
const char* PageName ="BATTERY";
int Voltage;
int ON_time;
int TimeLeft;
};

struct  InfoSystem  {
const char* PageName ="About";
char* DeviceName;
char* Model;
char* Mac;
char* Version;
char* SN;
};

struct system {
const char* PageName ="SYSTEM";
struct InfoSystem About;
int Update;
};



typedef struct MENU {
struct esp_now ESP_NOW;
struct Connection CONNECTION;
struct ir IR;
struct battery BATTERY;
struct system SYSTEM;
}MENU;


#endif
