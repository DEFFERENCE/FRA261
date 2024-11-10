#include "Current_sensor.h"

CurrentSensor::CurrentSensor(int analogPin, int offsetVoltage, int sensitivity, unsigned long updateInterval)
    : _analogPin(analogPin), _offsetVoltage(offsetVoltage), _sensitivity(sensitivity), _updateInterval(updateInterval),
      _previousMillis(0), _currentSum(0), _sampleCount(0) {}

void CurrentSensor::begin() {
    Serial.begin(115200);  // Set a high baud rate for faster serial communication
    pinMode(_analogPin, INPUT);
}

void CurrentSensor::update() {
    unsigned long currentMillis = millis();

    // Continuously collect data and add to the sum
    _currentSum += readCurrent();
    _sampleCount++;

    // Every update interval, calculate the average and print it
    if (currentMillis - _previousMillis >= _updateInterval) {
        _previousMillis = currentMillis;
        calculateAndPrintAverage();
    }
}

double CurrentSensor::readCurrent() {
    int analogValue = analogRead(_analogPin);
    double voltage = (analogValue / 4096.0) * 5000; // Convert ADC value to voltage in mV
    double current = (voltage - _offsetVoltage) / _sensitivity;
    return current;
}

void CurrentSensor::calculateAndPrintAverage() {
    if (_sampleCount > 0) {  // Ensure there are readings to avoid division by zero
        double averageCurrent = _currentSum / _sampleCount;
        Serial.println(averageCurrent);

        // Reset the sum and count for the next interval
        _currentSum = 0;
        _sampleCount = 0;
    }
}
