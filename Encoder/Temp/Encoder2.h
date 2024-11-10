#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
public:
  Encoder(int pinA, int pinB, float countsPerRev, int interval);

  void begin();
  void update();

  // Static method to set the instance
  static void setInstance(Encoder* enc);

private:
  int Encoder_A, Encoder_B;
  int Time_Interval;
  float counts_per_revolution;
  float radians_per_count;

  volatile long count;
  long prev_count;
  unsigned long last_time;

  void handleEncoderA();
  void handleEncoderB();

  // Static handlers to call instance methods
  static void handleStaticEncoderA();
  static void handleStaticEncoderB();

  // Singleton instance pointer to access from static functions
  static Encoder* instance;
};

#endif // ENCODER_H
