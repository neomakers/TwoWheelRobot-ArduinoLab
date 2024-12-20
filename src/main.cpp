#include <Arduino.h>
#include "diff_drive.h"

DifferentialDrive drive(0.15);  // 假设轮距为 0.15 米

void setup() {
    Serial.begin(9600);
}

void loop() {
    // 在循环中你可以调用控制函数来实时调整速度
    for(int i=0;i<10;i++){
        drive.calculateWheelSpeeds(0.1, i*0.1);  // 假设目标线速度为 0.1 m/s，角速度为 0.2 rad/s
        delay(1000);
    }
    
}
