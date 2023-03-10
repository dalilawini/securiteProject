#include "EspNow.h"

EspNow::EspNow(MENU* menu)
{
  this->menu=menu;
}

EspNow::~EspNow()
{
}

void EspNow::actionRequest(uint8_t id ) {
  
  if(menu->ESP_NOW.AvaibleDevices[id].status!=paired)
    {
      menu->ESP_NOW.AvaibleDevices[id].status=ready;
      check_send[id]=0;
    }
}

void EspNow::sendRequest(uint8_t id ) {
    enum EspNow_code send;

   if(menu->ESP_NOW.AvaibleDevices[id].status==ready)
   {

    if(millis() - previousTimeSend[id] > intervalSend) 
      {
        send=pairingRequest;
        esp_now_send( menu->ESP_NOW.AvaibleDevices[id].MacAddres,(u8*)&send,1);
        previousTimeSend[id]=millis();
        check_send[id]++;
      }
    
      if(menu->ESP_NOW.AvaibleDevices[id].Data_U8==pairingOK)
      {
        menu->ESP_NOW.AvaibleDevices[id].status=paired;
        send=pairingIDL;
        esp_now_send( menu->ESP_NOW.AvaibleDevices[id].MacAddres,(u8*)&send,1);
        check_send[id]=0;
      }
       if(menu->ESP_NOW.AvaibleDevices[id].Data_U8==pairingRefused)
      {
        menu->ESP_NOW.AvaibleDevices[id].status=refused;
        send=pairingIDL;
       esp_now_send( menu->ESP_NOW.AvaibleDevices[id].MacAddres,(u8*)&send,1);
        check_send[id]=0;
      }
      if(check_send[id] >10)
         {
          menu->ESP_NOW.AvaibleDevices[id].status=failed;
          check_send[id]=0;
         }

    }
}

void EspNow::listenner() {
  enum EspNow_code send;
  if(menu->ESP_NOW.PairingMode.PairData==pairingRequest && menu->ESP_NOW.PairingMode.status_paired==paired)
  {  
     send=pairingOK;
     esp_now_send( menu->ESP_NOW.PairingMode.PairMac,(u8*)&send,1);

  }
   if(menu->ESP_NOW.PairingMode.PairData==pairingRequest && menu->ESP_NOW.PairingMode.status_paired==refused)
  {  
     send=pairingRefused;
     esp_now_send( menu->ESP_NOW.PairingMode.PairMac,(u8*)&send,1);

  }
  

}

void EspNow::Pairing(void) {
  // configure device AP mode
  WiFi.mode(WIFI_AP);  
  String SSID = SlaveName + Prefix;
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL, 0);
  menu->ESP_NOW.PairingMode.DeviceName=SSID;
  menu->ESP_NOW.PairingMode.DeviceMac=WiFi.macAddress();

  
  if (!result) {
    Serial.println("AP Config failed.");
       // menu->ESP_NOW.PairingMode.status_paired=failed;
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
   // menu->ESP_NOW.PairingMode.status_paired=ready;
  }

}


// Init ESP Now with callback
void EspNow::InitESPNow(void) {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    this->manageSlave();


  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();
  }
}








// Scan for slaves in AP mode
void EspNow::ScanForSlave() {
  //Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);
  int8_t scanResults = WiFi.scanNetworks();
  //reset slaves
  memset(menu->ESP_NOW.AvaibleDevices, 0, sizeof(menu->ESP_NOW.AvaibleDevices));
  SlaveCnt = 0;
  Serial.println("");

  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
  } 
  else 
    {
        Serial.print("Found : "); Serial.print(scanResults); Serial.println(" devices ");
        for (int i = 0; i < scanResults; ++i) 
        {
            if (PRINTSCANRESULTS) 
            {
                Serial.print(i + 1); Serial.print(": "); Serial.print(WiFi.SSID(i)); Serial.print(" ["); Serial.print(WiFi.BSSIDstr(i)); Serial.print("]"); Serial.print(" ("); Serial.print(WiFi.RSSI(i)); Serial.print(")"); Serial.println("");
            }
            delay(10);
            // Check if the current device starts with Slave
            if(WiFi.SSID(i).indexOf(SlaveName)== 0)
            {
                // Print SSID and RSSI for each device found
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].id=SlaveCnt;
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].Name= WiFi.SSID(i);
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].RSSI = WiFi.RSSI(i);
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].BSSIDstr = WiFi.BSSIDstr(i);
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].channel=1;
                // Get BSSID => Mac Address of the Slave
                int mac[6];

                if ( 6 == sscanf(menu->ESP_NOW.AvaibleDevices[SlaveCnt].BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) 
                {                          

                    for (int j = 0; j < 6; ++j ) 
                    {
                        menu->ESP_NOW.AvaibleDevices[SlaveCnt].MacAddres[j] = (uint8_t) mac[j];
                    }
                }
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].channel = CHANNEL; // pick a channel
                menu->ESP_NOW.AvaibleDevices[SlaveCnt].encrypt[0] = 0; // no encryption
                SlaveCnt++;

            }
        }
        Serial.println("");
        if(SlaveCnt>0)
        {
          Serial.println("Target found ");
          for(int i=0;i<SlaveCnt;i++)
            {Serial.print(i+1); Serial.print(": "); Serial.print(menu->ESP_NOW.AvaibleDevices[i].Name); Serial.print(" ["); Serial.print(menu->ESP_NOW.AvaibleDevices[i].BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(menu->ESP_NOW.AvaibleDevices[i].RSSI); Serial.println(")");}
            Serial.println("");
        }
        else 
        Serial.println("No Slave Found, trying again.");
  
    }
  menu->ESP_NOW.NumberOfAvaibleDevices=SlaveCnt;
  WiFi.scanDelete();
}


// Check if the slave is already paired with the master.
// If not, pair the slave with master
void EspNow::manageSlave() 
{
  if (SlaveCnt > 0) 
  {
    for (int i = 0; i < SlaveCnt; i++) 
    {
      Serial.print("Processing: ");
      for (int ii = 0; ii < 6; ++ii )
      {
        Serial.print((uint8_t) menu->ESP_NOW.AvaibleDevices[i].MacAddres[ii], HEX);
        if (ii != 5) Serial.print(":");
      }
      Serial.print(" Status: ");
      // check if the peer exists
      bool exists = esp_now_is_peer_exist(menu->ESP_NOW.AvaibleDevices[i].MacAddres);
      if (exists) 
        // Slave already paired.
        Serial.println("Already Paired");
      else 
        // Slave not paired, attempt pair
       {
         esp_now_add_peer(menu->ESP_NOW.AvaibleDevices[i].MacAddres, ESP_NOW_ROLE_SLAVE, menu->ESP_NOW.AvaibleDevices[i].channel, menu->ESP_NOW.AvaibleDevices[i].encrypt, menu->ESP_NOW.AvaibleDevices[i].encrypt_len);
          Serial.println("Paired Successfully");
       }
    }
  }
  else 
    // No slave found to process
    Serial.println("No Slave found to process");
  
}

//------------------------Function for send data -------------------
void EspNow::sendData(char* data,uint8_t id) 
{ 
  device.Send.data.type= false;
  device.Send.data_len= strlen(data);
  device.Send.data.str=data;
  device.Send.id= id;
  device.Send.name= this->find_name(id);
  device.Send.mac=this->find_mac(id);

  updateSend();

  esp_now_send( device.Send.mac,(u8*)menu->ESP_NOW.P_Device[device.Send.id].Data.Send.str,device.Send.data_len+1);
  menu->ESP_NOW.P_Device[device.Send.id].Data.Send.str[device.Send.data_len]=0;
}

void EspNow::sendCode(enum EspNow_code  data,uint8_t id) 
{
  device.Send.data.type= true;
  device.Send.data.U8= data;
  device.Send.id= id;
  device.Send.name= this->find_name(id);
  device.Send.mac=this->find_mac(id);
  
  updateSend();

  esp_now_send( device.Send.mac,(u8*)&menu->ESP_NOW.P_Device[device.Send.id].Data.Send.U8,1);
}

void EspNow::sendData(char* data,String name) 
{
   sendData(data,this->find_id(name));
}

void EspNow::sendCode(enum EspNow_code  data,String name) 
{
  sendCode(data,this->find_id(name)) ;
}

//-------------------------Send CallBack------------------------
void EspNow::send_cb(esp_now_send_cb_t cp) {
   esp_now_register_send_cb(cp);
}

void EspNow::send_cb( uint8_t *mac_addr, uint8_t status){

  uint8_t id =this->find_id(mac_addr);
  menu->ESP_NOW.P_Device[id].Info.status=status;
  Serial.print("Last Packet Send from id: "); Serial.println( id);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  //----------------for SENDED data----------------

}

//-------------------------Recived CallBack------------------------
void EspNow::recv_cb(esp_now_recv_cb_t cp) {
  esp_now_register_recv_cb(cp);
}

void EspNow::recv_cb(uint8_t *mac_addr, uint8_t *data, uint8_t data_len){
 
  if(data[data_len-1]==0xff)
  {
    device.Recive.data.type= false;
    device.Recive.data.str=(char*)data;
    device.Recive.data_len= data_len-1;
    Serial.println("string cb");

  }
  else 
  {
    device.Recive.data.type= true;
    device.Recive.data.U8=(enum EspNow_code)data[0];
    device.Recive.data_len= data_len;
    Serial.println("code cb");

  }

  device.Recive.id=this->find_id(mac_addr);
  device.Recive.name=this->find_name(device.Recive.id);
  device.Recive.mac=mac_addr;
  updateRecive();
}

//------------------------Method of search-----------------------------------
uint8_t EspNow::find_id (uint8_t* mac){
  uint8_t check_id=0;
  for(int j=0;j<SlaveCnt;j++)
  {
    for(int i=0 ;i<6;i++)
    { 
      if(menu->ESP_NOW.AvaibleDevices[j].MacAddres[i]==mac[i])
        check_id++;
    }
    
    if(check_id==6)
    return j;
  }
  return 0xff;
}

uint8_t EspNow::find_id (String name){
  for(int j=0;j<SlaveCnt;j++)
  {
    if(menu->ESP_NOW.AvaibleDevices[j].Name==name)
     return  menu->ESP_NOW.AvaibleDevices[j].id;
      
  }
  return -1;
}

String EspNow::find_name (uint8_t id){
    return menu->ESP_NOW.AvaibleDevices[id].Name; 
}

uint8_t* EspNow::find_mac(uint8_t id){
  return menu->ESP_NOW.AvaibleDevices[id].MacAddres; 

}

//-----------------------------------------------------------------------------
void EspNow::LoadPairedDesvices()
{

}

void EspNow::LoadAvaibleDesvices()
{

}


void EspNow::updateSend()
{
  if(device.Send.data.type==false)
    {
      memcpy( menu->ESP_NOW.P_Device[device.Send.id].Data.Send.str, device.Send.data.str, device.Send.data_len);
      menu->ESP_NOW.P_Device[device.Send.id].Data.Send.str[device.Send.data_len]=0xff;
      menu->ESP_NOW.P_Device[device.Send.id].Data.Send.len= device.Send.data_len;
      menu->ESP_NOW.P_Device[device.Send.id].Data.Send.U8=empty;

    } 
    else
    {
       menu->ESP_NOW.P_Device[device.Send.id].Data.Send.U8=device.Send.data.U8;
      memset( menu->ESP_NOW.P_Device[device.Send.id].Data.Send.str,0,20);
    }  

}

void EspNow::updateRecive()
{
//----------------for RECIVED data----------------
  //----------------for both--------------------------
  menu->ESP_NOW.P_Device[device.Recive.id].Info.Name = device.Recive.name;
  memcpy(menu->ESP_NOW.P_Device[device.Recive.id].Info.MacAddres, device.Recive.mac, 6);
  memcpy(menu->ESP_NOW.PairingMode.PairMac, device.Recive.mac, 6);


 if(device.Recive.data.type==false)
    {
      memcpy( menu->ESP_NOW.P_Device[device.Recive.id].Data.Recive.str, device.Recive.data.str, device.Recive.data_len); 
      menu->ESP_NOW.P_Device[device.Recive.id].Data.Recive.len= device.Recive.data_len;
      menu->ESP_NOW.P_Device[device.Recive.id].Data.Recive.U8=empty;


    } 
    else
    {
      menu->ESP_NOW.P_Device[device.Recive.id].Data.Recive.U8=device.Recive.data.U8;
      menu->ESP_NOW.AvaibleDevices[device.Recive.id].Data_U8=device.Recive.data.U8;
      menu->ESP_NOW.PairingMode.PairData=device.Recive.data.U8;
      memset( menu->ESP_NOW.P_Device[device.Recive.id].Data.Recive.str,0,device.Recive.data_len);

    }  

}
