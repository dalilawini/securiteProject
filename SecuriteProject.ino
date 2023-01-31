#include "Wlan.h"

Oled* Display =new Oled();
Battery* battery=new Battery(Display);
Wlan* WIFI=new Wlan(&WiFi,Display);
//*****************Include file *****************


//----------IR-----------
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
//*****************Define Variable *****************


//*****************Global Function *****************

//----------IR-----------
const uint16_t IR_RecvPin = 14;
IRrecv irrecv(IR_RecvPin); // Create an IRrecv object on pin 4
decode_results results;


void setup() {
  Display->Logo();
  battery->Charge();
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the IR receiver
  WIFI->connect();
  pinMode(16,OUTPUT);
}
void loop() {

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

  

}











/*
void loop() {
  // put your main code here, to run repeatedly:
 //dlay=millis();
   if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    display.clearDisplay();
    display.setCursor(0,0); 
    display.println("IRrecv Code :");
    display.print(resultToHexidecimal(&results));
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    display.display();
    irrecv.resume();  // Receive the next value
     Serial.print("IN of function:");
     temps=millis()-dlay;
 Serial.println(temps);
   dlay=millis();
     display.invertDisplay(false);

  }
if(temps>200)
 display.invertDisplay(true);


   
   delay(1000);
   display.clearDisplay();
   display.drawBitmap(104,0,EmpttyBattery,24,8, 1);
   display.display();
delay(500);
   display.clearDisplay();
   display.drawBitmap(104,0,LowBattery, 24,8, 1);
   display.display();
delay(500);
    display.clearDisplay();
   display.drawBitmap(104,0,MediumBattery, 24,8, 1);
   display.display();
delay(500);
    display.clearDisplay();
   display.drawBitmap(104,0,HighBattery, 24,8, 1);
   display.display();
delay(500);
    display.clearDisplay();
   display.drawBitmap(104,0,FullBattery, 24,8, 1);
   display.display();
delay(500);

}
*/