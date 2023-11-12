#include "PID.H"

void LimitMax(float Input, float Max)           //限幅
{                          
	if (Input > Max)       
	{                      
		Input = Max;       
	}                      
	else if (Input < -Max) 
	{                      
		Input = -Max;      
	}                      
}

/**
  * @brief          pid初始化
  * @param          pid: PID结构数据指针
  * @retval         无
  */
void PID_Init(PID_type_def*pid)
{
	pid->Error[0] = pid->Error[1] = pid->Pout = pid->Iout = pid->Dout = pid->Out = 0.0f;
}

/**
  * @brief          pid计算
  * @param          pid: PID结构数据指针
  * @param          Current: 电机反馈的当前输出
  * @retval         pid输出
  */
float PID_Calc(PID_type_def*pid, float Current)
{
	if (pid == NULL)
    {
        return 0.0f;
    }
	
	pid->Error[1] = pid->Error[0];
	pid->Error[0] = pid->Target - Current;               //误差项= 期望输出 - 实际输出
	
	if(pid->Mode == PID_Positin)
	{
		pid->Pout = pid->Kp * pid->Error[0];
		pid->Iout += pid->Ki * pid->Error[0];
		pid->Dout = pid->Kd * (pid->Error[0] - pid->Error[1]);
		LimitMax(pid->Iout, pid->MaxIout);
		pid->Out = pid->Pout + pid->Iout + pid->Dout;
		LimitMax(pid->Out, pid->MaxOut);
	}
	return pid->Out;
}


