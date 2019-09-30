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
const float vrfExterna = 5;
const float vrfInternal = 1.2;
const uint8_t pinLCDpower = 2;
const uint8_t pinResistance = A0;
const uint8_t resSamples = 15;
volatile uint8_t index = 0;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

#include "lib/Messages.h"
#include "lib/ReadResistance.h"
#include "lib/ReadInduction.h"

#endif //MINIMETER_MINIMETER_H
