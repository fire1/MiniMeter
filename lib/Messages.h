//
// Created by Angel Zaprianov on 2019-09-30.
//

#ifndef MINIMETER_MESSAGES_H
#define MINIMETER_MESSAGES_H


#include <avr/pgmspace.h>

//
// Induction
const char msg0[] PROGMEM = "Hz";
const char msg1[] PROGMEM = "Khz";
const char msg2[] PROGMEM = "Mhz";
const char msg3[] PROGMEM = "nH";
const char msg4[] PROGMEM = "uH";
const char msg5[] PROGMEM = "mH";
const char msg6[] PROGMEM = "H";
const char msg7[] PROGMEM = "V";
const char msg8[] PROGMEM = "";
const char msg9[] PROGMEM = "";

//
// Voltage
const char msg10[] PROGMEM = "uOhms";
const char msg11[] PROGMEM = "mOhms";
const char msg12[] PROGMEM = "Ohms";
const char msg13[] PROGMEM = "Volts";
const char msg14[] PROGMEM = "kH";
const char msg15[] PROGMEM = "kH";
const char msg16[] PROGMEM = "kH";
const char msg17[] PROGMEM = " In";
const char msg18[] PROGMEM = " Ex";
const char msg19[] PROGMEM = "";

//
// Basic UI
const char msg20[] PROGMEM = " ";
const char msg21[] PROGMEM = "Mode: ";
const char msg22[] PROGMEM = "MiniMeter ";
const char msg23[] PROGMEM = " Small ";
const char msg24[] PROGMEM = " Peek ";

const char *const msgTable[] PROGMEM = {
        msg0, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, msg9, msg10, msg11, msg12, msg13, msg14, msg15, msg16,
        msg17, msg18, msg19, msg20, msg21, msg22, msg23, msg24
};


char charBuffer[30];

char *msg(uint8_t indexMessage) {
    strcpy_P(charBuffer, (char *) pgm_read_word(&(msgTable[indexMessage])));
    return charBuffer;
}


#endif //MINIMETER_MESSAGES_H
