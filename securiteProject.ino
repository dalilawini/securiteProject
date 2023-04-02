
//-------------------------librery -------------------------
#include "Battery.h"
#include "EspNow.h"
#include "Fota.h"
#include "Oled.h"
#include "Wlan.h"
#include "Time.h"
#include "tools.h"
#include "IR.h"


//----------------------class instance ----------------------
 MENU Menu;
IR* ir=new IR(&Menu);
EspNow* espnow=new EspNow(&Menu);
Wlan* WIFI=new Wlan(&Menu);

Oled* Display =new Oled(&Menu);

Time* time_=new Time();
Battery* battery=new Battery();
Fota* FOTA=new Fota();


// CALL BACK FUNCTION FOR ESPNOW ( this function can't call in other place just you can it here )
void OnDataSent( uint8_t *mac_addr, uint8_t status) {
  espnow->send_cb(mac_addr,status);
}
void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t data_len) {
  espnow->recv_cb(mac_addr, data,data_len);
}

uint8_t device=1;
char data[]="im Master"; 

//uint8_t device=2;
//char data[]="im Slave"; 

enum EspNow_code  real=pairingOK;
bool click_ok=false;
uint8_t click_id=0;



void setup() {
 // Display->OledBegin(&Menu);
  char  ssid_[]="dali";
  char password_[]="123456789";
  WIFI->setSsid(ssid_);
  WIFI->setPassword(password_);
  Serial.begin(115200);



 pinMode(0, INPUT);
Display->Logo();
//battery->Charge();
 // FOTA->begin();

 ir->enableIRIn(); // Start the IR receiver
 WIFI->LoadWifiDesvices();
 //WIFI->connect();
 //FOTA->check_for_update();
 //FOTA->dowload_packege();

 //espnow->configDeviceAP(); //for test find mac_id for master
 //delay(5000);master



espnow->Prefix=" 1";
 espnow->InitESPNow();
//espnow->ScanForSlave();     //master
espnow->send_cb(OnDataSent);//master

//espnow->Pairing(); //slave
espnow->recv_cb(OnDataRecv);//slave
 pinMode(16,OUTPUT);


 
if(device ==1)
{
//espnow->ScanForSlave();

Serial.println("");
for(int i=0;i<Menu.ESP_NOW.NumberOfAvaibleDevices;i++)
 {
    Serial.print("id: ");
    Serial.println(0);
    Serial.print("name: ");
    Serial.println(Menu.ESP_NOW.AvaibleDevices[i].Name);
    Serial.print("RSSI: ");
    Serial.println(Menu.ESP_NOW.AvaibleDevices[i].RSSI);
    Serial.print("Status: ");
    Serial.println((u8)Menu.ESP_NOW.AvaibleDevices[i].status,HEX);
    Serial.println("");
    Serial.print("mac :");
    for (int s = 0; s < 6; s++ )
        {
          Serial.print(Menu.ESP_NOW.AvaibleDevices[i].MacAddres[s] ,HEX);
          if (s != 5) Serial.print(":");
        }
        Serial.println("");

    
 }
}

if(device ==2)
{
espnow->Pairing();
Menu.ESP_NOW.PairingMode.status_paired=paired;
    Serial.print("name: ");
    Serial.println(Menu.ESP_NOW.PairingMode.DeviceName);
    Serial.print("mac: ");
    Serial.println(Menu.ESP_NOW.PairingMode.DeviceMac);

 
}
uint8_t mmmaccc[6]={00,11,22,33,44,55};
espnow->SaveMEM(1, "dali",mmmaccc);

}



void loop() {

espnow->process(Menu.ESP_NOW.Mode);
ir->process();
Display->MeNu();

delay(100);
  }







//time_->update();
//time_->TimeDisplay();




/*
if(device ==2)
{
espnow->listenner();

Serial.print("status: ");
Serial.println(Menu.ESP_NOW.PairingMode.status_paired);

Serial.print("data recved: ");
Serial.println((u8)Menu.ESP_NOW.PairingMode.PairData);

Serial.println("");
   Serial.print("mac :");
    for (int s = 0; s < 6; s++ )
        {
          Serial.print(Menu.ESP_NOW.PairingMode.PairMac[s] ,HEX);
          if (s != 5) Serial.print(":");
        }
Serial.println("");

}

if(device ==1)
{
uint8_t idd=0;
 espnow->sendRequest(idd);
 Serial.print("Status: ");
 Serial.println((u8)Menu.ESP_NOW.AvaibleDevices[idd].status,HEX);
}
 delay(500);

}*/
/*
Serial.println("");

  Serial.print("id: ");
  Serial.println(0);
  Serial.print("name: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Info.Name);

  Serial.print("mac :");
   for (int s = 0; s < 6; s++ )
      {
        Serial.print(Menu.ESP_NOW.P_Device[0].Info.MacAddres[s],HEX);
        if (s != 5) Serial.print(":");
 

     }

  Serial.println("");
  Serial.println("STRING DATA RECEVID");

espnow->sendData(data,0);

  Serial.print("data: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Data.Recive.str);
  Serial.print("data_length: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Data.Recive.len);
  
  Serial.println("");
  Serial.println("STRING DATA SENDED");
  Serial.print("data: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Data.Send.str);
  Serial.print("data_length: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Data.Send.len);
  Serial.println("");
  Serial.println("");
  Serial.println("");

delay(1000);

  Serial.println("");
  Serial.println("CODE  RECEVID");

  espnow->sendCode(real,0);



  Serial.print("CODE: ");
  Serial.print(Menu.ESP_NOW.P_Device[0].Data.Recive.U8);      
  
  Serial.println("");
  Serial.println("CODE  SENDED");
  Serial.print("CODE: ");
  Serial.print(Menu.ESP_NOW.P_Device[0].Data.Send.U8);
  Serial.println("");
  Serial.println("");
  Serial.println("");
delay(1000);

}
/*
espnow->sendData(data,0);

Serial.println("");

  Serial.print("id: ");
  Serial.println(0);
  Serial.print("name: ");
  Serial.println(Menu.ESP_NOW.PairingMode.Name);

  Serial.print("mac :");
  Serial.print(Menu.ESP_NOW.PairingMode.MacAddres);
  
  Serial.println("");
  Serial.println("DATA RECEVID");
  Serial.print("data: ");
  Serial.println(Menu.ESP_NOW.P_Device[255].Data.Recive.str);
  Serial.print("data_length: ");
  Serial.println(Menu.ESP_NOW.P_Device[255  ].Data.Recive.len);
  
  Serial.println("");
  Serial.println("");
  Serial.println("");
delay(1000);
}
*/
/*

     digitalWrite(16,0);

*/


