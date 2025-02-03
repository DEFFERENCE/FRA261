#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
public:
  /**
   * Constructor
   * @param pinA - Encoder channel A pin
   * @param pinB - Encoder channel B pin
   * @param countsPerRev - Number of counts per revolution of the encoder
   * @param interval - Time interval (in milliseconds) for velocity calculations
   */
  Encoder(int pinA, int pinB, float countsPerRev, int interval);

  /**
   * Initializes the encoder, sets up pins, and attaches interrupts.
   */
  void begin();

  /**
   * Updates the position and velocity calculations.
   * Should be called frequently in the main loop.
   */
  void update();

  /**
   * Gets the current velocity in radians per second.
   * @return Velocity in radians per second
   */
  double get_velocity();

  /**
   * Gets the current position in radians.
   * @return Position in radians
   */
  double get_Position();

  /**
   * Sets the singleton instance of the encoder.
   * Needed for the static interrupt handlers.
   * @param enc - Pointer to the Encoder instance
   */
  static void setInstance(Encoder* enc);

private:
  // Encoder pin assignments
  int Encoder_A, Encoder_B;

  // Time interval for velocity calculation (milliseconds)
  int Time_Interval;

  // Encoder specifications
  float counts_per_revolution;
  float radians_per_count;

  // Position and velocity
  volatile long count; // Current encoder count (volatile for ISR access)
  long prev_count;     // Previous encoder count for velocity calculations
  double velocity;     // Current velocity in radians per second
  double position;     // Current position in radians
  unsigned long last_time; // Last time the update function was called

  // Interrupt handler methods
  void handleEncoderA();
  void handleEncoderB();

  // Static interrupt handlers to call instance methods
  static void handleStaticEncoderA();
  static void handleStaticEncoderB();

  // Singleton instance pointer for accessing within static functions
  static Encoder* instance;
};

#endif // ENCODER_H
