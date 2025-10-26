#ifndef MOTOR_HANDLER_H
#define MOTOR_HANDLER_H

#include <Arduino.h>

class MotorHandler {
private:
    uint8_t pin;

public:
    MotorHandler(uint8_t motorPin);
    void initialize();
    void vibrate(int duration);
};

#endif