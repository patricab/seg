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
    seg(int digits, int *char_pins, int *mux_pins);
    void write();
    void master();
    void slave();
    bool isConnected();
    static void master();
    static void slave
  private:
    extern const int digitCodeMap[];
    static int size();
    static void clear();
};

#endif
