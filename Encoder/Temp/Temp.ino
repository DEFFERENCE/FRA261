#include "Encoder2.h"

// Initialize encoder with appropriate parameters
Encoder myEncoder(27, 28, 2048.0 * 4, 100);

void setup() {
  Encoder::setInstance(&myEncoder); // Set the instance pointer
  myEncoder.begin();
}

void loop() {
  myEncoder.update();
}
