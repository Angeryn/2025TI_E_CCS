#include "ti_msp_dl_config.h"
#include "PID.h"
#include "math.h"
#include "motor.h"
#include "encoder.h"


/*定位置模式PID参数
 *还需在主函数中补充的参数：Target,Actual,Threshold(可暂时不补充)
 */
PID_t LocationPID_A={
	.Kp = 3.13,
	.Ki = 0.001,
	.Kd = 2,
	.OutMax = 1000,
	.OutMin = -1000,
};

PID_t LocationPID_B={
	.Kp = 3.13,
	.Ki = 0.001,
	.Kd = 2,
	.OutMax = 1000,
	.OutMin = -1000,
};

/*定速度模式PID参数
 *还需在主函数中补充的参数：Target,Actual,Threshold(可暂时不补充)
 *注：积分分离阈值Threshold可以
 */
PID_t SpeedPID_A = {
	.Kp = 7.3,
	.Ki = 2.9,
	.Kd = 0,
	.OutMax = 1000,
	.OutMin = -1000,
	.ErrIntThreshold = 20
};

PID_t SpeedPID_B = {
	.Kp = 7.3,
	.Ki = 2.9,
	.Kd = 0,
	.OutMax = 1000,
	.OutMin = -1000,
	.ErrIntThreshold = 20
};


/*串级PID位置速度模式参数
 *串级PID最好用单独一套位置速度参数，不过速度参数可以暂时凑合用
 */
PID_t CascadePID_Location_A={
	.Kp = 0.5,
	.Ki = 0.001,
	.Kd = 2,
	.OutMax = 1000,
	.OutMin = -1000,
};

PID_t CascadePID_Location_B={
	.Kp = 0.5,
	.Ki = 0.001,
	.Kd = 2,
	.OutMax = 1000,
	.OutMin = -1000,
};



//速度限制函数——与串级PID联用
void Limit_Speed(PID_t *position_pid,PID_t *speed_pid,float speed_target)
{
	//限制速度，即当位置环计算出的PWM值大于目标速度值时，以限制速度为目标(串级PID控制速度核心)
	if(position_pid->Out > speed_target)	speed_pid->Target = speed_target;
	if(position_pid->Out <-speed_target)	speed_pid->Target =-speed_target;
	
}


//封装电机位置调控函数
void Motor_PIDLocation(void)
{
	//写入当前位置
	LocationPID_A.Actual = Encoder_A_Location();
	LocationPID_B.Actual = Encoder_B_Location();

	//PID计算
	PID_Calculate(&LocationPID_A);
	PID_Calculate(&LocationPID_B);
	
	//电机调速
    Set_PWM(LocationPID_A.Out,LocationPID_B.Out);
	
}

//封装电机速度调控函数
void Motor_PIDSpeed(void)
{
	//写入当前速度
	SpeedPID_A.Actual = Encoder_A_Val();
	SpeedPID_B.Actual = Encoder_B_Val();

	//PID计算
	PID_Calculate(&SpeedPID_A);
	PID_Calculate(&SpeedPID_B);
	
	//电机调速
    Set_PWM(SpeedPID_A.Out,SpeedPID_B.Out);
	
}

// 位置速度串级 PID ,注意速度环目标值是在此函数中输入的
void Cascade_PIDPosition(float speed_target)
{
	//写入当前位置
	CascadePID_Location_A.Actual = Encoder_A_Location();
	CascadePID_Location_B.Actual = Encoder_B_Location();
	
	
	//写入当前速度
	SpeedPID_A.Actual = Encoder_A_Val();
	SpeedPID_B.Actual = Encoder_B_Val();
	
	
    // 先计算位置环（外环）
    PID_Calculate(&CascadePID_Location_A);
	PID_Calculate(&CascadePID_Location_B);
	
	
	//将位置环输出值作为速度环输入
	SpeedPID_A.Target = CascadePID_Location_A.Out;
	SpeedPID_B.Target = CascadePID_Location_B.Out;
	
	
	//限制速度，即当位置环计算出的PWM值大于目标速度值时，以限制速度为目标(串级PID控制速度核心)
	Limit_Speed(&CascadePID_Location_A,&SpeedPID_A,speed_target);
	Limit_Speed(&CascadePID_Location_B,&SpeedPID_B,speed_target);
	
	
    // 计算速度环（内环）
    PID_Calculate(&SpeedPID_A);
	PID_Calculate(&SpeedPID_B);
	
	

	//电机调速,返回速度环的输出作为最终控制量
    Set_PWM(SpeedPID_A.Out,SpeedPID_B.Out);
}

/*电机走固定距离(四轮联动)
 *Mode:传入PID模式控制变量地址，以改变PID模式
 *Target:写入四个轮各自的目标位置
 **/
void PID_PositionMode(uint8_t *Mode,float TargetA,float TargetB)
{
	//模式选择变量第一位置1，意味着进入单位置控制模式
	Mode[0]=1;
	
	//写入目标位置
	LocationPID_A.Target = TargetA;
	LocationPID_B.Target = TargetB;
	
	
}

/*电机走固定速度(四轮联动)
 *Mode:传入PID模式控制变量地址，以改变PID模式
 *Target:写入四个轮各自的目标速度
 **/
void PID_SpeedMode(uint8_t *Mode,float TargetA,float TargetB)
{
	//模式选择变量第二位置1，意味着进入单速度控制模式
	Mode[1]=1;
	
	//写入目标速度
	SpeedPID_A.Target = TargetA;
	SpeedPID_B.Target = TargetB;
	
	//因为速度控制模式往往是与传感器检测停止条件配合使用，故在此函数中不设置自动检测停止条件
}

/*串级PID定速度定位置控制
 *Mode:传入PID模式控制变量地址，以改变PID模式
 *TargetX:写入各轮目标位置，速度在更新函数里写一个固定的值就行
 */
 void PID_CascadePosition(uint8_t *Mode,float TargetA,float TargetB)
{
	//模式选择变量第三位置1，意味着进入速度位置串级控制模式
	Mode[2]=1;
	
	//写入目标速度
	CascadePID_Location_A.Target = TargetA;
	CascadePID_Location_B.Target = TargetB;
		
}

/*PID控制模式停止函数
 *Mode:传入PID模式控制变量地址，以改变PID模式
 *此函数可令任一种PID模式停止
 */
void PID_Stop(uint8_t *Mode)
{
	//退出速度PID模式
	Mode[0]=0;

	
	//目标速度置0
	SpeedPID_A.Target = 0;
	SpeedPID_B.Target = 0;
	
	
	//速度存储变量和位置存储变量清零,以防影响下一次速度控制
	Encoder_Count_A=0;
	Encoder_Count_B=0;
	
	Encoder_Count_A0=0;
	Encoder_Count_B0=0;
	
	Val_A=0;
	Val_B=0;

	//一定记得停止时也要把电机强行关机，否则在退出循环时可能还保留了一个微小的PWM值
	
	Set_PWM(0,0);
}