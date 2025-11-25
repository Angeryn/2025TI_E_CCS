#include "board.h"
int32_t encoderA_cnt,encoderB_cnt;
uint8_t oled_buffer0[32],oled_buffer1[32],oled_buffer2[32],oled_buffer3[32],oled_buffer4[32],oled_buffer5[32],oled_buffer6[32],oled_buffer7[32];
uint32_t temp=0;
uint16_t adc;
uint16_t Encoder_Get_flag=0;
uint16_t CNT=0;
uint8_t Mode[3]={0};
int16_t err=0;
int8_t Speed=0;
uint8_t Track_Status[2]={3,0};
int16_t Speed_L=0,Speed_R=0;
int16_t Speed_L0=0,Speed_R0=0;
int32_t Encoder_status_cnt=0;
uint8_t Circle_cnt=0;
uint8_t Circle=0;
uint8_t Target_Cicle=0;//圈数设定
uint16_t Turn_wait_delay_cnt=0;//左转前预备等待时间
uint16_t Turn_wait_delay=11;//左转前预备等待时间
uint16_t Turn_delay_cnt=0;//左转计数
uint16_t Turn_delay=20;//左转设定时间
uint8_t KeyNum;
uint8_t num=0,start=0;

int main(void)
{


	SYSCFG_DL_init();
	OLED_Init();

	NVIC_ClearPendingIRQ(ENCODERA_INT_IRQN);
  	NVIC_ClearPendingIRQ(ENCODERB_INT_IRQN);
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);

	NVIC_EnableIRQ(ENCODERA_INT_IRQN);
    NVIC_EnableIRQ(ENCODERB_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
	delay_ms(1000);

	
    while (1) 
    {
		if(Track_Status[0]==3)
		{
			KeyNum = Key_GetNum();
			if (KeyNum == 1)
			{
				Target_Cicle++;
			}
			if (KeyNum == 2)
			{
				Track_Status[0]=0;
			}
		}
		
		//记录上一次速度值
		Speed_L0 = Speed_L;
		Speed_R0 = Speed_R;

		err = Grayscale_get_err(Track_Status);
		

		//巡线速度赋值
		if(Track_Status[0]==1)//执行左转
		{
			Speed_L=0;
			Speed_R=20;
		}
		else if(Track_Status[0]==0)//正常巡线，标志位未置1
		{
			Speed_L=38+err*1.2;
			Speed_R=38-err*1.2;
		}
		else if((Track_Status[0]==2)&&(Turn_wait_delay_cnt<=Turn_wait_delay))//左转前预备20*40ms
		{
			Speed_L= 25;//20
			Speed_R= 25;//20
		}

		if(Track_Status[0]!=3)//决定电机是否启动
		{
			//检测是否达到设定圈数
			if(Circle<Target_Cicle)
			{
				PID_SpeedMode(Mode,Speed_R*0.6+Speed_R0*0.4,Speed_L*0.6+Speed_L0*0.4);
			}
			else 
			{
				PID_Stop(Mode);
				Track_Status[0]=3;//关闭电机
				Target_Cicle=0;
			}
		}
		

		
		

		memset(OLED_GRAM,0, 128*8*sizeof(u8)); //GRAM���㵫������ˢ�£���ֹ����
		
		
		



		
		

		sprintf((char *)oled_buffer3, "%-6d", Circle_cnt);		
		OLED_ShowString(20,10,oled_buffer3);

      	sprintf((char *)oled_buffer4, "%-6dd", Circle);		
		OLED_ShowString(40,10,oled_buffer4);

		sprintf((char *)oled_buffer5, "%-6dd", Encoder_Count_A);		
		OLED_ShowString(40,30,oled_buffer5);

		sprintf((char *)oled_buffer6, "%-6dd", Encoder_Count_B);		
		OLED_ShowString(80,30,oled_buffer6);
	
	
		// OLED_ShowNumber(0,0,H1,1,12);
		// OLED_ShowNumber(10,0,H2,1,12);
		// OLED_ShowNumber(20,0,H3,1,12);
		// OLED_ShowNumber(30,0,H4,1,12);
		// OLED_ShowNumber(0,10,H5,1,12);
		// OLED_ShowNumber(10,10,H6,1,12);
		// OLED_ShowNumber(20,10,H7,1,12);
		// OLED_ShowNumber(30,10,H8,1,12);

		OLED_Refresh_Gram();
		
    }
}



void TIMER_0_INST_IRQHandler(void)
{
	if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
	{
		
		if(DL_TIMER_IIDX_ZERO)
		{
			if((H1==1)&&(H2==1)&&(H3==1)&&(Track_Status[0]==0))//由状态0进入状态2
			{
				if(Encoder_Count_A+Encoder_Count_B>3000)//不满足行驶一段距离不准许进入转弯模
				{	
					Track_Status[0]=2;//灰度转弯标志位置2
					Circle_cnt++;//边数加1
					if(Circle_cnt>4)
					{
						Circle++;//圈数加1
						Circle_cnt=1;//边数计数重置
					}
					
				}
			}
			if(Track_Status[0]==2)//转弯等待模式
			{
				/*延时写法*/
				Turn_wait_delay_cnt++;
				if((Turn_wait_delay_cnt>Turn_wait_delay))//转弯等待结束
				{
					Turn_wait_delay_cnt=0;//等待计数重置
					Track_Status[0]=1;    //进入转弯模式
				}

			}
			if(Track_Status[0]==1)//转弯模式
			{
				Turn_delay_cnt++;
				if((Turn_delay_cnt > Turn_delay)&&(H3==1))//转弯结束
				{
					Turn_delay_cnt=0; //转弯计数重置
					Track_Status[0]=0;//进入正常模式
					Speed_L=38;//提前给电机赋值防止转弯后跑偏
					Speed_R=38;
					Encoder_Count_B=0;//编码器置0，加入保护
					Encoder_Count_A=0;
					Encoder_Count_B0=0;//编码器置0，加入保护
					Encoder_Count_A0=0;
				}
				
			}

			//PID位置调控
			if(Mode[0]==1)
			{
				Motor_PIDLocation();
			}
			//PID速度调控
			if(Mode[1]==1)
			{
				Motor_PIDSpeed();
			}
			//PID串级位置速度
			if(Mode[2]==1)
			{
				Cascade_PIDPosition(30);//注意里面是速度
			}

		}
		       
	}
}
