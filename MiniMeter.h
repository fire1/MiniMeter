//
// Created by Admin on 9/29/2019.
//

#ifndef MINI_METER_H
#define MINI_METER_H

#include <Arduino.h>
#include <U8g2lib.h>

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif

#define VERSION 1.0
const float vrfExternal = 5;
const float vrfInternal = 1.2;
const uint8_t pinLCDpower = 2;
const uint8_t pinResistance = A0;
const uint8_t resSamples = 15;
volatile uint8_t index = 0;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);
struct display {
    String title;
    String mode;
    double genMeasure;
    char *getUnits;
    float subMeasure;
    char *subUnits;

};

display *showData;


void draw(display *data) {

    Serial.println();
    Serial.print(data->title);
    Serial.print(F(": "));
    Serial.print(data->mode);
    Serial.print(F(" >>> "));
    Serial.print(data->genMeasure);
    Serial.print(data->getUnits);
    Serial.print(F(" / "));
    Serial.print(data->subMeasure);
    Serial.print(data->subUnits);


    u8g2.setFont(u8g2_font_helvR12_tr);
    u8g2.firstPage();
    do {
        u8g2.setCursor(4, 4);
        u8g2.print(data->title);
        u8g2.print(F(" | "));
        u8g2.print(data->mode);
        u8g2.setCursor(4, 50);
        u8g2.print(data->subMeasure);
        u8g2.print(data->subUnits);
        u8g2.setFont(u8g2_font_logisoso20_tr);
        u8g2.setCursor(16, 20);
        u8g2.print(data->genMeasure);
        u8g2.print(data->getUnits);
    } while (u8g2.nextPage());
}


#include "lib/Messages.h"
#include "lib/ReadResistance.h"
#include "lib/ReadInduction.h"

#endif //MINIMETER_MINIMETER_H
