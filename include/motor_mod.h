#ifndef MOTOR_H_MOD
#define MOTOR_H_MOD
#include <Arduino.h> // 包含 Arduino 核心库

// 电机类定义
class Motor
{
public:
    // 构造函数：初始化电机的引脚
    Motor(int motorD_Pin, int motorA_Pin, int encoder_Pin);

    // 初始化电机引脚（可选）
    void begin(void (*interruptFunc)());

    // 设置电机速度（0-255）和方向（正转或反转）
    void setSpeed(int speed, int zone = 10);

    // 停止电机
    void stop();

    // 获取编码器脉冲计数
    unsigned int getEncoderCount();

    // 重置编码器计数
    void resetEncoderCount();
    void addEncoderCount();

private:
    int _motorD_Pin;                    // 电机正向引脚
    int _motorA_Pin;                    // 电机反向引脚
    int _encoder_Pin;                   // 编码器引脚
    volatile unsigned int encoderCount; // 编码器脉冲计数（volatile，因为它会在 ISR 中修改）
};

#endif // MOTOR_H
