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
    seg(int rows, int columns, int *top_pins, int *bottom_pins, int *mux_pins)
    void write();
 private:
    int _pin;
};

#endif
