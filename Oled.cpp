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
   menu[1]= Menu->CONNECTION.Name;
   menu[2]= Menu->IR.Name;
   menu[3]= Menu->BATTERY.Name;
   menu[4]= Menu->SYSTEM.Name;

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
              this->println(txt);
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

  if(!(page&0x0fff))
  {    
    Zone('A',"menu");
    this->setTextSize(2);
    Zone('D',menu[id-1]);
    title[0]=menu[id-1];
  }
  else if(!(page&0x00ff))
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
              Zone('D',Menu->CONNECTION.PageName[id-1]);
              title[1]=Menu->CONNECTION.PageName[id-1];
              break;
      case 5:  
              this->setTextSize(2);
              Zone('D',Menu->SYSTEM.PageName[id-1]);
              title[1]=Menu->SYSTEM.PageName[id-1];
              break;    
              
    }
  }
  else if(!(page&0x000f))
  {
    Zone('A',title[1]);
    switch ((page&0xff00)>>8)
    {
      case 0x21:  
              this->setTextSize(1);
              Zone('D'
              Zone('D',Menu->CONNECTION.Wifi[id-1].DeviceName.c_str());
              break;
      case 0x22:  
              this->setTextSize(1);
              Zone('D',Menu->CONNECTION.PageName[id-1]);
              break;
      case 0x23:  
              this->setTextSize(2);
              Zone('D',Menu->SYSTEM.PageName[id-1]);
              break;    
              
    };
  }


Serial.println((page&0xff00)>>8,HEX);

  
  
        

    //Zone('A', page[id_back[0]][id_back[1]]);

  // Serial.print(page[0]);
  /* for(int i=0;i<3;i++)
   Serial.print(id[i]);
      Serial.println("");

   */
  // Display->Zone('D', page[id[0]][id[1]]);
     d=0;

  }
}


