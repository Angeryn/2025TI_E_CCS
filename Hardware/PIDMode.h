#ifndef __PIDMODE_H
#define __PIDMODE_H

#include "PID.h"
#include "ti_msp_dl_config.h"



//结构体变量——位置控制
extern PID_t LocationPID_A;
extern PID_t LocationPID_B;


//结构体变量——速度控制
extern PID_t SpeedPID_A;
extern PID_t SpeedPID_B;

//结构体变量——串级控制位置环参数
extern PID_t CascadePID_Location_A;
extern PID_t CascadePID_Location_B;

//PID调控函数——位置调控
void Motor_PIDLocation(void);

//PID调控函数——速度调控
void Motor_PIDSpeed(void);

//PID调控函数——串级PID定位置定速度
void Cascade_PIDPosition(float speed_target);

//PID输入位置行驶固定距离函数
void PID_PositionMode(uint8_t *Mode,float TargetA,float TargetB);

//PID固定速度行驶函数
void PID_SpeedMode(uint8_t *Mode,float TargetA,float TargetB);

//PID串级定速度定位置
void PID_CascadePosition(uint8_t *Mode,float TargetA,float TargetB);

//PID模式停止函数
void PID_Stop(uint8_t *Mode);
#endif
