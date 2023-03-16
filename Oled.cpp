#include "Oled.h"

Oled::Oled(MENU* menu):Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
 this->Menu=menu;
 Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
 this->clearDisplay();
 this->setTextSize(1);
 this->setTextColor(SSD1306_WHITE);
 this->setCursor(0,0); 
 
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
   id[lk]++;
   else if (d=='z')
   id[lk]--;
   else if (d=='q')
   {
        memcpy(id_back,id,3);
             lk++;
              id[lk]++;
   }
   d=0;
     // Display->Zone('A', page[id_back[0]][id_back[1]]);

   if(id[1]==0&&id[2]==0);
      //Display->setTextSize(2);
     
        //  Display->setTextSize(1);
   this->print("dali");
   
  // Display->Zone('D', page[id[0]][id[1]]);
  }
}


