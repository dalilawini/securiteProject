#include "Wlan.h"

Oled* Display =new Oled();
Battery* battery=new Battery(Display);
Wlan* WIFI=new Wlan(&WiFi,Display);
Fota* FOTA=new Fota(Display);
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


void setup() {
Display->Logo();
//battery->Charge();
  FOTA->begin();
  Serial.begin(115200);
 //irrecv.enableIRIn(); // Start the IR receiver
  WIFI->connect();
 pinMode(16,OUTPUT);
 FOTA->check_for_update();
 //FOTA->dowload_packege();

}
void loop() {
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

