#include <TimerOne.h> // 使用TimerOne库，需要安装

double samplingPeriod = 100; // Time for encoder readings
volatile unsigned long previousTime = 0;
static volatile unsigned long lastDebounceTime = 0; // Time for debounce

double currentRPM = 0;
double filteredRPM = currentRPM;
double alpha = 0.08; // Exponential moving average filter

volatile int pulseCount = 0; // Number of pulses read by Arduino
int slotsCount = 20; // Number of slots

int pwmPin = 3;

// PID constants
double kp = 1;
double ki = 1;
double kd = 0.01;

// PID variables
double setPoint = 100.0; // Target RPM (Set Point)

double currentError = 0;     // e(n)
double previousError = 0;    // e(n-1)
double twoStepBackError = 0; // e(n-2)

double controlValue = 0;      // c(n)
double previousControlValue = 0; // c(n-1)
double sampleTime = 0.1;      // Ts (100ms)

double pidOutput = 0;
void encoderInterrupt();
void timerISR();
void setup() 
{
  Serial.begin(9600);
  attachInterrupt(0, encoderInterrupt, RISING); // Read pulses using interrupt
  pinMode(pwmPin, OUTPUT);

  // 使用Timer1设置定时中断，采样周期为 100ms
  Timer1.initialize(100000); // 定时器周期为 100,000 微秒 (100 ms)
  Timer1.attachInterrupt(timerISR); // 绑定定时器中断函数
}

void loop() 
{
  // 更新设定点 (Set Point) 的增减
  if (digitalRead(4)) // Increment Set Point
  {
    setPoint = setPoint + 10;
    delay(500);
  }

  if (digitalRead(5)) // Decrement Set Point
  {
    setPoint = setPoint - 10;
    delay(500);
  }
}

void encoderInterrupt()
{
  if (digitalRead(2) && (micros() - lastDebounceTime >= 500)) // Debounce mechanism
  {
    lastDebounceTime = micros();
    pulseCount++;  
  }  
}



double calculatePID() {
  currentError = setPoint - filteredRPM;

  // PID 差分方程
  controlValue = previousControlValue + 
                 (kp + (kd / sampleTime)) * currentError +
                 (-kp + ki * sampleTime - (2 * kd / sampleTime)) * previousError +
                 (kd / sampleTime) * twoStepBackError;

  // 更新历史变量
  previousControlValue = controlValue;
  twoStepBackError = previousError;
  previousError = currentError;

  // 限制 PID 输出范围
  if (controlValue >= 255) {
    controlValue = 255;
  }
  if (controlValue < 0) {
    controlValue = 0;
  }
  return controlValue;
}



// 定时器中断服务函数 (每 100ms 执行一次)
void timerISR() {
  // 计算当前 RPM
  currentRPM = (pulseCount * 60000.0) / (samplingPeriod * slotsCount);
  filteredRPM = alpha * currentRPM + (1.0 - alpha) * filteredRPM; // Exponential moving average filter
  pulseCount = 0;

  // 计算 PID 输出
  pidOutput = calculatePID();
  analogWrite(pwmPin, int(pidOutput));

  // 打印数据用于调试
  Serial.print(pidOutput);     // Control variable (CV)
  Serial.print(",");
  Serial.print(setPoint);      // Set Point (SP)
  Serial.print(",");
  Serial.println(filteredRPM); // Process Variable (PV)
}
   