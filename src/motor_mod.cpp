#include "motor_mod.h"
#include <Arduino.h>
// 全局指针，用于指向 Motor 类实例
Motor *motorPtr = nullptr; // 初始化全局指针为 nullptr

Motor::Motor(int motorD_Pin, int motorA_Pin, int encoder_Pin)
{
    _motorD_Pin = motorD_Pin;
    _motorA_Pin = motorA_Pin;
    _encoder_Pin = encoder_Pin;
    encoderCount = 0; // 初始化编码器计数为 0
}

void Motor::begin(void (*interruptFunc)())
{
    pinMode(_motorD_Pin, OUTPUT);
    pinMode(_motorA_Pin, OUTPUT);
    pinMode(_encoder_Pin, INPUT);
    stop();
    attachInterrupt(digitalPinToInterrupt(_encoder_Pin), interruptFunc, RISING);
}

// 设置电机速度和方向
void Motor::setSpeed(int speed, int zone)
{
    speed = constrain(speed, -255, 255);

    if (speed > zone)
    {
        analogWrite(_motorD_Pin, speed);
        analogWrite(_motorA_Pin, 0);
    }
    else if (speed < -1 * zone)
    {
        analogWrite(_motorD_Pin, 0);
        analogWrite(_motorA_Pin, -speed);
    }
    else
    {
        analogWrite(_motorD_Pin, 0);
        analogWrite(_motorA_Pin, 0);
    }
}

// 停止电机
void Motor::stop()
{
    analogWrite(_motorD_Pin, 0);
    analogWrite(_motorA_Pin, 0);
}

void Motor::addEncoderCount()
{
    encoderCount++;
}
// 获取编码器脉冲计数
unsigned int Motor::getEncoderCount()
{
    return encoderCount;
}

// 重置编码器计数
void Motor::resetEncoderCount()
{
    this->encoderCount = 0;
}
