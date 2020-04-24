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
      // Methods
      seg(int *char_pins, int *mux_pins);
      void write(int number);
      static bool isConnected();
      static void master();
      static void slave(int address, int num_devices);

   private:
      // Variables/arrays
      // extern const int digitCodeMap[];
      extern int _num_devices;
      extern int _address;
      extern int _char[8];
      extern int _mux[5];
      int digit;
      int pin;

      // Methods
      static void clear();
      static int size(int *arr);
};
#endif
