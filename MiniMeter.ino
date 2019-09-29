
// Timer and Counter example
// Author: Nick Gammon
// Date: 17th January 2012

// Input: Pin D5

#include "MiniMeter.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Millimeter");
    pinMode(pinLCDpower, OUTPUT);
    digitalWrite(pinLCDpower, HIGH);
    u8g2.begin();
    delay(100);
} // end of setup

void loop() {
//    resistance();
    induction();
}
