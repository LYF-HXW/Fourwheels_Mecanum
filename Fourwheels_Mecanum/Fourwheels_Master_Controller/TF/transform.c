#include <math.h>
#include "mydata.h"
#include "transform.h"
#include "timer.h"

/*********************
全局速度转换为单电机速度
*********************/
void TF_Global_To_Single(double g_e_v[3],double *motor,double a)//a为机器人坐标系与世界坐标系的夹角
{
 *motor=radius*g_e_v[2] - g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2) + g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2);
 *(motor+1)=radius*g_e_v[2] - g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2) - g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2);
 *(motor+2)=radius*g_e_v[2] + g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2) - g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2);
 *(motor+3)=radius*g_e_v[2] + g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2) + g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2);
}
/*********************
机器人速度转换为单电机速度
*********************/
void TF_Robot_To_Single(double g_e_v[3],double *motor)
{
 *motor=radius * g_e_v[2] - g_e_v[0] * pow(2.0,0.5)/2  + g_e_v[1] * pow(2.0,0.5)/2 ;
 *(motor+1)=radius * g_e_v[2] - g_e_v[0] * pow(2.0,0.5)/2 - g_e_v[1] * pow(2.0,0.5)/2;
 *(motor+2)=radius * g_e_v[2] + g_e_v[0] * pow(2.0,0.5)/2 - g_e_v[1] * pow(2.0,0.5)/2;
 *(motor+3)=radius * g_e_v[2] + g_e_v[0] * pow(2.0,0.5)/2 + g_e_v[1] * pow(2.0,0.5)/2;
}
/******************
设置世界坐标系速度函数
******************/
void Set_Speed_Global_To_Single()
{
	double g_e_v[3],motor[4];
	g_e_v[0]=basketballbot.globel_expected_speed.x;
	g_e_v[1]=basketballbot.globel_expected_speed.y;
	g_e_v[2]=basketballbot.globel_expected_speed.z;
  TF_Global_To_Single(g_e_v,motor,basketballbot.real_position.z+(double)pi/2.0);
	basketballbot.single_expected_speed.M1=(motor[0]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
	basketballbot.single_expected_speed.M2=(motor[1]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
	basketballbot.single_expected_speed.M3=(motor[2]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
	basketballbot.single_expected_speed.M4=(motor[3]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
}
/******************
设置机器人坐标系速度函数
******************/
void Set_Speed_Robot_To_Single()
{
	double r_e_v[3],motor[4];
	r_e_v[0]=basketballbot.robot_expected_speed.x;
	r_e_v[1]=basketballbot.robot_expected_speed.y;
	r_e_v[2]=basketballbot.robot_expected_speed.z;
  TF_Robot_To_Single(r_e_v,motor);
	basketballbot.single_expected_speed.M1=(motor[0]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
	basketballbot.single_expected_speed.M2=(motor[1]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
	basketballbot.single_expected_speed.M3=(motor[2]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
	basketballbot.single_expected_speed.M4=(motor[3]/ wheel_R ) * ( 180/pi ) /6.0;// r/s
}
/********************************
两个编码器的单位时间增量数据转换为全局坐标的单位时间增量
*********************************/
void TF_Single_To_Global(double motor[2],double *g_e_v,double a)
{
	*g_e_v = motor[0] * cos(a) + motor[1] * sin(a);
	*(g_e_v+1) = - motor[1] * cos(a) + motor[1] * sin(a);
}
/********************
里程计算
********************/
void position_counter()
{
	static double ecoder1[2]={0,0},ecoder2[2]={0,0};
	double motor[2],position[2],w;
	double angle;
	uint16_t buffer=0;
	
	
	buffer = TIM_GetCounter(TIM2); 
	angle= (float)buffer*360.0/encoder_barrier;
  basketballbot.encoder_data.M1=(basketballbot.count1+angle/360)*diameter*pi;		 //得到实际的累计转动长度，单位cm
	//单位时间内编码器数据的差值
	ecoder1[1] = basketballbot.encoder_data.M1;
	motor[0] = ecoder1[1] - ecoder1[0];
	ecoder1[0] = ecoder1[1];
	
	buffer = TIM_GetCounter(TIM4); 
	angle= (float)buffer*360.0/encoder_barrier;
  basketballbot.encoder_data.M2=(basketballbot.count2+angle/360)*diameter*pi;		 //得到实际的累计转动长度，单位cm
	ecoder2[1] = basketballbot.encoder_data.M2;
	motor[1] = ecoder2[1] - ecoder2[0];
	ecoder2[0] = ecoder2[1];
	//角度计算          //！！！！问！！！！
	if(motor[1]!=0)
		w = atan(motor[0]/motor[1])+ basketballbot.real_position.z * ( pi/180 );//弧度
	else
		w = pi*0.5+ basketballbot.real_position.z * ( pi/180 );//弧度
	TF_Single_To_Global(motor,position,w);
	//里程计的X，Y解算
	basketballbot.real_position.x += position[0];//单位：cm
	basketballbot.real_position.y += position[1];//单位：cm
}
/***************
底盘控制
**************/
void move_base_control()
{
 switch (basketballbot.Control_ID)
 {
	 case Global: Set_Speed_Global_To_Single(); break;
	 case Robot:  Set_Speed_Robot_To_Single(); break;
 } 
 position_counter();
}
