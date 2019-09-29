//
// Created by Admin on 5/22/2019.
//

#ifndef INDUCTANCEMETER_RESISTANCE_H
#define INDUCTANCEMETER_RESISTANCE_H

#include "MiniMeter.h"

int resistor;

void resistance() {

    resistor = 0;

    for (index = 0; index < 10; index++)
        resistor += analogRead(A0);

    resistor /= 10;

    int buffer = resistor * 5;
    double Vout = (buffer) / 1024.0;
    buffer = (5 / Vout) - 1;
    float R2 = 202.2 * buffer;
    Serial.print("Vout: ");
    Serial.println(Vout);
    Serial.print("R2: ");
    Serial.print(R2);
    Serial.println();


    u8g2.setFont(u8g2_font_lastapprenticebold_tr);    // choose a suitable font
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.setCursor(0, 24);
//        u8g2.print(F("  "));
        u8g2.print(R2);
    } while (u8g2.nextPage());


    delay(100);
}

#endif //INDUCTANCEMETER_RESISTANCE_H
