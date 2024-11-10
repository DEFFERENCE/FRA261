#include "Encoder.h"

// Initialize the static instance pointer
Encoder* Encoder::instance = nullptr;

// Constructor
Encoder::Encoder(int pinA, int pinB, float PulsePerRevolution)
    : pinA(pinA), pinB(pinB), countsPerRevolution(PulsePerRevolution * 4),
      radiansPerCount((2 * M_PI) / countsPerRevolution) {

    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);

    instance = this;
    attachInterrupt(digitalPinToInterrupt(pinA), handleInterruptA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinB), handleInterruptB, CHANGE);
}

// Update method to calculate position and velocity
void Encoder::update() {
    unsigned long currentTime = millis();
    if (currentTime - lastTime >= Time_Interval) {  // Update interval in milliseconds
        double deltaCount = count - prevCount;
        double deltaTime = (currentTime - lastTime); // Time in ms

        position = count * radiansPerCount;
        velocity = (deltaCount * radiansPerCount) * 1000 / deltaTime; // Convert ms to s

        prevCount = count;
        lastTime = currentTime;
    }
}

double Encoder::getPosition() const {
    return position;
}

double Encoder::getVelocity() const {
    return velocity;
}

void Encoder::handleA() {
    inputA = digitalRead(pinA);
    inputB = digitalRead(pinB);

    if (inputA == HIGH) {
        if (inputB == LOW) {
            count++;
        } else {
            count--;
        }
    } else {
        if (inputB == HIGH) {
            count++;
        } else {
            count--;
        }
    }
}

void Encoder::handleB() {
    inputA = digitalRead(pinA);
    inputB = digitalRead(pinB);

    if (inputB == HIGH) {
        if (inputA == HIGH) {
            count++;
        } else {
            count--;
        }
    } else {
        if (inputA == LOW) {
            count++;
        } else {
            count--;
        }
    }
}

void Encoder::handleInterruptA() {
    if (instance) {
        instance->handleA();
    }
}

void Encoder::handleInterruptB() {
    if (instance) {
        instance->handleB();
    }
}
