#include "Current_sensor.h"

CurrentSensor::CurrentSensor(int analogPin, int offsetVoltage, int sensitivity, unsigned long updateInterval)
    : _analogPin(analogPin),
      _offsetVoltage(offsetVoltage),
      _sensitivity(sensitivity),
      _updateInterval(updateInterval),
      _previousMillis(0),
      _currentSum(0),
      _sampleCount(0),
      averageCurrent(0) {}

void CurrentSensor::begin() {
    Serial.begin(9600);  // Set a high baud rate for debugging
    pinMode(_analogPin, INPUT);
}

void CurrentSensor::update() {
    unsigned long currentMillis = millis();

    // Accumulate current readings
    _currentSum += readCurrent();
    _sampleCount++;

    // Check if it's time to calculate the average
    if (currentMillis - _previousMillis >= _updateInterval) {
        _previousMillis = currentMillis;
        calculateAndPrintAverage();
    }
}

float CurrentSensor::readCurrent() {
    int analogValue = analogRead(_analogPin); // Read ADC value
    float voltage = (analogValue / 4096.0) * 5000; // Convert ADC value to voltage in mV
    float current = (voltage - _offsetVoltage) / _sensitivity; // Convert to current in A
    return current;
}

void CurrentSensor::calculateAndPrintAverage() {
    if (_sampleCount > 0) {
        averageCurrent = _currentSum / _sampleCount; // Calculate average current
        //Serial.println(averageCurrent); // Print the average current for debugging

        // Reset the accumulators
        _currentSum = 0;
        _sampleCount = 0;
    }
}

float CurrentSensor::get_current() {
    return averageCurrent; // Return the latest calculated average current
}
