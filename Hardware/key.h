#ifndef _KEY_H
#define _KEY_H
#include "ti_msp_dl_config.h"
#include "board.h"
#define KEY7  ((DL_GPIO_readPins(KEY_PORT,KEY_KEY7_PIN))>>7&&0x01)
#define KEY8  ((DL_GPIO_readPins(KEY_PORT,KEY_KEY8_PIN))>>8&&0x01)

uint8_t Key_GetNum(void);
// uint8_t click_N_Double (uint8_t time);  //��������ɨ����˫������ɨ��
// uint8_t click(void);               //��������ɨ��
// uint8_t Long_Press(void);           //����ɨ��
// void Key(void);

#endif
