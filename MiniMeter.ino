



#include "MiniMeter.h"


ReadInduction ri;
ReadResistance rr;

void setup() {
    Serial.begin(115200);
    Serial.print(msg(22));
    Serial.print(VERSION);
    Serial.println();

    rr.setup();
    ri.setup();
    pinMode(pinLCDpower, OUTPUT);
    digitalWrite(pinLCDpower, HIGH);
    pinMode(A5, OUTPUT);
    pinMode(A4, OUTPUT);
    delay(250);

#ifndef NO_DISPLAY
    u8g2.begin();
    u8g2.setPowerSave(0);
#endif
} // end of setup

void loop() {
    ri.measureSmall(&showData);
//    rr.measure(&showData);
    draw(&showData);
    delay(150);
}
