#ifndef TOOLS1_H
#define TOOLS1_H

#include <Arduino.h>

#define L_D 20    //lenght data 

// ------------PAGE--------------
struct DataEspNow {
 char str[L_D];
 uint8_t U8[L_D];
 uint8_t len;
};

struct InfoEspNow {
uint8_t status;
uint8_t MacAddres[6]; 
String Name ;
struct DataEspNow  Send;
struct DataEspNow  Recive;
};

struct esp_now {
const char* PageName ="ESP_NOW";
struct InfoEspNow P_Device[20];
char* AvaibleDevices;
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
