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
