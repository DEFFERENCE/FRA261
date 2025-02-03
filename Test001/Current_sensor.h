#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include <Arduino.h>

class CurrentSensor {
public:
    /**
     * Constructor
     * @param analogPin - The analog pin connected to the current sensor
     * @param offsetVoltage - The zero-current voltage of the sensor (in mV)
     * @param sensitivity - The sensor sensitivity (mV per ampere)
     * @param updateInterval - The interval (in ms) for calculating the average current
     */
    CurrentSensor(int analogPin, int offsetVoltage, int sensitivity, unsigned long updateInterval);

    /**
     * Initializes the current sensor.
     */
    void begin();

    /**
     * Reads and updates the current sensor data.
     * Should be called frequently in the main loop.
     */
    void update();

    /**
     * Gets the average current in amperes.
     * @return The average current
     */
    float get_current();

private:
    int _analogPin;           // Analog pin connected to the current sensor
    int _offsetVoltage;       // Zero-current voltage (in mV)
    int _sensitivity;         // Sensor sensitivity (mV per ampere)
    unsigned long _updateInterval; // Update interval for averaging (ms)
    unsigned long _previousMillis; // Last time the average was calculated
    float _currentSum;       // Sum of current readings
    int _sampleCount;         // Number of readings in the current interval
    float averageCurrent;    // Average current in amperes

    /**
     * Reads the current from the sensor.
     * @return Current in amperes
     */
    float readCurrent();

    /**
     * Calculates the average current and resets the accumulators.
     */
    void calculateAndPrintAverage();
};

#endif // CURRENT_SENSOR_H
