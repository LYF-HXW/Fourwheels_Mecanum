#include <math.h>
#include "mydata.h"
#include "transform.h"
#include "timer.h"

/*********************
ȫ���ٶ�ת��Ϊ������ٶ�
*********************/
void TF_Global_To_Single(double g_e_v[3],double *motor,double a)//aΪ����������ϵ����������ϵ�ļн�
{
 *motor=radius*g_e_v[2] - g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2) + g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2);
 *(motor+1)=radius*g_e_v[2] - g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2) - g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2);
 *(motor+2)=radius*g_e_v[2] + g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2) - g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2);
 *(motor+3)=radius*g_e_v[2] + g_e_v[0]*((pow(2.0,0.5)*cos(a))/2 - (pow(2.0,0.5)*sin(a))/2) + g_e_v[1]*((pow(2.0,0.5)*cos(a))/2 + (pow(2.0,0.5)*sin(a))/2);
}
/*********************
�������ٶ�ת��Ϊ������ٶ�
*********************/
void TF_Robot_To_Single(double g_e_v[3],double *motor)
{
 *motor=radius * g_e_v[2] - g_e_v[0] * pow(2.0,0.5)/2  + g_e_v[1] * pow(2.0,0.5)/2 ;
 *(motor+1)=radius * g_e_v[2] - g_e_v[0] * pow(2.0,0.5)/2 - g_e_v[1] * pow(2.0,0.5)/2;
 *(motor+2)=radius * g_e_v[2] + g_e_v[0] * pow(2.0,0.5)/2 - g_e_v[1] * pow(2.0,0.5)/2;
 *(motor+3)=radius * g_e_v[2] + g_e_v[0] * pow(2.0,0.5)/2 + g_e_v[1] * pow(2.0,0.5)/2;
}
/******************
������������ϵ�ٶȺ���
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
���û���������ϵ�ٶȺ���
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
�����������ĵ�λʱ����������ת��Ϊȫ������ĵ�λʱ������
*********************************/
void TF_Single_To_Global(double motor[2],double *g_e_v,double a)
{
	*g_e_v = motor[0] * cos(a) + motor[1] * sin(a);
	*(g_e_v+1) = - motor[1] * cos(a) + motor[1] * sin(a);
}
/********************
��̼���
********************/
void position_counter()
{
	static double ecoder1[2]={0,0},ecoder2[2]={0,0};
	double motor[2],position[2],w;
	double angle;
	uint16_t buffer=0;
	
	
	buffer = TIM_GetCounter(TIM2); 
	angle= (float)buffer*360.0/encoder_barrier;
  basketballbot.encoder_data.M1=(basketballbot.count1+angle/360)*diameter*pi;		 //�õ�ʵ�ʵ��ۼ�ת�����ȣ���λcm
	//��λʱ���ڱ��������ݵĲ�ֵ
	ecoder1[1] = basketballbot.encoder_data.M1;
	motor[0] = ecoder1[1] - ecoder1[0];
	ecoder1[0] = ecoder1[1];
	
	buffer = TIM_GetCounter(TIM4); 
	angle= (float)buffer*360.0/encoder_barrier;
  basketballbot.encoder_data.M2=(basketballbot.count2+angle/360)*diameter*pi;		 //�õ�ʵ�ʵ��ۼ�ת�����ȣ���λcm
	ecoder2[1] = basketballbot.encoder_data.M2;
	motor[1] = ecoder2[1] - ecoder2[0];
	ecoder2[0] = ecoder2[1];
	//�Ƕȼ���          //���������ʣ�������
	if(motor[1]!=0)
		w = atan(motor[0]/motor[1])+ basketballbot.real_position.z * ( pi/180 );//����
	else
		w = pi*0.5+ basketballbot.real_position.z * ( pi/180 );//����
	TF_Single_To_Global(motor,position,w);
	//��̼Ƶ�X��Y����
	basketballbot.real_position.x += position[0];//��λ��cm
	basketballbot.real_position.y += position[1];//��λ��cm
}
/***************
���̿���
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
