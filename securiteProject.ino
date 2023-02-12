#include "Wlan.h"
#include "EspNow.h"

Oled* Display =new Oled();
Battery* battery=new Battery(Display);
Wlan* WIFI=new Wlan(&WiFi,Display);
Fota* FOTA=new Fota(Display);
EspNow* espnow=new EspNow();
//*****************Include file *****************


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


// callback when data is sent from Master to Slave
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: "); Serial.println(macStr);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
Display->Logo();
//battery->Charge();
 // FOTA->begin();
  Serial.begin(115200);
 //irrecv.enableIRIn(); // Start the IR receiver
 // WIFI->connect();
 pinMode(16,OUTPUT);
 //FOTA->check_for_update();
 //FOTA->dowload_packege();

 espnow->ScanForSlave();
 espnow->InitESPNow();


 

}
void loop() {
  espnow->sendData(41);
  delay(1000);
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

