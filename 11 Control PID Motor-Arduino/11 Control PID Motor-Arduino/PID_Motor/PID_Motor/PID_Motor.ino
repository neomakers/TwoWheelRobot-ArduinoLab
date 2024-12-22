double samplingPeriod = 100; // Time for encoder readings
volatile unsigned long previousTime = 0;
static volatile unsigned long lastDebounceTime = 0; // Time for debounce

double currentRPM = 0;
double filteredRPM = currentRPM;
double alpha = 0.08; // Exponential moving average filter

volatile int pulseCount = 0; // Number of pulses read by Arduino
int slotsCount = 20; // Number of slots

unsigned long currentTime = 0;
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
double sampleTime = 0.1;      // Ts

double pidOutput = 0;

void setup() 
{
  Serial.begin(9600);
  attachInterrupt(0, encoderInterrupt, RISING); // Read pulses using interrupt
  pinMode(pwmPin, OUTPUT);

  previousTime = 0;
}

void loop() 
{
  if (millis() - previousTime >= samplingPeriod) 
  {
    currentRPM = (pulseCount * 60000.0) / ((millis() - previousTime) * slotsCount);
    filteredRPM = alpha * currentRPM + (1.0 - alpha) * filteredRPM; // Exponential moving average filter
    previousTime = millis();
    pulseCount = 0;
    
    pidOutput = calculatePID();
    analogWrite(pwmPin, int(pidOutput));
    
    Serial.print(pidOutput);     // Control variable (CV)
    Serial.print(",");
    Serial.print(setPoint);      // Set Point (SP)
    Serial.print(",");
    Serial.println(filteredRPM); // Process Variable (PV)
  }

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
  {
    currentError = setPoint - filteredRPM;
    controlValue = previousControlValue + (kp + (kd / sampleTime)) * currentError +
                   (-kp + ki * sampleTime - (2 * kd / sampleTime)) * previousError +
                   (kd / sampleTime) * twoStepBackError; 

    previousControlValue = controlValue;
    twoStepBackError = previousError; 
    previousError = currentError;
    
    if (controlValue >= 255) {
      controlValue = 255;    
    }
    if (controlValue < 0) {
      controlValue = 0;
    }
    return controlValue;
  }
}
