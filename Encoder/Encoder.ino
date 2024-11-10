#include "Encoder.h"
// Global Encoder instance
Encoder encoder(27, 28, 2048.0); // Adjust pins and pulse-per-revolution as needed

void setup() {
    Serial.begin(115200);
}

void loop() {
    encoder.update();
    Serial.print(encoder.getPosition());
    Serial.print(",");
    Serial.println(encoder.getVelocity());
}
