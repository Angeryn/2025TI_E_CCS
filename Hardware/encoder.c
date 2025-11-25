#include "encoder.h"
#include "led.h"
uint32_t gpio_interrup1,gpio_interrup2;

// 定义四个编码器的计数值和采样值
int16_t Encoder_Count_A=1500;//让第一次的保护消失
int16_t Encoder_Count_B=1500;

//上一次编码器传入的脉冲值
int16_t Encoder_Count_A0=1500;//同上
int16_t Encoder_Count_B0=1500;

//速度值
int16_t Val_A;
int16_t Val_B;
/*******************************************************
�������ܣ��ⲿ�ж�ģ���������ź�
���ں�������
����  ֵ����
***********************************************************/
void GROUP1_IRQHandler(void)
{
	//��ȡ�ж��ź�
    gpio_interrup1 = DL_GPIO_getEnabledInterruptStatus(ENCODERA_PORT,ENCODERA_E1A_PIN|ENCODERA_E1B_PIN);
    gpio_interrup2 = DL_GPIO_getEnabledInterruptStatus(ENCODERB_PORT,ENCODERB_E2A_PIN|ENCODERB_E2B_PIN);
    
    
	//encoderA
	if((gpio_interrup1 & ENCODERA_E1A_PIN)==ENCODERA_E1A_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERA_PORT,ENCODERA_E1B_PIN))
		{
			Encoder_Count_A--;
		}
		else
		{
			Encoder_Count_A++;
		}
	}
	else if((gpio_interrup1 & ENCODERA_E1B_PIN)==ENCODERA_E1B_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERA_PORT,ENCODERA_E1A_PIN))
		{
			Encoder_Count_A++;
		}
		else
		{
			Encoder_Count_A--;
		}
	}
	
	//encoderB
	if((gpio_interrup2 & ENCODERB_E2A_PIN)==ENCODERB_E2A_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERB_PORT,ENCODERB_E2B_PIN))
		{
			Encoder_Count_B++;
		}
		else
		{
			Encoder_Count_B--;
		}
	}
	else if((gpio_interrup2 & ENCODERB_E2B_PIN)==ENCODERB_E2B_PIN)
	{
		if(!DL_GPIO_readPins(ENCODERB_PORT,ENCODERB_E2A_PIN))
		{
			Encoder_Count_B--;
		}                 
		else              
		{                 
			Encoder_Count_B++;
		}
	}


	DL_GPIO_clearInterruptStatus(ENCODERA_PORT,ENCODERA_E1A_PIN|ENCODERA_E1B_PIN);
	DL_GPIO_clearInterruptStatus(ENCODERB_PORT,ENCODERB_E2A_PIN|ENCODERB_E2B_PIN);
}
/*编码器读当前位置*/
int16_t Encoder_A_Location(void)
{
    int16_t Temp = Encoder_Count_A;
    return Temp;
}

int16_t Encoder_B_Location(void)
{
    int16_t Temp = Encoder_Count_B;
    return Temp;
}


/*编码器读当前速度*/
int16_t Encoder_A_Val(void)
{
    Val_A = (int16_t)((uint16_t)Encoder_Count_A-(uint16_t)Encoder_Count_A0);
	Encoder_Count_A0 = Encoder_Count_A;
    return Val_A;
}

int16_t Encoder_B_Val(void)
{
    Val_B = (int16_t)((uint16_t)Encoder_Count_B-(uint16_t)Encoder_Count_B0);
	Encoder_Count_B0 = Encoder_Count_B;
    return Val_B;
}
