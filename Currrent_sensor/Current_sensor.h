#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include <Arduino.h>

class CurrentSensor {
public:
    CurrentSensor(int analogPin, int offsetVoltage, int sensitivity, unsigned long updateInterval);
    void begin();
    void update();

private:
    int _analogPin;
    int _offsetVoltage;
    int _sensitivity;
    unsigned long _updateInterval;
    unsigned long _previousMillis;
    double _currentSum;
    int _sampleCount;

    double readCurrent();
    void calculateAndPrintAverage();
};

#endif
