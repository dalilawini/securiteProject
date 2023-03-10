#include "EspNow.h"

EspNow::EspNow(MENU* menu)
{
  this->menu=menu;
}

EspNow::~EspNow()
{
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


void EspNow::configDeviceAP(void) {
   //Set device in AP mode to begin with
  WiFi.mode(WIFI_AP);
  // configure device AP mode
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  // Init ESPNow with a fallback logic
  String Prefix = "Slave:";
  String Mac = WiFi.macAddress();
  String SSID = Prefix + Mac;
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}



// Scan for slaves in AP mode
void EspNow::ScanForSlave() {
  //Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);
  Serial.println("ESPNow 1 Master /Multi-Slave"); 
  // This is the mac address of the Master in Station Mode
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());

  int8_t scanResults = WiFi.scanNetworks();
  //reset slaves
  memset(slaves, 0, sizeof(slaves));
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
                slaves[SlaveCnt].id=SlaveCnt;
                slaves[SlaveCnt].SSID = WiFi.SSID(i);
                slaves[SlaveCnt].RSSI = WiFi.RSSI(i);
                slaves[SlaveCnt].BSSIDstr = WiFi.BSSIDstr(i);
                slaves[SlaveCnt].channel=1;
                // Get BSSID => Mac Address of the Slave
                int mac[6];

                if ( 6 == sscanf(slaves[SlaveCnt].BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) 
                {                          

                    for (int j = 0; j < 6; ++j ) 
                    {
                        slaves[SlaveCnt].peer_addr[j] = (uint8_t) mac[j];
                    }
                }
                slaves[SlaveCnt].channel = CHANNEL; // pick a channel
                slaves[SlaveCnt].encrypt[0] = 0; // no encryption
                SlaveCnt++;

            }
        }
        Serial.println("");
        if(SlaveCnt>0)
        {
          Serial.println("Target found ");
          for(int i=0;i<SlaveCnt;i++)
            {Serial.print(i+1); Serial.print(": "); Serial.print(slaves[i].SSID); Serial.print(" ["); Serial.print(slaves[i].BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(slaves[i].RSSI); Serial.println(")");}
            Serial.println("");
        }
        else 
        Serial.println("No Slave Found, trying again.");
  
    }

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
        Serial.print((uint8_t) slaves[i].peer_addr[ii], HEX);
        if (ii != 5) Serial.print(":");
      }
      Serial.print(" Status: ");
      // check if the peer exists
      bool exists = esp_now_is_peer_exist(slaves[i].peer_addr);
      if (exists) 
        // Slave already paired.
        Serial.println("Already Paired");
      else 
        // Slave not paired, attempt pair
       {
         esp_now_add_peer(slaves[i].peer_addr, ESP_NOW_ROLE_SLAVE, slaves[i].channel, slaves[i].encrypt, slaves[i].encrypt_len);
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
  device.Send.data.str= data;
  device.Send.data_len= strlen(data);
  device.Send.id= id;
  device.Send.name= this->find_name(id);
  device.Send.mac=this->find_mac(id);

  esp_now_send( device.Send.mac,(u8*)device.Send.data.str,device.Send.data_len);
}

void EspNow::sendData(uint8_t* data,uint8_t id) 
{
  device.Send.data.type= true;
  device.Send.data.U8= data;
  device.Send.data_len= sizeof(data);
  device.Send.id= id;
  device.Send.name= this->find_name(id);
  device.Send.mac=this->find_mac(id);
        
  esp_now_send( device.Send.mac,device.Send.data.U8,device.Send.data_len);
}

void EspNow::sendData(char* data,String name) 
{
  device.Send.data.type= false;
  device.Send.data.str= data;
  device.Send.data_len= strlen(data);
  device.Send.id= this->find_id(name);
  device.Send.name= name;
  device.Send.mac=this->find_mac(device.Send.id);
        
  esp_now_send( device.Send.mac,(u8*)device.Send.data.str,device.Send.data_len);
}

void EspNow::sendData(uint8_t* data,String name) 
{
  device.Send.data.type= true;
  device.Send.data.U8= data;
  device.Send.data_len= sizeof(data);
  device.Send.id= this->find_id(name);
  device.Send.name= name;
  device.Send.mac=this->find_mac(device.Send.id);
        
  esp_now_send( device.Send.mac,device.Send.data.U8,device.Send.data_len);
}

//-------------------------Send CallBack------------------------
void EspNow::send_cb(esp_now_send_cb_t cp) {
   esp_now_register_send_cb(cp);
}

void EspNow::send_cb( uint8_t *mac_addr, uint8_t status){

  uint8_t id =this->find_id(mac_addr);
  menu->ESP_NOW.P_Device[id].status=status;
  Serial.print("Last Packet Send from id: "); Serial.println( id);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  //----------------for SENDED data----------------
  updateSend();

}

//-------------------------Recived CallBack------------------------
void EspNow::recv_cb(esp_now_recv_cb_t cp) {
  esp_now_register_recv_cb(cp);
}

void EspNow::recv_cb(uint8_t *mac_addr, uint8_t *data, uint8_t data_len){
 
  device.Recive.data.type= false;
  device.Recive.data.str=(char*)data;
  device.Recive.data_len= data_len;
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
      if(slaves[j].peer_addr[i]==mac[i])
        check_id++;
    }
    
    if(check_id==6)
    return j;
  }
  return -1;
}

uint8_t EspNow::find_id (String name){
  for(int j=0;j<SlaveCnt;j++)
  {
    if(slaves[j].SSID==name)
     return  slaves[j].id;
      
  }
  return -1;
}

String EspNow::find_name (uint8_t id){
    return slaves[id].SSID; 
}

uint8_t* EspNow::find_mac(uint8_t id){
  return slaves[id].peer_addr; 

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
      memcpy( menu->ESP_NOW.P_Device[device.Send.id].Send.str, device.Send.data.str, device.Send.data_len); 
      memset(menu->ESP_NOW.P_Device[device.Send.id].Send.U8,0,device.Send.data_len);
    } 
    else
    {
      memcpy( menu->ESP_NOW.P_Device[device.Send.id].Send.U8, device.Send.data.U8, device.Send.data_len);
      memset( menu->ESP_NOW.P_Device[device.Send.id].Send.str,0,device.Send.data_len);
    }  
  menu->ESP_NOW.P_Device[device.Send.id].Send.len= device.Send.data_len;

}

void EspNow::updateRecive()
{
//----------------for RECIVED data----------------
  //----------------for both--------------------------
  menu->ESP_NOW.P_Device[device.Recive.id].Name= device.Recive.name;
  memcpy(menu->ESP_NOW.P_Device[device.Recive.id].MacAddres, device.Recive.mac, 6);
  menu->ESP_NOW.P_Device[device.Recive.id].Recive.len= device.Recive.data_len;

 if(device.Recive.data.type==false)
    {
      memcpy( menu->ESP_NOW.P_Device[device.Recive.id].Recive.str, device.Recive.data.str, device.Recive.data_len); 
      memset(menu->ESP_NOW.P_Device[device.Recive.id].Recive.U8,0,device.Recive.data_len);
    } 
    else
    {
      memcpy( menu->ESP_NOW.P_Device[device.Recive.id].Recive.U8, device.Recive.data.U8, device.Recive.data_len);
      memset( menu->ESP_NOW.P_Device[device.Recive.id].Send.str,0,device.Recive.data_len);
    }  

}
