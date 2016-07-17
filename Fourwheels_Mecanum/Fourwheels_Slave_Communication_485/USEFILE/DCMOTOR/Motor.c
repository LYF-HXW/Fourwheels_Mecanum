#include "Motor.h"
#include "main.h"
#include "rs485.h"
#include "mydata.h" 									  

void Speed_Init()
{
		RS485_RoboModule_DRV_Reset(DRV_ALL_RESET_ID);
    delay_ms(500);
    RS485_RoboModule_DRV_Mode_Choice(DRV_ALL_MODE_CHOICE_ID,ENTER_PWM_VELOCITY_MODE);
    delay_ms(500);	
}
void send_speed()
{
		u16 v; 
		v = (int)speed.M1;
		RS485_RoboModule_DRV_PWM_Velocity_Mode(DRV01_PWM_VELOCITY_MODE_ID,5000,v);        //1号驱动盒赋速度
		delay_ms(10);
		v = (int)speed.M2;
		RS485_RoboModule_DRV_PWM_Velocity_Mode(DRV02_PWM_VELOCITY_MODE_ID,5000,v);        //2号驱动盒赋速度
		delay_ms(10);
		v = (int)speed.M3;
		RS485_RoboModule_DRV_PWM_Velocity_Mode(DRV03_PWM_VELOCITY_MODE_ID,5000,v);        //3号驱动盒赋速度
		delay_ms(10);
		v = (int)speed.M4;
		RS485_RoboModule_DRV_PWM_Velocity_Mode(DRV04_PWM_VELOCITY_MODE_ID,5000,v);        //4号驱动盒赋速度
		delay_ms(10);
}	
