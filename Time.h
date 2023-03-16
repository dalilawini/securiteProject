#pragma once
#ifndef TIME_H_
#define TIME_H_

#include "Arduino.h"
#include <WiFiUdp.h>
#include "Wlan.h"

#define SEVENZYYEARS 2208988800UL
#define NTP_PACKET_SIZE 48
#define NTP_DEFAULT_LOCAL_PORT 1337
#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )

class Time
{
private:
    WiFiUDP*          _udp=new WiFiUDP();
    bool          _udpSetup       = false;

    const char*   _poolServerName = "pool.ntp.org"; // Default time server
    int           _port           = NTP_DEFAULT_LOCAL_PORT;
    int           _timeOffset     = 3600;

    unsigned long _updateInterval = 60000;  // In ms

    unsigned long _currentEpoc    = 0;      // In s
    unsigned long _lastUpdate     = 0;      // In ms

    byte          _packetBuffer[NTP_PACKET_SIZE];

    void          sendNTPPacket();
    bool          isValid(byte * ntpPacket);
 
    int DAY;
    int MONTH;
    int YEAR;
public:
    Time();
    ~Time();
    bool update();
    unsigned long getEpochTime();
    void begin();
    bool forceUpdate();
    void end();
    int getSec();
    int getMin();
    int getHour();
    int getDay();
    int getMon();
    int getYear();
    String getFormattedTime(unsigned long secs=0) ;
    String getFormattedDate(unsigned long secs=0) ;
    //void TimeDisplay();

};

#endif 
