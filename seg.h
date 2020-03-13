/*
  seg.h - Library for 7 segment displays
  Patric A.B (s0phie)
*/

#ifndef seg
#define seg

#include "Arduino.h"

class seg
{
  public:
    seg(int pin);
    void dot();
    void dash();
 private:
    int _pin;
};

#endif
