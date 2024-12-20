#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>  // 包含 Arduino 核心库
// 电机类定义
class Motor {
public:
    // 构造函数：初始化电机的引脚
    Motor(int motorD_Pin, int motorA_Pin);
    // 初始化电机引脚（可选）
    void begin();
    // 设置电机速度（0-255）和方向（正转或反转）
    void setSpeed(int speed);
    // 停止电机
    void stop();
private:
    int _motorD_Pin;  // 电机正向引脚
    int _motorA_Pin;  // 电机反向引脚
};
#endif  // MOTOR_H
