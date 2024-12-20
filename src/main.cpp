#include "ps2_controller.h"

// 创建PS2Controller对象
PS2Controller ps2Controller;

void setup() {
  Serial.begin(9600);

  // 尝试初始化 PS2 控制器
  if (!ps2Controller.init()) {
    Serial.println("PS2 Controller initialization failed.");
    while (1);  // 初始化失败，停在这里
  }

  Serial.println("PS2 Controller initialized successfully.");
}

void loop() {
  // 每次循环时读取控制器的状态
  ps2Controller.update();
  
  // 获取遥控器的状态
  int analogX = ps2Controller.state.analogX;
  int analogY = ps2Controller.state.analogY;
  bool buttonA = ps2Controller.state.buttonA;

  // 输出摇杆值和按钮状态
  Serial.print("Analog X: ");
  Serial.print(analogX);
  Serial.print(" Analog Y: ");
  Serial.print(analogY);
  Serial.print(" Button A: ");
  Serial.println(buttonA ? "Pressed" : "Not Pressed");

  delay(500);  // 延时500毫秒，避免输出过快
}
