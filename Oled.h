#ifndef OLED_H_
#define OLED_H_


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "tools.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16






class Oled:public Adafruit_SSD1306,ESP8266WiFiClass
{

private:
  MENU* Menu;

  const char* menu[5]=
  { 
    Menu->ESP_NOW.Name,
    Menu->CONNECTION.Name,
    Menu->IR.Name,
    Menu->BATTERY.Name,
    Menu->SYSTEM.Name
  };
  const char * page[3];
//  memcpy(page,Menu->ESP_NOW.PageName,3);

 // 
  
//temporelle
  uint8_t id[2]={1,0};
uint8_t id_back[2]={0,0};
uint8_t lk=0;
//-----------------

  struct cordonne {
    uint8_t x;
    uint8_t y;
    uint8_t xf;
    uint8_t yf;
  };

  struct ZONE {
    struct cordonne A;
    struct cordonne B;
    struct cordonne C;
    struct cordonne D;
  };
    struct ZONE zone ={{0,0,87,10},{0,0,87,10},{88,0,128,10},{0,10,128,32}};
    void clearZone(uint8_t x,uint8_t y, uint8_t xf ,uint8_t yf);
public:
    void Zone(char ZoNe,const char* txt);


    Oled(MENU* menu);
    void wifi_connect();
    void wifi_init();
    void Logo();
    void IRcode(String code);
    void MeNu();


    ~Oled();


};

#endif 

