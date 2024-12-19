#include <PS2X_lib.h>  // 引入 PS2 控制器库
#include"configuration.h"
PS2X ps2x;  // 创建 PS2 控制器对象

void setup() {
   pinMode(SENSOR_1_PIN, INPUT);
   pinMode(SENSOR_2_PIN, INPUT);
   pinMode(SENSOR_3_PIN, INPUT);

   pinMode(MOTOR_LEFT_A_PIN, OUTPUT);
   pinMode(MOTOR_LEFT_D_PIN, OUTPUT);
   digitalWrite(MOTOR_LEFT_EN,HIGH);


   pinMode(MOTOR_RIGHT_A_PIN, OUTPUT);
   pinMode(MOTOR_RIGHT_D_PIN, OUTPUT);    digitalWrite(MOTOR_LEFT_EN,HIGH);

   Serial.begin(9600);  // 初始化串口通信
   int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);  // 配置 PS2 控制器的引脚

   if (error == 0) {
     Serial.println("PS2 Controller initialized successfully.");
   } else {
     Serial.println("Error initializing PS2 controller.");
     while (1);  // 如果初始化失败，停止程序
   }
}
int convertedNumber=0;
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
   analogWrite(MOTOR_LEFT_D_PIN,convertedNumber-125);
   analogWrite(MOTOR_LEFT_A_PIN,0);
 }else{
   analogWrite(MOTOR_LEFT_D_PIN,0);
   analogWrite(MOTOR_LEFT_A_PIN,125-convertedNumber);    
 }

 if(convertedNumber>125){
   analogWrite(MOTOR_RIGHT_D_PIN,convertedNumber-125);
   analogWrite(MOTOR_RIGHT_A_PIN,0);
}else{
  analogWrite(MOTOR_RIGHT_D_PIN,0);
  analogWrite(MOTOR_RIGHT_A_PIN,125-convertedNumber);    
}
 delay(100);  // 延时，避免输出过快
}