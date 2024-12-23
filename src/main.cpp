#include <Arduino.h>
#include "motor_mod.h"
#include "configuration.h"

// 创建左右电机对象
Motor motorLeft(MOTOR_LEFT_A_PIN, MOTOR_LEFT_D_PIN, MOTOR_LEFT_EN);     // 左电机
Motor motorRight(MOTOR_RIGHT_A_PIN, MOTOR_RIGHT_D_PIN, MOTOR_RIGHT_EN); // 右电机

// 左电机编码器中断服务函数
void countPulseLeft()
{
  motorLeft.addEncoderCount(); // 获取左电机编码器计数
}

// 右电机编码器中断服务函数
void countPulseRight()
{
  motorRight.addEncoderCount(); // 获取右电机编码器计数
}

// 初始化
void setup()
{
  Serial.begin(9600);

  // 初始化左右电机
  motorLeft.begin(countPulseLeft);   // 将 `countPulseLeft` 作为中断服务函数传递给左电机
  motorRight.begin(countPulseRight); // 将 `countPulseRight` 作为中断服务函数传递给右电机
}

void loop()
{
  // 控制电机速度，设置为中速
  motorLeft.setSpeed(128); // 左电机速度为 128
  Serial.print(motorLeft.getEncoderCount());
  motorRight.setSpeed(128); // 右电机速度为 128
  Serial.print(motorRight.getEncoderCount());
  delay(1000); // 延时 1 秒，循环更新
}
