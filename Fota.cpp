#include "Fota.h"


Fota::Fota()
{
   
    
}

Fota::~Fota()
{
}

void Fota::begin()
{
 


    this->setTextSize(1);
    this->setCursor(0, 0);
    this->println("FOTA BEGIN");
    this->display();
    delay(500);


}
void Fota::check_for_update()
{
    std::unique_ptr<BearSSL::WiFiClientSecure>client( new BearSSL::WiFiClientSecure);
    client->setInsecure();
    http.begin(*client,HOST_FOR_JSON);
    
     int resp= http.GET();
    if(resp == HTTP_CODE_OK)
    {  
     String payload = http.getString();
     http.end();
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, payload);
      
    if (error) {
    Serial.println("Failed to parse JSON");
     return ;
    }
    FIRMWARE_VERSION = String(doc["firmware_version"]);
    Serial.println(FIRMWARE_VERSION);
    if(FIRMWARE_VERSION=="01.01.10");
     {    http.begin(*client,HOST);

       dowload_packege();   
     }
    }
      else
        Serial.print("HTTP response ERROR");
}

void Fota::dowload_packege()
{   
    this->clearDisplay();
    this->setTextSize(1);
    this->setCursor(0, 0);
    this->println("FIRMWARE UPDATE START");
    this->println("");

    //std::unique_ptr<BearSSL::WiFiClientSecure>client( new BearSSL::WiFiClientSecure);
    //client->setInsecure();

    int resp= http.GET();
    if(resp == HTTP_CODE_OK)
    {   
       
        // get length of document (is -1 when Server sends no Content-Length header)
        FW_Size = http.getSize();
        // this is required to start firmware update process
        lenght =FW_Size;
        this->print("FIRMWARE SIZE:");
        this->println(FW_Size);
        this->display();
        delay(1000);
        // create buffer for read
        uint8_t buff[128] = { 0 };
        // get tcp stream
        WiFiClient * stream = http.getStreamPtr();
          
           
        // read all data from server
        while(http.connected() && (lenght> 0 || lenght== -1)) 
        {  
            progress= (currentLength*100)/FW_Size;
            this->clearDisplay();
            this->setTextSize(1);
            this->setCursor(10, 0);
            this->println("INSTALL PROGRESSE :");
            this->setTextSize(2);
            this->setCursor(50, 13);
            this->print(progress);
            this->print("%");
            this->display();
            
            
           // get available data size
            size_t size = stream->available();
            if(size) 
            {
                // read up to 128 byte
                int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
                // pass to function
                this->updateFirmware(buff, c);
                if(lenght> 0)
                    lenght-= c;
                    
            }
        delay(1);
        }
    }
    else
        {this->print("HTTP response ERROR");this->display();}
http.end();
}

void Fota::updateFirmware(uint8_t *data, size_t len)
{
    Update.begin(FW_Size, U_FLASH);
    Update.write(data, len);
    currentLength += len;
    // if current length of written firmware is not equal to total firmware size, repeat
    if(currentLength != FW_Size) return;
    Update.end(true);
    this->clearDisplay();
    this->setTextSize(1);
    this->setCursor(0, 0);
    this->println("    UPDATE DONE"); 
    this->println("   --ESP-REBOOT--"); 
    this->display();
    ESP.restart();

}
