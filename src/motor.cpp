#include "motor.h"

Motor::Motor(int motorD_Pin, int motorA_Pin) {
    _motorD_Pin = motorD_Pin;
    _motorA_Pin = motorA_Pin;
}

void Motor::begin() {
    pinMode(_motorD_Pin, OUTPUT);
    pinMode(_motorA_Pin, OUTPUT);
    stop();
}

void Motor::setSpeed(int speed,unsigned int zone=10) {
    speed = constrain(speed, -255, 255);

    if (speed > zone) {
        analogWrite(_motorD_Pin, speed);
        analogWrite(_motorA_Pin, 0);
    } else if (speed < -zone) {
        analogWrite(_motorD_Pin, 0);
        analogWrite(_motorA_Pin, -speed);
    } else {
        analogWrite(_motorD_Pin, 0);
        analogWrite(_motorA_Pin, 0);
    }
}

void Motor::stop() {
    analogWrite(_motorD_Pin, 0);
    analogWrite(_motorA_Pin, 0);
}
