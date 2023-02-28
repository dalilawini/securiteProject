#ifndef TOOLS1_H
#define TOOLS1_H



// ------------PAGE--------------
struct DataEspNow {
char* Name ;
int DataSend;
int DataRecive;
char*  MacAddres;
};

struct esp_now {
char* PageName ="ESP_NOW";
struct DataEspNow PairedDevices[20];
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
char* PageName ="CONNECTION";
struct DataWifi Wifi[20];
uint8_t AvaibleDevices;
struct DataConnection  AccessPoint;
};




struct ir {
char* PageName ="IR";
int Data_send;
int Data_Reciv;
bool SecurityStatus;
};

struct battery{
char* PageName ="BATTERY";
int Voltage;
int ON_time;
int TimeLeft;
};

struct  InfoSystem  {
char* PageName ="About";
char* DeviceName;
char* Model;
char* Mac;
char* Version;
char* SN;
};

struct system {
char* PageName ="SYSTEM";
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

extern MENU Menu;

#endif
