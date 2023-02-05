#include "Battery.h"
Battery::Battery(Oled * display)
{
    this->display=display;
}
void Battery::Charge()
{
    display->clearDisplay();
    display->drawBitmap(104,0,EmpttyBattery,24,8, 1);
    display->display();
    delay(500);
    display->clearDisplay();
    display->drawBitmap(104,0,LowBattery, 24,8, 1);
    display->display();
    delay(500);
    display->clearDisplay();
    display->drawBitmap(104,0,MediumBattery, 24,8, 1);
    display->display();
    delay(500);
    display->clearDisplay();
    display->drawBitmap(104,0,HighBattery, 24,8, 1);
    display->display();
    delay(500);
    display->clearDisplay();
    display->drawBitmap(104,0,FullBattery, 24,8, 1);
    display->display();
    delay(500);
    

}