#ifndef __PID_H__
#define __PID_H__

enum PID_Mode                           //PID模式选择
{
	PID_Position = 0,                   //普通PID
}

typedef struct
{
	//需要用户初始化配置
	uint8_t Mode;                       //模式选择
	float Kp;                           //PID3个参数
	float Ki;
	float Kd;
	float MaxOut;                       //最大输出
	float MaxIout;                      //最大积分输出
	float Target;                       //期望输出

	//不需要用户初始化配置
	float Out;
	float Pout;
	float Iout;
	float Dout;
	float Error[1];                     //误差项，0代表最新，1代表上一次
}PID_type_def;

void PID_Init(void);
float PID_Calc(PID_type_def*pid, float Current);
#endif

