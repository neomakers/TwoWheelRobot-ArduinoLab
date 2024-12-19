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