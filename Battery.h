#ifndef BATTERY_H_
#define BATTERY_H_

#include "Oled.h"

class Battery:Oled
{
private:
uint8_t FullBattery[24]=
 {
 0b00111111,0b11111111,0b11111111,0b11100000,0b00000000,0b00000001,0b10011110,0b11110111,0b10111101,0b10011110,0b11110111,0b10111101,
 0b10011110,0b11110111,0b10111101,0b10011110,0b11110111,0b10111101,0b11100000,0b00000000,0b00000001,0b00111111,0b11111111,0b11111111
 };
 
uint8_t HighBattery[24]=
 {
 0b00111111,0b11111111,0b11111111,0b11100000,0b00000000,0b00000001,0b10000000,0b11110111,0b10111101,0b10000000,0b11110111,0b10111101,
 0b10000000,0b11110111,0b10111101,0b10000000,0b11110111,0b10111101,0b11100000,0b00000000,0b00000001,0b00111111,0b11111111,0b11111111
};

uint8_t MediumBattery[24]=
 {
 0b00111111,0b11111111,0b11111111,0b11100000,0b00000000,0b00000001,0b10000000,0b00000111,0b10111101,0b10000000,0b00000111,0b10111101,
 0b10000000,0b00000111,0b10111101,0b10000000,0b00000111,0b10111101,0b11100000,0b00000000,0b00000001,0b00111111,0b11111111,0b11111111
};

uint8_t LowBattery[24]=
 {
  0b00111111,0b11111111,0b11111111,0b11100000,0b00000000,0b00000001,0b10000000,0b00000000,0b00111101,0b10000000,0b00000000,0b00111101,
 0b10000000,0b00000000,0b00111101,0b10000000,0b00000000,0b00111101,0b11100000,0b00000000,0b00000001,0b00111111,0b11111111,0b11111111
};
uint8_t EmpttyBattery[24]=
 {
 0b00111111,0b11111111,0b11111111,0b11100000,0b00000000,0b00000001,0b10000000,0b00000000,0b00000001,0b10000000,0b00000000,0b00000001,
 0b10000000,0b00000000,0b00000001,0b10000000,0b00000000,0b00000001,0b11100000,0b00000000,0b00000001,0b00111111,0b11111111,0b11111111
};

    /* data */
public:
    Battery();
    void Charge();
    ~Battery();
};

#endif 


