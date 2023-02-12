#include "EspNow.h"

EspNow::EspNow(/* args */)
{
}

EspNow::~EspNow()
{
}



// Init ESP Now with callback
void EspNow::InitESPNow() {
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
  Serial.println("ESPNow/Multi-Slave/Master Example"); 
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
                slaves[SlaveCnt].SSID = WiFi.SSID(i);
                slaves[SlaveCnt].RSSI = WiFi.RSSI(i);
                slaves[SlaveCnt].BSSIDstr = WiFi.BSSIDstr(i);
                slaves[SlaveCnt].channel=1;

                // SSID of interest
                Serial.print(SlaveCnt + 1); Serial.print(": "); Serial.print(slaves[SlaveCnt].SSID); Serial.print(" ["); Serial.print(slaves[SlaveCnt].BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(slaves[SlaveCnt].RSSI); Serial.print(")"); Serial.println("");
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
    }

  if (SlaveCnt > 0) 
  {
    Serial.print(SlaveCnt); Serial.println(" Slave(s) found, processing..");
  } else 
  {
    Serial.println("No Slave Found, trying again.");
  }

  // clean up ram
  WiFi.scanDelete();
}


// Check if the slave is already paired with the master.
// If not, pair the slave with master
void EspNow::manageSlave() {
  if (SlaveCnt > 0) {
    for (int i = 0; i < SlaveCnt; i++) {
      Serial.print("Processing: ");
      for (int ii = 0; ii < 6; ++ii ) {
        Serial.print((uint8_t) slaves[i].peer_addr[ii], HEX);
        if (ii != 5) Serial.print(":");
      }
      Serial.print(" Status: ");
      // check if the peer exists
      bool exists = esp_now_is_peer_exist(slaves[i].peer_addr);
      if (exists) {
        // Slave already paired.
        Serial.println("Already Paired");
      } else {
        // Slave not paired, attempt pair
        int addStatus = esp_now_add_peer(slaves[i].peer_addr, ESP_NOW_ROLE_SLAVE, slaves[i].channel, slaves[i].encrypt, slaves[i].encrypt_len);
        if (addStatus == ESP_OK) {
          // Pair success
          Serial.println("Pair success");
        } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
          // How did we get so far!!
          Serial.println("ESPNOW Not Init");
        } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
          Serial.println("Add Peer - Invalid Argument");
        } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
          Serial.println("Peer list full");
        } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
          Serial.println("Out of memory");
        } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
          Serial.println("Peer Exists");
        } else {
          Serial.println("Not sure what happened");
          Serial.println(addStatus);
        }
        delay(100);
      }
    }
  } else {
    // No slave found to process
    Serial.println("No Slave found to process");
  }
}

// send data
void EspNow::sendData(uint8_t data) 
{

  for (int i = 0; i < SlaveCnt; i++)
   {
        if (i == 0) 
        { // print only for first slave
            Serial.print("Sending: ");
            Serial.println(data);
        }
        int  result = esp_now_send(slaves[i].peer_addr, &data, sizeof(data));
        Serial.print("Send Status: ");
        if (result == ESP_OK) 
        {
        Serial.println("Success");
        } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
            // How did we get so far!!
            Serial.println("ESPNOW not Init.");
        } else if (result == ESP_ERR_ESPNOW_ARG) {
            Serial.println("Invalid Argument");
        } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
            Serial.println("Internal Error");
        } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
            Serial.println("ESP_ERR_ESPNOW_NO_MEM");
        } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
            Serial.println("Peer not found.");
        } else {
            Serial.println("Not sure what happened");
        }
    delay(100);
  }
}

