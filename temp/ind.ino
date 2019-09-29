#include <Arduino.h>
#include <FreqCount.h>

#ifndef FreqCount_h

#include "../libraries/FreqCount/FreqCount.h"

#endif
unsigned long hz;

const double pi4 = 39.4784176044;



// Frequency counter sketch, for measuring frequencies low enough to execute an interrupt for each cycle
// Connect the frequency source to the INT0 pin (digital pin 2 on an Arduino Uno)

volatile unsigned long firstPulseTime;
volatile unsigned long lastPulseTime;
volatile unsigned long numPulses;

void isr() {
    unsigned long now = micros();
    if (numPulses == 0) {
        firstPulseTime = now;
    } else {
        lastPulseTime = now;
    }
    ++numPulses;
}

// Measure the frequency over the specified sample time in milliseconds, returning the frequency in Hz
float readFrequency(unsigned int sampleTime) {
    uint8_t pin = digitalPinToInterrupt(3);
    numPulses = 0;                      // prime the system to start a new reading
    attachInterrupt(pin, isr, FALLING);    // enable the interrupt
    delay(sampleTime);
    detachInterrupt(pin);
    return (numPulses < 2) ? 0 : (1000000UL * (numPulses - 1)) / (lastPulseTime - firstPulseTime);
}


const double capacitor = 0.00015;

double induction(float hertz) {
    return 1 / (pi4 * capacitor * pow(hertz, 2));
//    return abs(((hertz * hertz) / (1.38 * 1.38 ) * - 1.0) * L_ideal);
}

const int interval = 2000;

void setup() {
    Serial.begin(115200);
    pinMode(9, OUTPUT);
    pinMode(5, INPUT);
    pinMode(3,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(3), isr, FALLING);
    FreqCount.begin(2000);
}


double pulse;
float frequency;                    // measure frequency using the pulse as in usec use 1.E6
double inductance;
double mH_induct;
double cap = 1.5E-6;

boolean blink = 0;

void loop() {
    Serial.println();
    Serial.print(readFrequency(1000));
    delay(100);
    /*
    if (FreqCount.available()) {
        frequency = interval / FreqCount.read();

        Serial.print(" - ");
        Serial.print(frequency);
        Serial.print(" / ");
        Serial.print(map(frequency, 153, 333, 22, 100));
        Serial.print(" / ");
        Serial.print(induction(frequency));
        Serial.print(" uH");
        digitalWrite(LED_BUILTIN, blink);
        blink = !blink;
        delay(100);
    }
     */
}