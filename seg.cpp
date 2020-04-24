#include "Arduino.h"
#include "Wire.h"
#include "seg.h"
#include "math.h"

// digitCodeMap: List of indexes for segment pins (character pins)
// 0 = a, 1 = b, 2 = c, 3 = d, 4 = e, 5 = f, 6 = d
const int digitCodeMap[10][8] = {
   {0, 1, 2, 3, 4, 5, 0, 0}, // 0
   {1, 2, 1, 1, 1, 1, 1, 1}, // 1
   {0, 1, 3, 4, 6, 0, 0, 0}, // 2
   {0, 1, 2, 3, 6, 0, 0, 0}, // 3
   {1, 2, 5, 6, 1, 1, 1, 1}, // 4
   {0, 2, 3, 5, 6, 0, 0, 0}, // 5
   {0, 2, 3, 4, 5, 6, 0, 0}, // 6
   {0, 1, 2, 0, 0, 0, 0, 0}, // 7
   {0, 1, 2, 3, 4, 5, 6, 0}, // 8
   {0, 1, 2, 3, 5, 6, 0, 0} // 9
}

// Return size of array
template <class T, std::size_t N>
constexpr std::size_t size(const T (&array)[N]) noexcept
{
   return N;
}

// Constructor
seg::seg(int *char_pins, int *mux_pins) {
   // Copy input to private arrays
   for (int i = 0; i < size(char_pins); i++) {
      _char[i] = char_pins[i];
   }
   for (int k = 0; k < size(mux_pins); k++) {
      _mux[k] = mux_pins[k];
   }

   // Declare pins as outputs
   for (int i = 0; i < size(_char); i++) {
      pinMode(_char[i], OUTPUT);
      digitalWrite(_char[i], HIGH);
   }
   for (int i = 0; i < size(_mux); i++) {
      pinMode(_mux[i], OUTPUT);
   }
}

// Clear segment
void seg::clear() {
   for (int i = 0; i < size(_char); i++) {
      digitalWrite(_char[i], HIGH);
   }
}

// Write to segment block
void seg::write(int number) {
   // Find size/last index of mux_pins
   int m = size(_mux) - 1;

   // Loop through *number*
   while (m > -1) {
      // Clear display
      seg::clear();
      // Set MUX pins
      for (int i = m; i >= 0; i--) {
         if (i == m) {
            digitalWrite(_mux[i], HIGH);
         }
         else {
            digitalWrite(_mux[i], LOW);
         }
      }
      /// Print to segment display
      digit = number % 10;
      // Set relevant character pins
      for (int i = 0; i < 8; i++) {
         pin = digitCodeMap[digit][i];
         digitalWrite(_char[pin], LOW);
      }
      ///
      m--;
      number = floor(number / 10);
   }
}


/// I2C Configuration

// Set instance as master
void seg::master(int num_devices) {
   _num_devices = num_devices;

   Wire.begin();
}

// Set instance as slave
void seg::slave(int address) {
   _address = address;

   Wire.begin(_address);
}

// Check if device is connected
bool seg::isConnected() {
   for (uint8_t dev = 1; dev <= _num_devices; dev++) {
      Wire.beginTransmission(dev);
      if (Wire.endTransmission() == 0) {
         return true;
      }
   }
   return false;
}

///
