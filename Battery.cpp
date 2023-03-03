#include "Battery.h"
Battery::Battery()
{
}
void Battery::Charge()
{
   this->clearDisplay();
   this->drawBitmap(104,0,EmpttyBattery,24,8, 1);
   this->display();
    delay(500);
   this->clearDisplay();
   this->drawBitmap(104,0,LowBattery, 24,8, 1);
   this->display();
    delay(500);
   this->clearDisplay();
   this->drawBitmap(104,0,MediumBattery, 24,8, 1);
   this->display();
    delay(500);
   this->clearDisplay();
   this->drawBitmap(104,0,HighBattery, 24,8, 1);
   this->display();
    delay(500);
   this->clearDisplay();
   this->drawBitmap(104,0,FullBattery, 24,8, 1);
   this->display();
    delay(500);
    

}
