#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
public:
  // Constructor
  Encoder(int pinA, int pinB, float PulsePerRevolution);

  // Public methods to update the encoder state and retrieve position and velocity
  void update();
  double getPosition() const;
  double getVelocity() const;

private:
  // Encoder pin definitions
  const int pinA;
  const int pinB;

  // Constants related to encoder resolution and conversion
  const double countsPerRevolution;
  const double radiansPerCount;
  const int Time_Interval = 100;

  // Variables for tracking encoder counts, position, and velocity
  volatile long count = 0;
  int inputA, inputB;
  unsigned long lastTime = 0;
  long prevCount = 0;
  double position = 0.0;
  double velocity = 0.0;

  // Private methods for handling encoder interrupts
  void handleA();
  void handleB();

  // Static instance pointer and static interrupt handlers
  static Encoder* instance;
  static void handleInterruptA();
  static void handleInterruptB();
};

#endif // ENCODER_H
