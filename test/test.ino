#include <math.h>

int chr[] = {4, 5, 8, 7, 6, 3, 2, 9};
int mux[] = {10, 11};
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
   {0, 1, 2, 0, 5, 6, 0, 0} // 9
   // {0, 1, 2, 3, 5, 6, 0, 0} // 9
};

void setup () {
   // Set up program counter
   // seg prog = seg(digits, chr, mux);
   // seg::master();
   Serial.begin(9600);
   // Set pins as output
   for (int i = 0; i < 8; i++) {
      pinMode(chr[i], OUTPUT);
      digitalWrite(chr[i], HIGH);
   }
   for (int i = 0; i < 2; i++) {
      pinMode(mux[i], OUTPUT);
   }
}

void clear() {
   for(int i = 0; i < 8; i++) {
      digitalWrite(chr[i], HIGH);
   }
}

void write(int number) {
   int pin;
   int digit;
   // Find size/last index of mux_pins
   int m = 1;

   // Loop through *number*
   while (m > -1) {
      // Clear display
      clear();
      // Set MUX pins
      for (int i = 1; i >= 0; i--) {
         if (i == m) {
            digitalWrite(mux[i], HIGH);
         }
         else {
            digitalWrite(mux[i], LOW);
         }
      }
      /// Print to segment display
      digit = number % 10;
      // Set relevant character pins
      for (int i = 0; i < 8 ; i++) {
         pin = digitCodeMap[digit][i];
         digitalWrite(chr[pin], LOW);
      }
      ///
      m--;
      number = floor(number / 10);
   }
}

void loop() {
   write(39);
}
