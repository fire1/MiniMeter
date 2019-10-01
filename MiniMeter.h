//
// Created by Admin on 9/29/2019.
//

#ifndef MINI_METER_H
#define MINI_METER_H

#include <Arduino.h>

#undef NO_DISPLAY
#ifndef NO_DISPLAY

#include <Wire.h>
#include <U8g2lib.h>

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif
#endif


#define VERSION 1.0
const float vrfExternal = 5;
const float vrfInternal = 1.2;
const uint8_t pinLCDpower = 2;
const uint8_t pinResistance = A0;
const uint8_t resSamples = 15;
volatile uint8_t index = 0;

#ifndef NO_DISPLAY
U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0);
#endif


struct display {
    String title;
    String mode;
    double genMeasure;
    char *getUnits;
    float subMeasure;
    char *subUnits;
};

display showData;


#include "lib/Messages.h"
#include "lib/ReadResistance.h"
#include "lib/ReadInduction.h"

/**
 * Display data
 * @param data
 */
void draw(display *data) {

    Serial.println();
    Serial.print(data->title);
    Serial.print(F(": "));
    Serial.print(data->mode);
    Serial.print(F(" >>> "));
    Serial.print(data->genMeasure, 4);
    Serial.print(F(" "));
    Serial.print(data->getUnits);
    Serial.print(F(" / "));
    Serial.print(data->subMeasure, 4);
    Serial.print(F(" "));
    Serial.print(data->subUnits);
    Serial.print(F(" "));


#ifndef NO_DISPLAY
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_artossans8_8r);
        u8g2.setCursor(4, 12);
        u8g2.print(data->title);
        u8g2.print(data->mode);
        u8g2.setCursor(4, 62);
        u8g2.print(data->subMeasure);
        u8g2.print(msg(20));
        u8g2.print(data->subUnits);
        u8g2.setFont(u8g2_font_logisoso16_tr);
        u8g2.setCursor(12, 44);
        u8g2.print(data->genMeasure);
        u8g2.setFont(u8g2_font_artossans8_8r);
        u8g2.print(F(" "));
        u8g2.print(data->getUnits);
    } while (u8g2.nextPage());
#endif
}


#endif //MINIMETER_MINIMETER_H
