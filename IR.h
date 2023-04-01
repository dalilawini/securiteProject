#ifndef IR_H_
#define IR_H_

//----------IR-----------
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "tools.h"


#define IR_RecvPin  14


class IR:public IRrecv
{
private:
  MENU* Menu;
decode_results results;
String resultHEX;
    /* data */
public:
    IR(MENU* menu_);
    ~IR();
   void process();
};



#endif 

