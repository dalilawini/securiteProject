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

bool click_ok=false;
uint8_t click_id=0;

const char* menu_name[5] = {
"  ESP_NOW",
"CONNECTION",
"  IR",
"  BATTERY",
"  SYSTEM",
};

const char* page_ESP_NOW[2] = {
" Paired devices",
"Avaible devices",
};

const char* sub_page_ESP_NOW[2] = {
" Slave 1",
" Slave 2"
};

const char* str_data_ESP_NOW[3] = {
"data send: ",
"data recive: ",
"mac slave: "
};

const int data_ESP_NOW[3] = {
10,
20,
30
};


typedef struct SUB_PAGE{
  String name="empty";
  String str_data[5]={"empty","empty","empty","empty","empty"};
  int data[5]={0,0,0,0,0};

}SUB_PAGE;

typedef struct PAGE{
  String name="empty";
  SUB_PAGE sub_page[5];
  String str_data[5]={"empty","empty","empty","empty","empty"};
  int data[5]={0,0,0,0,0};

}PAGE;

typedef struct MENU{
 String name="empty";
 PAGE page[4];
}MENU;

 MENU menu[5];

void setup() {
   for (int i=0;i<5;i++)
menu[i].name=menu_name[i];

  menu[0].page[0].name=page_ESP_NOW[0];

    menu[0].page[0].sub_page[0].name=sub_page_ESP_NOW[0];

      menu[0].page[0].sub_page[0].str_data[0]=str_data_ESP_NOW[0];
      menu[0].page[0].sub_page[0].str_data[1]=str_data_ESP_NOW[1];
      menu[0].page[0].sub_page[0].str_data[2]=str_data_ESP_NOW[2];
      menu[0].page[0].sub_page[0].data[0]=data_ESP_NOW[0];
      menu[0].page[0].sub_page[0].data[1]=data_ESP_NOW[1];
      menu[0].page[0].sub_page[0].data[2]=data_ESP_NOW[2];
 
    menu[0].page[0].sub_page[1].name=sub_page_ESP_NOW[1];

      menu[0].page[0].sub_page[1].str_data[0]=str_data_ESP_NOW[0];
      menu[0].page[0].sub_page[1].str_data[1]=str_data_ESP_NOW[1];
      menu[0].page[0].sub_page[1].str_data[2]=str_data_ESP_NOW[2];
      menu[0].page[0].sub_page[1].data[0]=data_ESP_NOW[0];
      menu[0].page[0].sub_page[1].data[1]=data_ESP_NOW[1];
      menu[0].page[0].sub_page[1].data[2]=data_ESP_NOW[2];     
      

  menu[0].page[1].name=page_ESP_NOW[1];

    menu[0].page[1].sub_page[0].name=sub_page_ESP_NOW[0];

    menu[0].page[1].sub_page[1].name=sub_page_ESP_NOW[1];

     


 pinMode(0, INPUT);
Display->Logo();
//battery->Charge();
 // FOTA->begin();
  Serial.begin(115200);
 //irrecv.enableIRIn(); // Start the IR receiver
 //WIFI->connect();
 //FOTA->check_for_update();
 //FOTA->dowload_packege();
 
 //espnow->configDeviceAP(); //slave
 //espnow->ScanForSlave();
 //espnow->InitESPNow();//slave
 //espnow->send_cb(OnDataSent);
 //espnow->recv_cb(OnDataRecv);//slave
 pinMode(16,OUTPUT);
 //time_->TimeDisplay();

 

}
void loop() {
 if (!digitalRead(0)) 
    {
      click_id++;
      delay(250);
    }

  Display->clearDisplay();
  Display->setTextSize(1);
  Display->setCursor(0,0);
Display->println (menu[0].page[click_id].name);
  Display->setCursor(0,10);
  Display->setTextSize(1);

Display->println(menu[0].page[click_id].sub_page[0].name);

Display->println(menu[0].page[click_id].sub_page[1].name);



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
    Display->display();


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
