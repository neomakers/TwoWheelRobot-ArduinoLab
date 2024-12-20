#ifndef PS2_CONTROLLER_STATE_H
#define PS2_CONTROLLER_STATE_H

class PS2ControllerState {
public:
    int analogX;  // 左摇杆的X轴值
    int analogY;  // 左摇杆的Y轴值
    bool buttonA; // 按钮A的状态

    // 默认构造函数，初始化状态
    PS2ControllerState() : analogX(0), analogY(0), buttonA(false) {}
};

#endif  // PS2_CONTROLLER_STATE_H
