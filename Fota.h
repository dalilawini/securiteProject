#ifndef FOTA_H_
#define FOTA_H_

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

#include <ArduinoOTA.h>
#include <Arduino.h>
#include "Battery.h"

#define HOST_FOR_JSON "https://actiaserver.000webhostapp.com/dali.json"
#define HOST "https://actiaserver.000webhostapp.com/securiteProject.ino.bin"


// location of firmware file on external web server
// change to your actual .bin location



 //current size of written firmware


class Fota:Oled
{
private:
  int currentLength = 0;
  int lenght=0;
  void updateFirmware(uint8_t *data, size_t len);
  unsigned int progress;

public:
HTTPClient http;

  Fota();
  ~Fota();
  void begin();
  void dowload_packege();
  void check_for_update();
  int FW_Size;       //total size of firmware
  String FIRMWARE_VERSION;
};

#endif 

