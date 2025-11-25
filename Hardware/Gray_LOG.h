#ifndef  __GRAY_LOG_
#define  __GRAY_LOG_

#include "ti_msp_dl_config.h"
#include "motor.h"

#define H1 ((DL_GPIO_readPins(GW_Adress_A_PORT,GW_Adress_A_PIN_1_PIN)>>12)&0x01)
#define H2 ((DL_GPIO_readPins(GW_Adress_B_PORT,GW_Adress_B_PIN_2_PIN)>>16)&0x01)
#define H3 ((DL_GPIO_readPins(GW_Adress_B_PORT,GW_Adress_B_PIN_3_PIN)>>17)&0x01)
#define H4 ((DL_GPIO_readPins(GW_Adress_A_PORT,GW_Adress_A_PIN_4_PIN)>>22)&0x01)
#define H5 ((DL_GPIO_readPins(GW_Adress_A_PORT,GW_Adress_A_PIN_5_PIN)>>24)&0x01)
#define H6 ((DL_GPIO_readPins(GW_Adress_A_PORT,GW_Adress_A_PIN_6_PIN)>>27)&0x01)
#define H7 ((DL_GPIO_readPins(GW_Adress_A_PORT,GW_Adress_A_PIN_7_PIN)>>9)&0x01)



extern int8_t FCD;

int8_t  Grayscale_get_err(uint8_t *Status);

#endif