#include <Arduino.h>
#include <string>

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
    uint8_t peer_addr[6];    /**< ESPNOW peer MAC address that is also the MAC address of station or softap */
    uint8_t channel ;      
    String SSID ;
    int32_t RSSI;
    String BSSIDstr ;
    uint8_t encrypt[6];           /**< ESPNOW peer local master key that is used to encrypt data */
    uint8_t encrypt_len ;
} esp_now_peer_info_t;
// callback when data is sent from Master to Slave



// Global copy of slave
#define NUMSLAVES 20

#define CHANNEL 1

class EspNow
{
private:
    void manageSlave() ;



    /* data */
public:

  int SlaveCnt = 0;

  esp_now_peer_info_t slaves[NUMSLAVES] = {};

    EspNow(/* args */);
    ~EspNow();
    //void onDataSent(uint8_t *mac_addr, uint8_t sendStatus) ;
    void InitESPNow() ;
    void ScanForSlave() ;
    void sendData(uint8_t data) ;
    void send_cb(esp_now_send_cb_t cp);
    void send_cb( uint8_t *mac_addr, uint8_t status);

    void configDeviceAP(void);
    void recv_cb(esp_now_recv_cb_t cp);
    void recv_cb(u8 *mac_addr, u8 *data, u8 len);


    uint8_t PRINTSCANRESULTS = 0;
    String SlaveName ="Slave";




};
