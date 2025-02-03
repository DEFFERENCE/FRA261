#include "Encoder2.h"

// Initialize the static instance pointer
Encoder* Encoder::instance = nullptr;

Encoder::Encoder(int pinA, int pinB, float countsPerRev, int interval)
  : Encoder_A(pinA), Encoder_B(pinB), counts_per_revolution(countsPerRev), Time_Interval(interval),
    velocity(0), position(0), count(0), prev_count(0), last_time(0) {
  radians_per_count = (2 * PI) / counts_per_revolution;
}

void Encoder::begin() {
  pinMode(Encoder_A, INPUT);
  pinMode(Encoder_B, INPUT);

  // Register static interrupt handlers
  attachInterrupt(digitalPinToInterrupt(Encoder_A), handleStaticEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Encoder_B), handleStaticEncoderB, CHANGE);
  Serial.begin(9600);
}

void Encoder::update() {
  unsigned long current_time = millis();
  if (current_time - last_time >= Time_Interval) {
    position = count * radians_per_count;

    double delta_count = count - prev_count;
    double delta_time = (current_time - last_time) / 1000.0; // Convert ms to seconds
    velocity = (delta_count * radians_per_count) / delta_time;

    prev_count = count;
    last_time = current_time;
  }
}

double Encoder::get_velocity() {
  return velocity;
}

double Encoder::get_Position() {
  return position;
}

void Encoder::setInstance(Encoder* enc) {
  instance = enc;
}

void Encoder::handleEncoderA() {
  int inputA = digitalRead(Encoder_A);
  int inputB = digitalRead(Encoder_B);

  if (inputA == HIGH) {
    count += (inputB == LOW) ? 1 : -1;
  } else {
    count += (inputB == HIGH) ? 1 : -1;
  }
}

void Encoder::handleEncoderB() {
  int inputA = digitalRead(Encoder_A);
  int inputB = digitalRead(Encoder_B);

  if (inputB == HIGH) {
    count += (inputA == HIGH) ? 1 : -1;
  } else {
    count += (inputA == LOW) ? 1 : -1;
  }
}

void Encoder::handleStaticEncoderA() {
  if (instance != nullptr) {
    instance->handleEncoderA();
  }
}

void Encoder::handleStaticEncoderB() {
  if (instance != nullptr) {
    instance->handleEncoderB();
  }
}
