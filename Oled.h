#ifndef OLED_H_
#define OLED_H_
#endif 


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

  


class Oled:public Adafruit_SSD1306
{
private:
    ESP8266WiFiClass* WiFi;
public:
    Oled();
    void wifi_connect();
    void wifi_init(ESP8266WiFiClass* wifi);
    void Logo();
    void IRcode(String code);


    ~Oled();


};


