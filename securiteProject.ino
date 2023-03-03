
//-------------------------librery -------------------------
#include "Battery.h"
#include "EspNow.h"
#include "Fota.h"
#include "Oled.h"
#include "Wlan.h"
#include "Time.h"
#include "tools.h"

//----------------------class instance ----------------------
 MENU Menu;
EspNow* espnow=new EspNow(&Menu);

Oled* Display =new Oled();

Time* time_=new Time();
Battery* battery=new Battery();
Wlan* WIFI=new Wlan();
Fota* FOTA=new Fota();


//----------IR-----------
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
//*****************Define Variable *****************


//*****************Global Function *****************

//----------IR-----------gl:
const uint16_t IR_RecvPin = 14;
IRrecv irrecv(IR_RecvPin); // Create an IRrecv object on pin 4
decode_results results;


// CALL BACK FUNCTION FOR ESPNOW ( this function can't call in other place just you can it here )
void OnDataSent( uint8_t *mac_addr, uint8_t status) {
  espnow->send_cb(mac_addr,status);
}
void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t data_len) {
  espnow->recv_cb(mac_addr, data,data_len);
 /* Serial.print("data: ");
  Serial.println((char*)data);
  Serial.print("mac: ");
  Serial.println((char*)mac_addr);
  Serial.print("data_len: ");
  Serial.println(data_len);
*/
}
char data[]="im master";
bool click_ok=false;
uint8_t click_id=0;
void setup() {

  char  ssid_[]="dali";
  char password_[]="123456789";
  WIFI->setSsid(ssid_);
  WIFI->setPassword(password_);
  Serial.begin(115200);



 pinMode(0, INPUT);
//Display->Logo();
//battery->Charge();
 // FOTA->begin();
 //irrecv.enableIRIn(); // Start the IR receiver
 //WIFI->connect();
 //FOTA->check_for_update();
 //FOTA->dowload_packege();

 //espnow->configDeviceAP(); //for test find mac_id for master
 //delay(5000);
  // espnow->InitESPNow();

//espnow->ScanForSlave();     //master
//espnow->send_cb(OnDataSent);//master

//espnow->configDeviceAP(); //slave
//espnow->recv_cb(OnDataRecv);//slave

 pinMode(16,OUTPUT);
/*
Serial.print("page name:");
Serial.println(Menu.CONNECTION.PageName);

for(int i=0;i<Menu.CONNECTION.AvaibleDevices;i++)
{
Serial.print("name: ");
Serial.println(Menu.CONNECTION.Wifi[i].DeviceName);
Serial.print("Mac: ");
Serial.println(Menu.CONNECTION.Wifi[i].Mac);
Serial.print("Signal Strength: ");
Serial.println(Menu.CONNECTION.Wifi[i].SignalStrength);
}
*/
}
void loop() {
 /*if (!digitalRead(0)) 
    {
      click_id++;
      delay(250);
    }

  Display->clearDisplay();
  Display->setTextSize(1);
  Display->setCursor(0,0);
  Display->setCursor(0,10);
  Display->setTextSize(1);
*/
//time_->update();
//time_->TimeDisplay();



/*
  switch (click_id)
  {

    case 1: Display->print("  ESP_NOW");break;
    case 2: Display->print("CONNECTION");break;
    case 3: Display->print("  IR");break;
    case 4: Display->print("  BATTERY");break;
    case 5: Display->print("  SYSTEM");break;
    default : click_id=1;

  }
*/
   // Display->display();
espnow->sendData(data,1);
delay(1000);

Serial.println("");

  Serial.print("id: ");
  Serial.println(0);
  Serial.print("name: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Name);

  Serial.print("mac :");
   for (int s = 0; s < 6; s++ )
      {
        Serial.print(Menu.ESP_NOW.P_Device[0].MacAddres[s],HEX);
        if (s != 5) Serial.print(":");
      }
  Serial.println("");
  Serial.println("DATA RECEVID");
  Serial.print("data: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Recive.str);
  Serial.print("data_length: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Recive.len);
  
  Serial.println("");
  Serial.println("DATA SENDED");
  Serial.print("data: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Send.str);
  Serial.print("data_length: ");
  Serial.println(Menu.ESP_NOW.P_Device[0].Send.len);
  Serial.println("");
  Serial.println("");
  Serial.println("");




/*

  if (irrecv.decode(&results)) {
    irrecv.resume();  // Receive the next value
  }
  Display->IRcode(resultToHexidecimal(&results));
  if(resultToHexidecimal(&results)=="0x00FFE01F")
  {
   digitalWrite(16,1);
   delay(1000);
  
  }
     digitalWrite(16,0);

*/

}
/*
void ESP_NOW(void)
{ 
  Display->setCursor(0,14);
  Display->setTextSize(2);
  Display->setTextColor(SSD1306_WHITE);
  Display->print("  ESP_NOW");
  while (0)
   {
    Display->clearDisplay();
    Display->setTextSize(1);
    Display->setCursor(10,0);
    Display->println("Esp_now :");
    Display->setCursor(10,14);
    click_id==1 ? Display->setTextColor(SSD1306_BLACK, SSD1306_WHITE):Display->setTextColor(SSD1306_WHITE);
    Display->println("* Paired devices");
    Display->setCursor(10,24);
    click_id==2 ? Display->setTextColor(SSD1306_BLACK, SSD1306_WHITE):Display->setTextColor(SSD1306_WHITE);
    Display->println("* Avaible devices");
    Display->display();

   }
}
*/
