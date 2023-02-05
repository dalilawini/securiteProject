#include "Fota.h"


Fota::Fota(Oled* display)
{
   
    this->display=display;
}

Fota::~Fota()
{
}

void Fota::begin()
{
 


    display->setTextSize(1);
    display->setCursor(0, 0);
    display->println("FOTA BEGIN");
    display->display();
    delay(500);


}

void Fota::dowload_packege()
{   
    display->clearDisplay();
    display->setTextSize(1);
    display->setCursor(0, 0);
    display->println("FIRMWARE UPDATE START");
    display->println("");

    std::unique_ptr<BearSSL::WiFiClientSecure>client( new BearSSL::WiFiClientSecure);
    client->setInsecure();
    http.begin(*client,HOST);

    int resp= http.GET();
    if(resp == HTTP_CODE_OK)
    {   
       
        // get length of document (is -1 when Server sends no Content-Length header)
        FW_Size = http.getSize();
        // this is required to start firmware update process
        lenght =FW_Size;
        display->print("FIRMWARE SIZE:");
        display->println(FW_Size);
        display->display();
        delay(1000);
        // create buffer for read
        uint8_t buff[128] = { 0 };
        // get tcp stream
        WiFiClient * stream = http.getStreamPtr();
          
           
        // read all data from server
        while(http.connected() && (lenght> 0 || lenght== -1)) 
        {  
            progress= (currentLength*100)/FW_Size;
            display->clearDisplay();
            display->setTextSize(1);
            display->setCursor(10, 0);
            display->println("INSTALL PROGRESSE :");
            display->setTextSize(2);
            display->setCursor(50, 13);
            display->print(progress);
            display->print("%");
            display->display();
            
            
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
        {display->print("HTTP response ERROR");display->display();}
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
    display->clearDisplay();
    display->setTextSize(1);
    display->setCursor(0, 0);
    display->println("    UPDATE DONE"); 
    display->println("   --ESP-REBOOT--"); 
    display->display();
    ESP.restart();

}