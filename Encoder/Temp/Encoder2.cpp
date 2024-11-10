#include "Encoder2.h"

Encoder* Encoder::instance = nullptr; // Define the static instance pointer

Encoder::Encoder(int pinA, int pinB, float countsPerRev, int interval)
  : Encoder_A(pinA), Encoder_B(pinB), counts_per_revolution(countsPerRev), Time_Interval(interval) {
  radians_per_count = (2 * PI) / counts_per_revolution;
  count = 0;
  prev_count = 0;
  last_time = 0;
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
    double position = count * radians_per_count;

    double delta_count = count - prev_count;
    double delta_time = (current_time - last_time);
    double velocity = (delta_count * radians_per_count) * 1000 / delta_time;

    prev_count = count;
    last_time = current_time;

    Serial.print(position);
    Serial.print(",");
    Serial.println(velocity);
  }
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

// Static handlers to call instance methods
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
