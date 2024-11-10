#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
public:
    Encoder(int pinA, int pinB, float PulsePerRevolution);
    void update();
    double getPosition() const;
    double getVelocity() const;

private:
    const int pinA;
    const int pinB;
    const double countsPerRevolution;
    const double radiansPerCount;
    const int Time_Interval = 100;

    volatile long count = 0;
    int inputA, inputB;
    unsigned long lastTime = 0;
    long prevCount = 0;
    double position = 0.0;
    double velocity = 0.0;

    void handleA();
    void handleB();

    static Encoder* instance;
    static void handleInterruptA();
    static void handleInterruptB();
};

#endif // ENCODER_H
