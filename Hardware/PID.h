#ifndef __PID_H
#define __PID_H

#include "ti_msp_dl_config.h"


//PID结构体
typedef struct {
	float Target;
	float Actual;
	float Out;
	
	float Err0;
	float Err1;
	float ErrInt;
	
	float ErrIntThreshold;
	
	float Kp;
	float Ki;
	float Kd;
	
	float OutMax;
	float OutMin;
} PID_t;

//PID计算函数
void PID_Calculate(PID_t *pid);



#endif
