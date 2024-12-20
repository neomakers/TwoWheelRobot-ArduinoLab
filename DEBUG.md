# Chatgpt
https://chatgpt.com/c/67640fa6-2d94-8009-a5e3-cc4fb47092a1
  
# org
jian
```c
#include <Arduino.h>
#include"configuration.h"

void setup(){
  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(SENSOR_3_PIN, INPUT);

  pinMode(MOTOR_LEFT_A_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_D_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_EN,OUTPUT);
  pinMode(MOTOR_RIGHT_A_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_D_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(MOTOR_LEFT_EN,HIGH);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(MOTOR_LEFT_D_PIN,0);
  analogWrite(MOTOR_LEFT_A_PIN,255);
}
```
# char2int

```c
char inputBuffer[50];           // 用于存储串口输入的字符数组
int bufferIndex = 0;            // 字符数组当前索引
int convertedNumber = 0;        // 用于存储转换后的整数
bool inputComplete = false;     // 标记输入是否完成

void setup() {
  Serial.begin(9600);            // 初始化串口通信
  Serial.println("请输入一个整数：");
}

void loop() {
  // 检查串口是否有数据可读
  if (Serial.available() > 0) {
    // 读取串口数据并追加到inputBuffer中
    char incomingChar = Serial.read();
    if (incomingChar == '\n') {  // 检测换行符，表示输入结束
      inputBuffer[bufferIndex] = '\0'; // 在字符串末尾添加空字符，形成C风格字符串
      inputComplete = true;
    } else if (bufferIndex < 49) {  // 确保不会超出数组边界
      inputBuffer[bufferIndex] = incomingChar;
      bufferIndex++;
    }

    // 如果输入完成，则进行转换并打印结果
    if (inputComplete) {
      // 使用atoi()函数将C风格字符串转换为整数
      convertedNumber = atoi(inputBuffer);
      // 打印转换后的整数
      Serial.print("您输入的整数是：");
      Serial.println(convertedNumber);
      // 重置变量，为下一次输入做准备
      bufferIndex = 0;
      inputComplete = false;
    }
  }
}
```


# 未尝试用PWM的程序
```c
#include <Arduino.h>
#include"configuration.h"

char inputBuffer[50];           // 用于存储串口输入的字符数组
int bufferIndex = 0;            // 字符数组当前索引
int convertedNumber = 0;        // 用于存储转换后的整数
bool inputComplete = false;     // 标记输入是否完成

void setup(){
  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(SENSOR_3_PIN, INPUT);

  pinMode(MOTOR_LEFT_A_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_D_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_EN,OUTPUT);
  pinMode(MOTOR_RIGHT_A_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_D_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(MOTOR_LEFT_EN,HIGH);
  Serial.begin(9600);
  Serial.println("请输入一个整数：");
}

void loop(){
  if (Serial.available() > 0) {
    // 读取串口数据并追加到inputBuffer中
    char incomingChar = Serial.read();
    if (incomingChar == '\n') {  // 检测换行符，表示输入结束
      inputBuffer[bufferIndex] = '\0';  // 在字符串末尾添加空字符，形成C风格字符串
      inputComplete = true;
    } else if (bufferIndex < 49) {  // 确保不会超出数组边界
      inputBuffer[bufferIndex] = incomingChar;
      bufferIndex++;
    }

    // 如果输入完成，则进行转换并打印结果
    if (inputComplete) {
      // 使用atoi()函数将C风格字符串转换为整数
      convertedNumber = atoi(inputBuffer);
      // 打印转换后的整数
      Serial.print("您输入的整数是：");
      Serial.println(convertedNumber);
      // 重置变量，为下一次输入做准备
      bufferIndex = 0;
      inputComplete = false;
    }
  }
  digitalWrite(MOTOR_LEFT_D_PIN,0);
  analogWrite(MOTOR_LEFT_A_PIN,convertedNumber);
}
```

# 尝试用PWM的

```c
// 定义电机控制引脚
const int pwmPin = 9;  // PWM 引脚，可以是 3, 5, 6, 9, 10, 或 11 中的任何一个
const int directionPin1 = 8;  // 控制电机方向的一个引脚
const int directionPin2 = 7;  // 控制电机方向的另一个引脚

void setup() {
  // 设置 PWM 引脚为输出模式
  pinMode(pwmPin, OUTPUT);
  // 设置方向引脚为输出模式
  pinMode(directionPin1, OUTPUT);
  pinMode(directionPin2, OUTPUT);
  
  // 初始化电机停止状态
  digitalWrite(directionPin1, LOW);
  digitalWrite(directionPin2, LOW);
}

void loop() {
  // 示例：逐渐增加电机速度到最大值，然后逐渐减小到零
  for (int speed = 0; speed <= 255; speed++) {
    // 设置 PWM 值来控制速度
    analogWrite(pwmPin, speed);
    
    // 设置电机方向（例如，正向）
    digitalWrite(directionPin1, HIGH);
    digitalWrite(directionPin2, LOW);
    
    // 等待一段时间以观察速度变化
    delay(10);
  }
  
  for (int speed = 255; speed >= 0; speed--) {
    // 设置 PWM 值来控制速度
    analogWrite(pwmPin, speed);
    
    // 保持电机方向不变
    digitalWrite(directionPin1, HIGH);
    digitalWrite(directionPin2, LOW);
    
    // 等待一段时间以观察速度变化
    delay(10);
  }
  
  // 可选：在循环结束时停止电机
  digitalWrite(pwmPin, LOW);
  digitalWrite(directionPin1, LOW);
  digitalWrite(directionPin2, LOW);
  
  // 等待一段时间再重复循环
  delay(2000);
}
```

# 尝试用遥控器控制
```c
#include<Arduino.h>
#include <PS2X_lib.h>  // 引入 PS2 控制器库
#include"configuration.h"
PS2X ps2x;  // 创建 PS2 控制器对象

void setup() {
  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(SENSOR_3_PIN, INPUT);

  pinMode(MOTOR_LEFT_A_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_D_PIN, OUTPUT);


  pinMode(MOTOR_RIGHT_A_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_D_PIN, OUTPUT);    
  

  Serial.begin(9600);  // 初始化串口通信
  int maxRetries = 5;  // 最大重试次数
  int retryDelay = 1000;  // 每次重试的间隔时间（毫秒）
  int error = -1;  // 初始化错误状态
  int attempt = 0;  // 当前尝试次数

  while (attempt < maxRetries) {
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
    if (error == 0) {
      Serial.println("PS2 Controller initialized successfully.");
      break;  // 成功初始化，退出循环
    } else {
      attempt++;
      Serial.print("Initialization failed. Attempt ");
      Serial.print(attempt);
      Serial.print(" of ");
      Serial.println(maxRetries);
      delay(retryDelay);  // 等待后重试
    }
  }

  if (error != 0) {
    Serial.println("Failed to initialize PS2 controller after maximum retries.");
    while (1);  // 初始化彻底失败，停止程序
  }
}


int convertedNumber=0;
int tmp=0;

void loop() {
 ps2x.read_gamepad();  // 读取 PS2 手柄的状态

 // 判断按钮状态并输出
 if (ps2x.Button(PSB_TRIANGLE)) {
   Serial.println("Triangle button pressed.");
 }
 if (ps2x.Button(PSB_CIRCLE)) {
   Serial.println("Circle button pressed.");
 }

 // 输出摇杆值
 int leftX = ps2x.Analog(PSS_LX);  // 左摇杆 X 轴
 int leftY = ps2x.Analog(PSS_LY);  // 左摇杆 Y 轴
 Serial.print("Left X: ");
 Serial.print(leftX);
 Serial.print(" Left Y: ");
 Serial.println(leftY);  
 convertedNumber=leftY;
  
 if(convertedNumber>125){
   analogWrite(MOTOR_LEFT_D_PIN,(convertedNumber-125)*2);
   analogWrite(MOTOR_LEFT_A_PIN,0);
 }else{
   analogWrite(MOTOR_LEFT_D_PIN,0);
   analogWrite(MOTOR_LEFT_A_PIN,(125-convertedNumber)*2);    
 }

 if(convertedNumber>127){
   tmp=convertedNumber-127;
   analogWrite(MOTOR_RIGHT_D_PIN,tmp);
   analogWrite(MOTOR_RIGHT_A_PIN,0);
  }else{
    tmp=127-convertedNumber;
    analogWrite(MOTOR_RIGHT_D_PIN,0);
    analogWrite(MOTOR_RIGHT_A_PIN,(127-convertedNumber)*2);    
  }
 delay(100);  // 延时，避免输出过快
}

```
思考，由于映射关系，知道$0<125-convertedNumber<125$，需要调整到$0~255$。
```c
 if(convertedNumber>127){
   tmp=convertedNumber-127;
   tmp=tmp*2;
   tmp=constrain(tmp,0,255);
   analogWrite(MOTOR_RIGHT_D_PIN,tmp);
   analogWrite(MOTOR_RIGHT_A_PIN,0);
  }else{
    tmp=127-convertedNumber;
    tmp=tmp*2;
    tmp=constrain(tmp,0,255);    
    analogWrite(MOTOR_RIGHT_D_PIN,0);
    analogWrite(MOTOR_RIGHT_A_PIN,tmp);    
  }
  Serial.println(tmp);
 delay(100);  // 延时，避免输出过快
}
```
# 创建电机对象

```c
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
```

源文件

```c
#include "motor.h"
#include"configuration.h"
// 创建电机实例
Motor rightMotor(MOTOR_RIGHT_D_PIN, MOTOR_RIGHT_A_PIN);
Motor leftMotor(MOTOR_LEFT_D_PIN,MOTOR_LEFT_A_PIN);
void setup() {
    // 初始化电机
    rightMotor.begin();
    Serial.begin(9600);  // 启动串口调试，查看输出
}

void loop() {
    // 电机正转，速度 200（范围 0 到 255）
    rightMotor.setSpeed(200);
    Serial.println("Motor is rotating forward at speed 200.");
    delay(2000);  // 等待 2 秒

    // 电机反转，速度 150（范围 -255 到 0）
    rightMotor.setSpeed(-150);
    Serial.println("Motor is rotating backward at speed 150.");
    delay(2000);  // 等待 2 秒

    // 电机停止，速度 0
    rightMotor.setSpeed(0);
    Serial.println("Motor has stopped.");
    delay(2000);  // 等待 2 秒
}
```

使用示例

```c
#include "motor.h"
#include"configuration.h"
// 创建电机实例
Motor rightMotor(MOTOR_RIGHT_D_PIN, MOTOR_RIGHT_A_PIN);
Motor leftMotor(MOTOR_LEFT_D_PIN,MOTOR_LEFT_A_PIN);
void setup() {
    // 初始化电机
    rightMotor.begin();
    Serial.begin(9600);  // 启动串口调试，查看输出
}

void loop() {
    // 电机正转，速度 200（范围 0 到 255）
    rightMotor.setSpeed(200);
    Serial.println("Motor is rotating forward at speed 200.");
    delay(2000);  // 等待 2 秒

    // 电机反转，速度 150（范围 -255 到 0）
    rightMotor.setSpeed(-150);
    Serial.println("Motor is rotating backward at speed 150.");
    delay(2000);  // 等待 2 秒

    // 电机停止，速度 0
    rightMotor.setSpeed(0);
    Serial.println("Motor has stopped.");
    delay(2000);  // 等待 2 秒
}
```
# 创建遥控机器示例
`ps2_controller.h`文件当中的内容
```c++
#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include <PS2X_lib.h>  // 引入PS2X库
#include <Arduino.h>
#include "ps2_controller_state.h"  // 引入状态类
// 宏定义：控制器连接引脚
#define PS2_DAT 12
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 13

class PS2Controller {
public:
    PS2ControllerState state;  // 控制器状态

    // 构造函数，接受最大重试次数和重试延迟
    PS2Controller(int maxRetries = 5, int retryDelay = 1000);
    
    // 封装初始化过程
    bool init();
    
    // 读取按钮和摇杆输入（你可以在这里添加更多的功能）
    void update(bool show=false);
    
private:
    int _maxRetries;  // 最大重试次数
    int _retryDelay;  // 每次重试的间隔时间
    PS2X ps2x;  // PS2 控制器对象，作为成员变量
};

#endif  // PS2_CONTROLLER_H
```
`ps2_controller.cpp`
文件当中的内容
```c++
#include "ps2_controller.h"
// 初始化构造函数，接受最大重试次数和重试延迟
PS2Controller::PS2Controller(int maxRetries, int retryDelay) {
    _maxRetries = maxRetries;
    _retryDelay = retryDelay;
}

// 初始化PS2控制器
bool PS2Controller::init() {
    int error = -1;
    int attempt = 0;

    while (attempt < _maxRetries) {
        error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
        if (error == 0) {
            Serial.println("PS2 Controller initialized successfully.");
            return true;  // 成功初始化，返回true
        } else {
            attempt++;
            Serial.print("Initialization failed. Attempt ");
            Serial.print(attempt);
            Serial.print(" of ");
            Serial.println(_maxRetries);
            delay(_retryDelay);  // 等待后重试
        }
    }

    Serial.println("Failed to initialize PS2 controller after maximum retries.");
    return false;  // 初始化失败，返回false
}

// 读取PS2控制器的输入（例如按钮和摇杆状态）
void PS2Controller::update(bool show=false) {
    ps2x.read_gamepad();  // 读取控制器状态

// 更新按钮A状态
    state.buttonA = ps2x.Button(PSB_GREEN);
    // 更新摇杆X和Y值
    state.analogX = ps2x.Analog(PSS_LX);
    state.analogY = ps2x.Analog(PSS_LY);
    if(show==true){
        Serial.print("analogX");
        Serial.println(state.analogX);
        Serial.print("analogY");
        Serial.println(state.analogY);        
    }
}

```
测试主程序
```c++
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

```