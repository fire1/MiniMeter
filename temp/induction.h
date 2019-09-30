//
// Created by Admin on 5/22/2019.
//

#ifndef INDUCTANCEMETER_INDUCTION_H
#define INDUCTANCEMETER_INDUCTION_H

#include "MiniMeter.h"

// these are checked for in the main program
volatile unsigned long timerCounts;
volatile boolean counterReady;

// internal to counting routine
unsigned long overflowCount;
unsigned int timerTicks;
unsigned int timerPeriod;


void startCounting(unsigned int ms) {
    counterReady = false;         // time not up yet
    timerPeriod = ms;             // how many 1 ms counts to do
    timerTicks = 0;               // reset interrupt counter
    overflowCount = 0;            // no overflows yet

    // reset Timer 1 and Timer 2
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR2A = 0;
    TCCR2B = 0;

    // Timer 1 - counts events on pin D5
    TIMSK1 = bit (TOIE1);   // interrupt on Timer 1 overflow

    // Timer 2 - gives us our 1 ms counting interval
    // 16 MHz clock (62.5 ns per tick) - prescaled by 128
    //  counter increments every 8 µs.
    // So we count 125 of them, giving exactly 1000 µs (1 ms)
    TCCR2A = bit (WGM21);   // CTC mode
    OCR2A = 124;            // count up to 125  (zero relative!!!!)

    // Timer 2 - interrupt on match (ie. every 1 ms)
    TIMSK2 = bit (OCIE2A);   // enable Timer2 Interrupt

    TCNT1 = 0;      // Both counters to zero
    TCNT2 = 0;

    // Reset prescalers
    GTCCR = bit (PSRASY);        // reset prescaler now
    // start Timer 2
    TCCR2B = bit (CS20) | bit (CS22);  // prescaler of 128
    // start Timer 1
    // External clock source on T1 pin (D5). Clock on rising edge.
    TCCR1B = bit (CS10) | bit (CS11) | bit (CS12);
}  // end of startCounting

ISR (TIMER1_OVF_vect) {
    ++overflowCount;               // count number of Counter1 overflows
}  // end of TIMER1_OVF_vect


//******************************************************************
//  Timer2 Interrupt Service is invoked by hardware Timer 2 every 1 ms = 1000 Hz
//  16Mhz / 128 / 125 = 1000 Hz

ISR (TIMER2_COMPA_vect) {
    // grab counter value before it changes any more
    unsigned int timer1CounterValue;
    timer1CounterValue = TCNT1;  // see datasheet, page 117 (accessing 16-bit registers)
    unsigned long overflowCopy = overflowCount;

    // see if we have reached timing period
    if (++timerTicks < timerPeriod)
        return;  // not yet

    // if just missed an overflow
    if ((TIFR1 & bit (TOV1)) && timer1CounterValue < 256)
        overflowCopy++;

    // end of gate time, measurement ready

    TCCR1A = 0;    // stop timer 1
    TCCR1B = 0;

    TCCR2A = 0;    // stop timer 2
    TCCR2B = 0;

    TIMSK1 = 0;    // disable Timer1 Interrupt
    TIMSK2 = 0;    // disable Timer2 Interrupt

    // calculate total count
    timerCounts = (overflowCopy << 16) + timer1CounterValue;  // each overflow is 65536 more
    counterReady = true;              // set global flag for end count period
}  // end of TIMER2_COMPA_vect


void induction(){

    // stop Timer 0 interrupts from throwing the count out
    byte oldTCCR0A = TCCR0A;
    byte oldTCCR0B = TCCR0B;
    TCCR0A = 0;    // stop timer 0
    TCCR0B = 0;

    startCounting(500);  // how many ms to count for

    while (!counterReady) {}  // loop until count over

    // adjust counts by counting interval to give frequency in Hz
    float frq = (timerCounts * 1000.0) / timerPeriod;
    double ind = 50000 / (frq / 100);



    Serial.println();
    Serial.print("Frequency: ");
    Serial.print((unsigned long) frq);
    Serial.print(" Hz.  ");
    if (ind > 1000000) {
        Serial.print(ind / 1000000);
        Serial.print(" H");
    } else if (ind > 1000) {
        Serial.print(ind / 1000);
        Serial.print(" mH");
    } else {
        Serial.print(ind);
        Serial.print(" uH");
    }
    // restart timer 0
    TCCR0A = oldTCCR0A;
    TCCR0B = oldTCCR0B;
    // let serial stuff finish



    u8g2.setFont(u8g2_font_lastapprenticebold_tr);    // choose a suitable font
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.setCursor(0, 24);
        u8g2.print(ind);
        u8g2.print(" uH");
        u8g2.setCursor(0, 46);
        u8g2.print(frq);
        u8g2.print(" hZ");
    } while (u8g2.nextPage());
    delay(100);
}


#endif //INDUCTANCEMETER_INDUCTION_H
