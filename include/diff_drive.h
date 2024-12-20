#ifndef DIFF_DRIVE_H
#define DIFF_DRIVE_H

class DifferentialDrive {
public:
    // 构造函数，初始化轮距
    DifferentialDrive(float wheelDistance);

    // 计算左右轮速度
    void calculateWheelSpeeds(float v, float omega);

private:
    float d;  // 轮距（单位：米）
};

#endif
