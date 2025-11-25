#ifndef _ENCODER_H
#define _ENCODER_H
#include "ti_msp_dl_config.h"
#include "board.h"

//用于重新定义当前位置
extern int16_t Encoder_Count_A;
extern int16_t Encoder_Count_B;

extern int16_t Encoder_Count_A0;
extern int16_t Encoder_Count_B0;


extern int16_t Val_A;
extern int16_t Val_B;

//当前位置获取函数
int16_t Encoder_A_Location(void);
int16_t Encoder_B_Location(void);

//当前速度获取函数
int16_t Encoder_A_Val(void);
int16_t Encoder_B_Val(void);


#endif
