#include "EspNow.h"
#include "Time.h"
Oled* Display =new Oled();
Time* time_=new Time(Display);
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


// CALL BACK FUNCTION FOR ESPNOW ( this function can't call in other place just you can it here )
void OnDataSent( uint8_t *mac_addr, uint8_t status) {
  espnow->send_cb(mac_addr,status);
}
void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t data_len) {
  espnow->recv_cb(mac_addr, data,data_len);
}

unsigned long epochTime;
void setup() {
Display->Logo();
//battery->Charge();
 // FOTA->begin();
  Serial.begin(115200);
 //irrecv.enableIRIn(); // Start the IR receiver
 WIFI->connect();
 //FOTA->check_for_update();
 //FOTA->dowload_packege();
 
 //espnow->configDeviceAP(); //slave
 //espnow->ScanForSlave();
 //espnow->InitESPNow();//slave
 //espnow->send_cb(OnDataSent);
 //espnow->recv_cb(OnDataRecv);//slave
 pinMode(16,OUTPUT);

 //time_->begin();
 

}
void loop() {
time_->TimeDisplay();

 delay(1000);


/*
  //espnow->sendData(41);

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

