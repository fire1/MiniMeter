

#define NO_DISPLAY

#include "MiniMeter.h"


ReadResistance rr;
ReadInduction ri;

void setup() {
    Serial.begin(115200);
    Serial.print(msg(22));
    Serial.print(VERSION);
    Serial.println();
    pinMode(pinLCDpower, OUTPUT);
    digitalWrite(pinLCDpower, HIGH);

#ifdef NO_DISPLAY
    u8g2.begin();
#endif
    rr.setup();
    ri.setup();
    delay(100);
} // end of setup

void loop() {
    rr.measure(&showData);
    draw(&showData);
    delay(150);
}
