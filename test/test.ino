#include <math.h>

int chr[] = {4, 5, 8, 7, 6, 3, 2, 9};
int mux[] = {0, 0, 0, 10, 11};

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
};

void setup() {
   // Set up program counter
   // seg prog = seg(digits, chr, mux);
   // seg::master();
   Serial.begin(9600);
   // Set pins as output
   for (int i = 0; i < 8; i++) {
      pinMode(chr[i], OUTPUT);
      digitalWrite(chr[i], HIGH);
   }
   for (int i = 0; i < 5; i++) {
      pinMode(mux[i], OUTPUT);
   }
}

void clear() {
   for(int i = 0; i < 8; i++) {
      digitalWrite(chr[i], HIGH);
   }
   for(int i = 0; i < 5; i++) {
      digitalWrite(mux[i], LOW);
   }
}

void write(int number) {
   int _num = number;
   int pin = 0;
   int digit = 0;
   // Last index of mux_pins
   int m = 4;

   // Loop through *number*
   // Added null-exception: allows for variable segment length (max 5)
   while ((m > -1) && (mux[m] != 0)) {
      // delay(10);
      // clear display
      clear();

      // Set MUX pins
      for (int i = 4; i >= 0; i--) {
         if (i == m) {
            digitalWrite(mux[i], HIGH);
         }
         else {
            digitalWrite(mux[i], LOW);
         }
      }
      /// Print to segment display
      digit = _num % 10;
      // Serial.print(digit);
      // Serial.print("\t");
      // Set relevant character pins
      for (int i = 0; i < 8; i++) {
         pin = digitCodeMap[digit][i];
         digitalWrite(chr[pin], LOW);
      }
      ///
      m--;
      _num = floor(_num / 10);
      // Serial.print(number);

      // Serial.print("\t");
      // Serial.print(digitalRead(11));
      // Serial.print("\t");
      // Serial.println(digitalRead(10));
      delay(10);
   }
}

void loop() {
   // for (int i = 0; i < 100; i++) {
   //    write(i);
   //    delay(100);
   // }
   write(1);
   delay(1000);
   write(22);
   delay(1000);
}
