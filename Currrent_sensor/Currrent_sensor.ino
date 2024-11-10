#include "Current_sensor.h"

// Parameters: analog pin (A1), offset voltage (975), sensitivity (66), update interval (10 ms)
CurrentSensor sensor(A1, 975, 66, 10);

void setup() {
    sensor.begin();
}

void loop() {
    sensor.update();
}
