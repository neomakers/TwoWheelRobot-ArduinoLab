#include "diff_drive.h"
#include <Arduino.h>  // 包含 Arduino 库，以便使用 Serial 对象

// 构造函数初始化轮距
DifferentialDrive::DifferentialDrive(float wheelDistance) {
    this->d = wheelDistance;
}

// 计算左右轮的速度
void DifferentialDrive::calculateWheelSpeeds(float v, float omega,bool show) {
    // v: 线速度 (m/s)
    // omega: 角速度 (rad/s)
    // d: 轮距 (m)

    v_L = v - (omega * d / 2);  // 左轮速度
    v_R = v + (omega * d / 2);  // 右轮速度
    if(show==true){
        // 输出左右轮速度
        Serial.print("Left Wheel Speed: ");
        Serial.println(v_L);
        Serial.print("Right Wheel Speed: ");
        Serial.println(v_R);
    }
}
