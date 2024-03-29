#ifndef ESPNOW_H_
#define ESPNOW_H_
#include "tools.h"
#include <Arduino.h>
#include <string>
#include <EEPROM.h>

#include <espnow.h>
#include <ESP8266WiFi.h>



/* Definitions for error constants. */
#define ESP_OK          0       /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL        -1      /*!< Generic esp_err_t code indicating failure */

#define ESP_ERR_WIFI_BASE           0x3000  /*!< Starting number of WiFi error codes */
#define ESP_ERR_ESPNOW_BASE         (ESP_ERR_WIFI_BASE + 100) /*!< ESPNOW error number base. */
#define ESP_ERR_ESPNOW_NOT_INIT     (ESP_ERR_ESPNOW_BASE + 1) /*!< ESPNOW is not initialized. */
#define ESP_ERR_ESPNOW_ARG          (ESP_ERR_ESPNOW_BASE + 2) /*!< Invalid argument */
#define ESP_ERR_ESPNOW_NO_MEM       (ESP_ERR_ESPNOW_BASE + 3) /*!< Out of memory */
#define ESP_ERR_ESPNOW_FULL         (ESP_ERR_ESPNOW_BASE + 4) /*!< ESPNOW peer list is full */
#define ESP_ERR_ESPNOW_NOT_FOUND    (ESP_ERR_ESPNOW_BASE + 5) /*!< ESPNOW peer is not found */
#define ESP_ERR_ESPNOW_INTERNAL     (ESP_ERR_ESPNOW_BASE + 6) /*!< Internal error */
#define ESP_ERR_ESPNOW_EXIST        (ESP_ERR_ESPNOW_BASE + 7) /*!< ESPNOW peer has existed */
#define ESP_ERR_ESPNOW_IF           (ESP_ERR_ESPNOW_BASE + 8) /*!< Interface error */

/**
 * @brief Status of sending ESPNOW data .
 */
typedef enum {
    ESP_NOW_SEND_SUCCESS = 0,       /**< Send ESPNOW data successfully */
    ESP_NOW_SEND_FAIL,              /**< Send ESPNOW data fail */
} esp_now_send_status_t;



/**
 * @brief ESPNOW peer information parameters.
 */
typedef struct esp_now_peer_info {
    uint8_t id;
    String SSID ;     //name
    int32_t RSSI;     // wifi Signal Strength Indicato
    String BSSIDstr ; //mac
    uint8_t peer_addr[6];    /**< ESPNOW peer MAC address that is also the MAC address of station or softap */
    uint8_t channel ;      
    uint8_t encrypt[6];           /**< ESPNOW peer local master key that is used to encrypt data */
    uint8_t encrypt_len ;

} esp_now_peer_info_t;
// callback when data is sent from Master to Slave



struct datatype {   //type true => uint8_t 
    bool type; 
    enum EspNow_code  U8;
    char* str;

};

struct info {
    uint8_t  data_len;
    uint8_t id;
    uint8_t* mac;
    String name;
    struct datatype data;
};

typedef struct Devices {
 struct info  Recive;
 struct info  Send;
}Devices;


// Global copy of slave
#define NUMSLAVES 20

#define CHANNEL 1

class EspNow
{
private:
    String SlaveName="NouDa" ;
    Devices device; 
    void manageSlave(uint8_t id) ;
    uint8_t find_id (uint8_t* mac_);
    uint8_t find_id (String name);
    String find_name (uint8_t id);
    uint8_t* find_mac(uint8_t id);
    MENU* menu;
    void updateRecive();
    void updateSend();
    uint8_t TotalPeerNumber=0;
    void writeArrayToEEPROM(int address, uint8_t *data, size_t size) ;
    void readArrayFromEEPROM(int address, uint8_t *data, size_t size) ;
    void writeStringToEEPROM(int address, String value) ;
    String readStringFromEEPROM(int address) ;
    void loadFromMEM();
    bool isExsitPairing(uint8_t * mac);
    void ClearEEPROM();

    uint8_t block_offset[11]={1,24,47,70,93,116,139,162,185,208,231};
    uint8_t id_offset=0;
    uint8_t mac_offset=1;
    uint8_t name_offset=7;







public:
    void SaveMEM(String name,uint8_t* mac);

  int SlaveCnt = 0;
  uint8_t MMAAC[6];
  unsigned long previousTimeSend[20]; // Variable to store the previous time
  unsigned long previousTimeProcess=0;
  unsigned long previousTimeCheck = 0; // Variable to store the previous time

  const unsigned long intervalSend = 1000; 
  uint8_t check_send[20];

  esp_now_peer_info_t slaves[NUMSLAVES] = {};

    EspNow(MENU* menu);
    ~EspNow();
    void process(enum esp_now_Mode mode);
    //void onDataSent(uint8_t *mac_addr, uint8_t sendStatus) ;
    void InitESPNow() ;
    void ScanForSlave() ;

    void sendRequest(uint8_t id) ;
    void listenner() ;


    void sendData(char* data,uint8_t id) ;
    void sendCode(enum EspNow_code data,uint8_t id) ;
    void sendCode(enum EspNow_code  data,String name) ;
    void sendData(char* data,String name) ;

    void send_cb(esp_now_send_cb_t cp);
    void send_cb( uint8_t *mac_addr, uint8_t status);

    void Pairing(void);
    void recv_cb(esp_now_recv_cb_t cp);
    void recv_cb(u8 *mac_addr, u8 *data, u8 len);
    void begin();



    uint8_t PRINTSCANRESULTS = 0;
    String Prefix;


};

#endif 
