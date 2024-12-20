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
