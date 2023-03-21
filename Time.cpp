#include "Time.h"

Time::Time()
{
    //this->display=display;
}

Time::~Time()
{
}


int Time::getSec() 
{
  return (this->getEpochTime() % 60);


}

int Time::getMin() 
{
   return ((this->getEpochTime() % 3600) / 60);

}

int Time::getHour() 
{
  return ((this->getEpochTime()  % 86400L) / 3600);

}

int Time::getDay() 
{
    return this->DAY;
}

int Time::getMon() 
{
    return this->MONTH;
}

int Time::getYear() 
{
    return this->YEAR;
}

String Time::getFormattedTime(unsigned long secs) {
  unsigned long rawTime = secs ? secs : this->getEpochTime();
  unsigned long hours = (rawTime % 86400L) / 3600;
  String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

  unsigned long minutes = (rawTime % 3600) / 60;
  String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

  unsigned long seconds = rawTime % 60;
  String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

  return hoursStr + ":" + minuteStr + ":" + secondStr;
}

// Based on https://github.com/PaulStoffregen/Time/blob/master/Time.cpp
// currently assumes UTC timezone, instead of using this->_timeOffset
String Time::getFormattedDate(unsigned long secs) {
  unsigned long rawTime = (secs ? secs : this->getEpochTime()) / 86400L;  // in days
  unsigned long days = 0, year = 1970;
  uint8_t month;
  static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};

  while((days += (LEAP_YEAR(year) ? 366 : 365)) <= rawTime)
    year++;
  rawTime -= days - (LEAP_YEAR(year) ? 366 : 365); // now it is days in this year, starting at 0
  days=0;
  for (month=0; month<12; month++) {
    uint8_t monthLength;
    if (month==1) { // february
      monthLength = LEAP_YEAR(year) ? 29 : 28;
    } else {
      monthLength = monthDays[month];
    }
    if (rawTime < monthLength) break;
    rawTime -= monthLength;
  }
  String monthStr = ++month < 10 ? "0" + String(month) : String(month); // jan is month 1  
  String dayStr = ++rawTime < 10 ? "0" + String(rawTime) : String(rawTime); // day of month 
  this->DAY= rawTime;
  this->MONTH=month;
  this->YEAR=year;
  return String(year) + "-" + monthStr + "-" + dayStr;
}

void Time::begin() 
{
  this->_udp->begin(this->_port);
  this->_udpSetup = true;
}

bool Time::update() 
{   
    if ((millis() - this->_lastUpdate >= this->_updateInterval)|| this->_lastUpdate == 0) 
    {     
        if (!this->_udpSetup) this->begin();                         // setup the UDP client if needed
        return this->forceUpdate();
    }
    return true;
}

bool Time::forceUpdate() {
  #ifdef DEBUG_NTPClient
    Serial.println("Update from NTP Server");
  #endif

  this->sendNTPPacket();

  // Wait till data is there or timeout...
  byte timeout = 0;
  int cb = 0;
  do {
    delay ( 10 );
    cb = this->_udp->parsePacket();
    
    if(cb > 0)
    {
      this->_udp->read(this->_packetBuffer, NTP_PACKET_SIZE);
      if(!this->isValid(this->_packetBuffer))
        cb = 0;
    }
    
    if (timeout > 100) return false; // timeout after 1000 ms
    timeout++;
  } while (cb == 0);

  this->_lastUpdate = millis() - (10 * (timeout + 1)); // Account for delay in reading the time

  unsigned long highWord = word(this->_packetBuffer[40], this->_packetBuffer[41]);
  unsigned long lowWord = word(this->_packetBuffer[42], this->_packetBuffer[43]);
  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;

  this->_currentEpoc = secsSince1900 - SEVENZYYEARS;

  return true;
}

unsigned long Time::getEpochTime() {
  return this->_timeOffset + // User offset
         this->_currentEpoc + // Epoc returned by the NTP server
         ((millis() - this->_lastUpdate) / 1000); // Time since last update
}


void Time::sendNTPPacket() {
  // set all bytes in the buffer to 0
  memset(this->_packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  this->_packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  this->_packetBuffer[1] = 0;     // Stratum, or type of clock
  this->_packetBuffer[2] = 6;     // Polling Interval
  this->_packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  this->_packetBuffer[12]  = 0x49;
  this->_packetBuffer[13]  = 0x4E;
  this->_packetBuffer[14]  = 0x49;
  this->_packetBuffer[15]  = 0x52;

  // all NTP fields have been given values, now. version: sanusb.org
  // you can send a packet requesting a timestamp:
  this->_udp->beginPacket(this->_poolServerName, 123); //NTP requests are to port 123
  this->_udp->write(this->_packetBuffer, NTP_PACKET_SIZE);
  this->_udp->endPacket();
}

bool Time::isValid(byte * ntpPacket)
{
	//Perform a few validity checks on the packet
	if((ntpPacket[0] & 0b11000000) == 0b11000000)		//Check for LI=UNSYNC
		return false;
		
	if((ntpPacket[0] & 0b00111000) >> 3 < 0b100)		//Check for Version >= 4
		return false;
		
	if((ntpPacket[0] & 0b00000111) != 0b100)			//Check for Mode == Server
		return false;
		
	if((ntpPacket[1] < 1) || (ntpPacket[1] > 15))		//Check for valid Stratum
		return false;

	if(	ntpPacket[16] == 0 && ntpPacket[17] == 0 && 
		ntpPacket[18] == 0 && ntpPacket[19] == 0 &&
		ntpPacket[20] == 0 && ntpPacket[21] == 0 &&
		ntpPacket[22] == 0 && ntpPacket[22] == 0)		//Check for ReferenceTimestamp != 0
		return false;

	return true;
}
/*
void Time::TimeDisplay(){
this->update();
this->clearDisplay();
this->setTextSize(2);
this->setCursor(0,0);
this->println(this->getFormattedTime());
this->setTextSize(1);
this->print("Date:");
this->print(this->getFormattedDate());
this->display();

}
*/
void Time::end() {
  this->_udp->stop();

  this->_udpSetup = false;
}

