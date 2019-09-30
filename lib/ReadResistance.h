//
// Created by Angel Zaprianov on 2019-09-30.
//

#ifndef MINIMETER_READRESISTANCE_H
#define MINIMETER_READRESISTANCE_H

//
// Threshold raw read to switch to internal  voltage reference
#ifndef THRESHOLD_INT
#define THRESHOLD_INT 246 // value is read from external reference
#endif

//
// Threshold raw read to switch to external voltage reference
#ifndef THRESHOLD_EXT
#define THRESHOLD_EXT 1000 // value is read from internal reference
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
        return ((float) raw / (float) resSamples * vReference) / 1024.0;
    }

    void switchInternalVrf() {
        analogReference(INTERNAL);
        vRefExternal = false;
        fooRead();
    }

    void switchExternalVrf() {
        analogReference(EXTERNAL);
        vRefExternal = false;
        fooRead();
    }

    double getParsedVoltage() {

        raw = readRaw();
        if (raw > THRESHOLD_EXT && !vRefExternal) {
            // switch to external voltage reference
            switchExternalVrf();
            raw = readRaw();
        } else if (raw < THRESHOLD_INT && vRefExternal) {
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

    void measure(display *&data) {
        double voltage = getParsedVoltage();
        data->title = String("MilliOhm meter");
        data->mode = String("Small ");
        data->genMeasure = voltage;
        data->getUnits = msg(12);
        data->subMeasure = raw;
        data->subUnits = "";
    }
};

#endif //MINIMETER_READRESISTANCE_H
