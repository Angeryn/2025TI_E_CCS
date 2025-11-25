#include "key.h"


/**************************************************************************
Function: Key scan
Input   : Double click the waiting time
Output  : 0��No action��1��click��2��Double click
�������ܣ�����ɨ��
���ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬ 0���޶��� 1������ 2��˫��
**************************************************************************/
// u8 click_N_Double (u8 time)
// {
//     static  u8 flag_key,count_key,double_key=0;
//     static  u16 count_single,Forever_count;
//     if(DL_GPIO_readPins(KEY_=PORT,KEY_KEY7_PIN)>0)  Forever_count++;   //������־λδ��1
//     else        Forever_count0;
//     if((DL_GPIO_readPins(KEY_PORT,KEY_KEY7_PIN)>0)&&0==flag_key)     flag_key=1; //��һ�ΰ���
//     if(0==count_key)
//     {
//             if(flag_key==1)
//             {
//                 double_key++;
//                 count_key=1;            //���ǰ���һ��
//             }
//             if(double_key==3)
//             {                                       //��������
//                 double_key=0;
//                 count_single=0;
//                 return 2;                   //˫��ִ�е�ָ��
//             }
//     }
//     if(0==DL_GPIO_readPins(KEY_PORT,KEY_key_PIN))          flag_key=0,count_key=0;
//     if(1==double_key)
//     {
//         count_single++;
//         if(count_single>time&&Forever_count<time)
//         {
//             double_key=0;
//             count_single=0; //��ʱ������Ϊ˫��
// 			return 1;//����ִ�е�ָ��
//         }
//         if(Forever_count>time)
//         {
//             double_key=0;
//             count_single=0;
//         }
//     }
//     return 0;
// }
// /**************************************************************************
// Function: Long press detection
// Input   : none
// Output  : 0��No action��1��Long press for 2 seconds��
// �������ܣ���������
// ���ڲ�������
// ����  ֵ������״̬ 0���޶��� 1������2s
// **************************************************************************/
// u8 Long_Press(void)
// {
//         static u16 Long_Press_count,Long_Press;
//       if(Long_Press==0&&KEY==0)  Long_Press_count++;   //������־λδ��1
//     else                       Long_Press_count=0;
//         if(Long_Press_count>200)        //10msɨ��һ��
//       {
//             Long_Press=1;
//             Long_Press_count=0;
//             return 1;
//         }
//         if(Long_Press==1)     //������־λ��1
//         {
//             Long_Press=0;
//         }
//         return 0;
// }


// void Key(void)
// {
// 	u8 tmp,tmp2;
// 	tmp=click_N_Double(50);
// 	if(tmp==1)
// 	{
// 		Flag_Stop=!Flag_Stop;
// 	}		//��������С������ͣ
// }

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (KEY7 == 0)
	{
		delay_ms(20);
		while (KEY7 == 0);
		delay_ms(20);
		KeyNum = 1;
	}
	if (KEY8 == 0)
	{
		delay_ms(20);
		while (KEY8 == 0);
		delay_ms(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}

