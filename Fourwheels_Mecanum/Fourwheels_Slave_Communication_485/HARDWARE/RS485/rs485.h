#ifndef __RS485_H__
#define __RS485_H__
#include "queue_handle_data.h"

#define RS485_TX_EN		PDout(7)	//485模式控制.0,接收;1,发送.

void RS485_Init(u32 bound);
void USART_485_Send_Char(unsigned char data);

void RS485_RoboModule_DRV_Reset(unsigned char RS485_ID);
void RS485_RoboModule_DRV_Mode_Choice(unsigned char RS485_ID,unsigned char mode);
void RS485_RoboModule_DRV_PWM_Mode(unsigned char RS485_ID,short temp_pwm);
void RS485_RoboModule_DRV_PWM_Current_Mode(unsigned char RS485_ID,short temp_pwm,short temp_current);
void RS485_RoboModule_DRV_PWM_Velocity_Mode(unsigned char RS485_ID,short temp_pwm,short temp_velocity);
void RS485_RoboModule_DRV_PWM_Position_Mode(unsigned char RS485_ID,short temp_pwm,long temp_position);
void RS485_RoboModule_DRV_PWM_Velocity_Position_Mode(unsigned char RS485_ID,short temp_pwm,short temp_velocity,long temp_position);
void RS485_RoboModule_DRV_Current_Velocity_Mode(unsigned char RS485_ID,short temp_current,short temp_velocity);
void RS485_RoboModule_DRV_Current_Position_Mode(unsigned char RS485_ID,short temp_current,long temp_position);
void RS485_RoboModule_DRV_Current_Velocity_Position_Mode(unsigned char RS485_ID,short temp_current,short temp_velocity,long temp_position);

#endif
