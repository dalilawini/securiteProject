
#include "Oled.h"

Oled::Oled():Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
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
