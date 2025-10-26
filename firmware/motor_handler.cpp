#include "motor_handler.h"

MotorHandler::MotorHandler(uint8_t motorPin) {
    pin = motorPin;
}

void MotorHandler::initialize() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void MotorHandler::vibrate(int duration) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
}