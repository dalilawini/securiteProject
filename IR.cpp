#include "IR.h"

IR::IR(MENU* menu_):IRrecv(IR_RecvPin)
{
   this->Menu=menu_;
}

IR::~IR()
{
}


void IR::process()
{
 if (this->decode(&results)) {
    resultHEX=resultToHexidecimal(&results);
    Menu->IR.Data_Reciv=resultHEX;
    this->resume();  // Receive the next value
  }
  
}