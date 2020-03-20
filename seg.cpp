/* Pinout:
+5v: 3, 8 (10, 11)
a: 7 (8)
b: 6 (9)
c: 4 (4)
d: 2 (3)
e: 1 (2)
f: 9 (7)
g: 10 (6)
dp: 5 (5)

10 9 8 7 6
 5 4 3 2 1
*/

#include "seg.h"
#include "Wire.h"
#include "Arduino.h"

// digitCodeMap: List of indexes for segment pins (character pins)
// 0 = a, 1 = b, 2 = c, 3 = d, 4 = e, 5 = f, 6 = d
extern const int digitCodeMap[] {
  {0, 1, 2, 3, 4, 5}, // 0
  {1, 2}, // 1
  {0, 1, 3, 4, 6}, // 2
  {0, 1, 2, 3, 6}, // 3
  {1, 2, 5, 6}, // 4
  {0, 2, 3, 5, 6}, // 5
  {0, 2, 3, 4, 5, 6}, // 6
  {0, 1, 2, 6}, // 7
  {0, 1, 2, 3, 4, 5, 6}, // 8
  {0, 1, 2, 3, 5, 6} // 9
}

// Constructor
seg::seg(int digits, int[] char_pins, int[] mux_pins) {
  // Declare pins as outputs
  for (int i = 0; i < sizeof(top_pins); i++) {
    pinMode(top_pins[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(bottom_pins); i++) {
    pinMode(bottom_pins[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(mux_pins); i++) {
    pinMode(mux_pins[i], OUTPUT);
  }
}

// Write to segment block
void seg::write(uint32_t number) {
  int digit;
  int m = seg::size(mux_pins[]); // Find size/last index of mux_pins

  // Clear segment
  seg::clear();
  // Loop through *number*
  while (number != 0) {
    // Set MUX pins
    digitalWrite(m, HIGH);
    /// Print to segment display
    digit = (number % 10);
    // Set relevant character pins
    for (int i = 0; i < seg::size(digitCodeMap[digit]); i++) {
      digitalWrite(digitCodeMap[i], HIGH);
    }
    ///
    // Clear MUX pin
    digitalWrite(m, LOW);
    //
    m--;
    number /= 10;
  }
}

// Return size of array
int seg::size(int[] arr) {
  return size = sizeof(arr)/sizeof(arr[0]);
}

// Clear segment
void seg::clear() {
  for (int i = 0; i < seg.size(char_pins[]); i++) {
    digitalWrite(digitCodeMap[i], LOW);
  }
}

/// I2C Configuration

// Set instance as master
static void seg::master() {
  Wire.begin();
}

// Set instance as slave
static void seg::slave(uint8_t _address, int num_devices) {
  Wire.begin(_address);
}

// Check if device is connected
bool seg::isConnected() {
{
  for (uint8_t dev = 1; dev <= num_devices; dev++) {
    Wire.beginTransmission(dev);
    if (Wire.endTransmission() == 0) {
      return true;
    }
  }
  return false;
}

///
