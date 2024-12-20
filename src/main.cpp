#include "motor.h"
#include"configuration.h"
#include "diff_drive.h"
#include<Arduino.h>
#include "ps2_controller.h"
#define RPM 48
float omega_max=RPM*PI/60;
// 创建PS2Controller对象
PS2Controller ps2Controller;
// 创建电机实例
DifferentialDrive drive(0.144);
Motor rightMotor(MOTOR_RIGHT_D_PIN, MOTOR_RIGHT_A_PIN);
Motor leftMotor(MOTOR_LEFT_D_PIN,MOTOR_LEFT_A_PIN);
void setup() {
    // 初始化电机
    rightMotor.begin();
    leftMotor.begin();
    Serial.begin(9600);
    // 尝试初始化 PS2 控制器
    if (!ps2Controller.init()) {
        while (1);  // 初始化失败，停在这里
  }
}

int map_math2pythics(float math,float math_max=0.41,int physcis_max=255){
    int convert=0;
    convert=int(round((math/math_max)*physcis_max));
    return constrain(convert,-255,255); 
}

float map_pythics2math(int physics,int physcis_max=255,float math_max=0.41){
    float convert=0;
    physics=physics-physcis_max/2;
    return constrain(physics,-math_max,math_max);
}

int physics_v_R=0;
int physics_v_L=0;
void loop() {
    // 电机正转，速度 200（范围 0 到 255）

    ps2Controller.update(true);
    // 获取遥控器的状态
    int analogX = ps2Controller.state.analogX;
    int analogY = ps2Controller.state.analogY;
    float mathY=map_pythics2math(analogY,255,0.41);
    float mathX=map_pythics2math(analogX,255,omega_max);
    drive.calculateWheelSpeeds(mathY,mathX,true);  // 假设目标线速度为 0.1 m/s，角速度为 0.2 rad/s
    physics_v_L=map_math2pythics(drive.v_L,0.41,240);
    physics_v_R=map_math2pythics(drive.v_R);
    rightMotor.setSpeed(physics_v_R);
    leftMotor.setSpeed(physics_v_L); 
    delay(100);
}