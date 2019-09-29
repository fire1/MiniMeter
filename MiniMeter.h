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


const uint8_t pinLCDpower = 2;
volatile uint8_t index = 0;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

#include "induction.h"
#include "resistance.h"
#endif //MINIMETER_MINIMETER_H
