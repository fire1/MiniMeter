//
// Created by Angel Zaprianov on 2019-09-30.
//

#ifndef MINIMETER_READRESISTANCE_H
#define MINIMETER_READRESISTANCE_H

#include "../MiniMeter.h"
//
// Threshold raw read to switch to internal  voltage reference
#ifndef THRESHOLD_INT
// value is read from external reference
#define THRESHOLD_INT 246
#endif

//
// Threshold raw read to switch to external voltage reference
#ifndef THRESHOLD_EXT
// value is read from internal reference
#define THRESHOLD_EXT 1000
#endif

class ReadResistance {
    int raw;
    boolean vRefExternal = true;


    static int readRaw() {
        uint32_t readSamples = 0;
        for (index = 0; index < resSamples; index++) {
            readSamples += analogRead(pinResistance);
            delayMicroseconds(600);
        }
        readSamples /= resSamples;
        return readSamples;
    }

    static void fooRead() {
        // After changing the analog reference, the first few readings from analogRead() may not be accurate.
        index = 0;
        while (index < 10) {
            analogRead(pinResistance);
            delay(10);
            index++;
        }
    }

    static inline double toVolts(int raw, float vReference) {
        return (vReference * raw) / 1024.0;
    }

    void switchInternalVrf() {
        analogReference(INTERNAL);
        vRefExternal = false;
        fooRead();
    }

    void switchExternalVrf() {
        analogReference(DEFAULT);
        vRefExternal = true;
        fooRead();
    }

    double getParsedVoltage() {

        raw = readRaw();
        if (raw > 1000 && !vRefExternal) {
            // switch to external voltage reference
            switchExternalVrf();
            raw = readRaw();
        }
        if (raw < 245 && vRefExternal) {
            // switch to internal voltage reference
            switchInternalVrf();
            raw = readRaw();
        }
        return toVolts(raw, (vRefExternal) ? vrfExternal : vrfInternal);
    }

public:

    void setup() {
        pinMode(pinResistance, INPUT_PULLUP);
    }

    void measure(display *data) {
        double voltage = getParsedVoltage();
        data->title = F("MilliOhm meter");
        data->mode = msg(23);
        data->genMeasure = voltage;
        data->getUnits = msg(12);
        data->subMeasure = raw;
//        data->subUnits = "";
        Serial.print(F(" vRef "));
        Serial.print(vRefExternal);
    }
};

#endif //MINIMETER_READRESISTANCE_H
