#include "Gray_LOG.h"

int8_t FCD=0,FCD_0=0;//正常巡线
int8_t FCD_T=0,FCD_T_0;//转弯巡线
uint8_t Gray[7]={0};

void Get_Gray(void)
{
	Gray[0]=H1;
	Gray[1]=H2;
	Gray[2]=H3;
	Gray[3]=H4;
	Gray[4]=H5;
	Gray[5]=H6;
	Gray[6]=H7;
}

int8_t  Grayscale_get_err(uint8_t *Status)
{

    //去掉三路为0以及没有0的数据，即只考虑为1路压线和两路压线的情况
    //取出每位数据
	Get_Gray();

			for(int j=1;j<=2;j++)//左单->
			{
				if(Gray[j]==1)//注意根据具体情况修改成0/1
				{
					FCD = 2*j-6;//2*(-(5-(i+1)))+1将i从0、1、2、3转化为F-7、F-5、F-3、F-1
					break;//找到0后直接退出提高运行效率
				}
			}

			for(int k=1;k<=2;k++)//左双->
			{
				if(Gray[k]==1&&Gray[k+1]==1)
				{
					FCD = 2*k-5;//-2*(4-(i+1))将i、i+1从0\1、1\2、2\3转化为F-6、F-4、F-2
					break;//找到0后直接退出提高运行效率
				}
				
			}

			for(int n=3;n<=4;n++)//右双->
			{
				if(Gray[n]==1&&Gray[n+1]==1)
				{
					FCD = 2*n-5;//-2*(4-(i+1))将i、i+1从0\1、1\2、2\3转化为F-6、F-4、F-2
					break;//找到0后直接退出提高运行效率
				}
			}

			for(int i=4;i<=5;i++)//右单->
			{
				if(Gray[i]==1)//注意根据具体情况修改成0/1
				{
					FCD = 2*i-6;//2*(-(5-(i+1)))+1将i从0、1、2、3转化为F-7、F-5、F-3、F-1
					break;//找到0后直接退出提高运行效率
				}
				
			}

	//根据转弯标志位返回误差值
	if(Status[0]==1)//如果检测到进弯
	{
		FCD_T=FCD-4;//从-6~6转换为-10~2
		FCD_T_0=FCD_T;//记录上一次偏差值
		FCD_T=0;//重置这一次的值
		return (FCD_T+FCD_T_0)/2;
	}
	else 
	{
		FCD_0=FCD;//放入上一次的值
		FCD=0;//重置这一次的值
		return (FCD+FCD_0)/2;
	}
	
	

	
	
}


