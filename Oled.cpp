#include "Oled.h"

Oled::Oled(MENU* menu_):Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
 this->Menu=menu_;
 Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
 this->clearDisplay();
 this->setTextSize(1);
 this->setTextColor(SSD1306_WHITE);
 this->setCursor(0,0); 
   menu[0]= Menu->ESP_NOW.Name;
   menu[1]= Menu->Wifi.Name;
   menu[2]= Menu->IR.Name;
   menu[3]= Menu->BATTERY.Name;
   menu[4]= Menu->SYSTEM.Name;
   menu[5]= Menu->RESET.Name;
   Menu->ESP_NOW.AvaibleDevices[0].Name = "Scaninng ...";


}

Oled::~Oled()
{
}



void Oled::Logo()
{
  this->clearDisplay();
  this->setCursor(20,5);
  this->setTextSize(3);
  this->println("NouDa");
  this->display();
  delay(1000);
  this->setTextSize(1);
  this->setCursor(0,0);
  this->clearDisplay();
 
}
void Oled::wifi_connect()
{    
  this->clearDisplay();
  this->setCursor(0,0);
  this->println("WiFi connected");
  this->print("IP: ");
  this->println(WiFi.localIP());
  this->print("ESP Board MAC Address:  ");
  this->println(WiFi.macAddress());
  this->display();
  delay(2000);
}


void Oled::wifi_init()
{ 
  this->clearDisplay();
  this->setCursor(0,0);
  this->print("Connecting to :");
  this->print(WiFi.SSID());
  this->display();
}

void Oled::IRcode(String code)
{
    this->clearDisplay();
    this->setCursor(0,0); 
    this->println("IRrecv Code :");
    this->print(code);
    this->display();
}


void Oled::Zone(char ZoNe,const char* txt)
{     
  this->setTextColor(SSD1306_WHITE);
  switch (ZoNe)
  {
    case 'A': clearZone(zone.A.x,zone.A.y,zone.A.xf,zone.A.yf);
              this->setCursor(zone.A.x,zone.A.y); 
              this->setTextSize(1);
              this->println(txt);
              this->display();
              break;

    case 'B': clearZone(zone.B.x,zone.B.y,zone.B.xf,zone.B.yf);
              this->setCursor(zone.B.x,zone.B.y);
              this->setTextSize(1); 
              this->println(txt);
              this->display();
              break;

    case 'C': clearZone(zone.C.x,zone.C.y,zone.C.xf,zone.C.yf);
              this->setCursor(zone.C.x,zone.C.y); 
              this->setTextSize(1);
              this->println(txt);
              this->display();
              break;   

    case 'D': clearZone(zone.D.x,zone.D.y,zone.D.xf,zone.D.yf);
              this->setCursor(zone.D.x,zone.D.y); 
              this->print(txt);
              this->display();
              break;
  }
  

  
}

void Oled::clearZone(uint8_t x,uint8_t y, uint8_t xf ,uint8_t yf)
{
  for(int i=x;i<xf;i++)
    for(int j=y;j<yf;j++)
        this->drawPixel(i, j, SSD1306_BLACK);
}


void Oled::MeNu()
{
 
  
  if (Serial.available()) {
    int d=Serial.read();
   if (d=='a')
   id++;
   else if (d=='z')
   id--;
   else if (d=='q')
   {    
     id=1;
     page_jump-=4;
     BasePage=page;
   }
      else if (d=='w')
   {    
     id=1;
     page_jump=12;
     BasePage=0;
   }
   
   page=BasePage+(id<<page_jump);
   Serial.println(page,HEX);
d=0;
  }
  if(!(page&0x0fff))                       //--------------------------------------> Menu 
  {    
    Zone('A',"menu");
    Zone('A',"menu");
    this->setTextSize(2);
    Zone('D',menu[id-1]);
    title[0]=menu[id-1];
  }
  else if(!(page&0x00ff))                  //--------------------------------------> PAGE 
  {
    Zone('A',title[0]);
    switch (page>>12)
    {
      case 1:  
              this->setTextSize(1);
              Zone('D',Menu->ESP_NOW.PageName[id-1]);
              title[1]=Menu->ESP_NOW.PageName[id-1];
              break;
      case 2:  
              this->setTextSize(1);
              Zone('D',Menu->Wifi.PageName[id-1]);
              title[1]=Menu->Wifi.PageName[id-1];
              break;
      case 3:
              this->setTextSize(1);              
              Zone('D',"Send: ");
              this->println(Menu->IR.Data_send);
              this->print("Recive: ");
              this->println(Menu->IR.Data_Reciv);
              this->display();
              break;
      case 5:  
              this->setTextSize(2);
              Zone('D',Menu->SYSTEM.PageName[id-1]);
              title[1]=Menu->SYSTEM.PageName[id-1];
              break;    
      case 6:
            this->setTextSize(1);
            Zone('D',"CLEAR DATA");
            title[1]="CLEAR DATA";
            break; 
              
    }
  }
  else if(!(page&0x000f))                   //--------------------------------------> SUB PAGE 
  {
    Zone('A',title[1]);
    switch ((page&0xff00)>>8)
    {
      case 0x11:
              this->setTextSize(1);
              Menu->ESP_NOW.Mode=AvaibleDevices;
              Zone('D',Menu->ESP_NOW.AvaibleDevices[id-1].Name.c_str());
              Menu->ESP_NOW.AvaibleDevices_id=-1;
              Menu->ESP_NOW.AvaibleDevices[id-1].status=ready;              
              title[2]=Menu->ESP_NOW.AvaibleDevices[id-1].Name.c_str();
              break;
      case 0x12:
              this->setTextSize(1);
              Menu->ESP_NOW.Mode=PairedDevices;
              Zone('D',Menu->ESP_NOW.P_Device[id-1].Info.Name.c_str());

              this->println("");
              for (int s = 0; s < 6; s++ )
              {
                this->print(Menu->ESP_NOW.P_Device[id-1].Info.MacAddres[s]);
                if (s != 5) this->print(":");
              }
              
              this->display();
              break;
      case 0x13:
              this->setTextSize(1);
              Menu->ESP_NOW.Mode=PairingMode;
              //Zone('D',Menu->ESP_NOW.PairingMode. .AvaibleDevices[id-1].Name.c_str());
              break;
      case 0x21:  
              this->setTextSize(1);
              Zone('D',Menu->Wifi.AvaibleNetworks[id-1].DeviceName.c_str());
              break;
      case 0x22:  
              this->clearDisplay();
              this->setTextSize(1);
              this->setCursor(0,0);
              this->print("name: ");
              this->println(Menu->Wifi.NetworkInfo.DeviceName);
              this->print("ip: ");
              this->println(Menu->Wifi.NetworkInfo.ip);
              this->print("signal: ");
              this->println(Menu->Wifi.NetworkInfo.SignalStrength);
              this->print("mac:");
              this->println(Menu->Wifi.NetworkInfo.Mac);
              this->display();
              break;
      case 0x23:  
              this->setTextSize(1);
              Zone('D',(const char *)"name: ");
              this->println(Menu->Wifi.AccessPoint.DeviceName);
              this->print("ip: ");
              this->println(Menu->Wifi.AccessPoint.IP);
              this->print("mac:");
              this->println(Menu->Wifi.AccessPoint.Mac);
              this->display();              
              break;   
      case 0x51:
              this->setTextSize(1);
              clearZone(zone.D.x,zone.D.y,zone.D.xf,zone.D.yf);
              this->setCursor(zone.D.x,zone.D.y); 
              this->println(Menu->SYSTEM.About.DeviceName);
              this->print("Model: ");
              this->println(Menu->SYSTEM.About.Model);
              this->display();              
              break;
      case 0x52:
              this->setTextSize(1);
              Zone('D',Menu->SYSTEM.Update.c_str());
              break;  

      case 0x61:
            Menu->ESP_NOW.Mode=resetMode;
            this->setTextSize(1);
            Zone('D',"Clear all data user ... ");
            break;              
              
    };
  }
  else if(page&0x000f)                   //--------------------------------------> SUB PAGE 
  {
    Zone('A',title[2]);
    switch ((page&0xff00)>>8)
    {  
      case 0x11:              
                this->setTextSize(2);
                switch (Menu->ESP_NOW.AvaibleDevices[((page&0x00f0)>>4)-1].status)
                {
                  case ready  : Zone('D',"Connecting ..."); break;
                  case paired : Zone('D',"paired");         break;
                  case refused: Zone('D',"refused");        break;
                  case failed : Zone('D',"failed"); page=0x1100;     break;

                };
                Menu->ESP_NOW.AvaibleDevices_id=((page&0x00f0)>>4)-1;
                Menu->ESP_NOW.Mode=idl;
                break;


    };
  }
        
          //Zone('A', page[id_back[0]][id_back[1]]);

        // Serial.print(page[0]);
        /* for(int i=0;i<3;i++)
        Serial.print(id[i]);
            Serial.println("");

        */
        // Display->Zone('D', page[id[0]][id[1]]);

  
}


