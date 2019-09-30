


#include "MiniMeter.h"


ReadResistance rr;
ReadInduction ri;

void setup() {
    Serial.begin(115200);
    Serial.print(msg(22));
    Serial.print(VERSION);
    pinMode(pinLCDpower, OUTPUT);
    digitalWrite(pinLCDpower, HIGH);
    rr.setup();
    ri.setup();
    u8g2.begin();
    delay(100);
} // end of setup

void loop() {
    rr.measure(showData);
    draw(showData);
    delay(100);
}
