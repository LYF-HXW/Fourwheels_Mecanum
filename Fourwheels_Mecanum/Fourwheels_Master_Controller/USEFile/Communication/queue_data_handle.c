#include "queue_data_handle.h"

static int noselect;
uint8_t radBufferRS485[99];  //记录转角
float xiansu(float v)                        //防止速度过快
{
   if(v>2) 
     {
	    return 2;
	 }
   if(v<-2) 
     {
	    return -2;
	 } 
   else
   {
        return v;
   }

}

void handle_data(uint8_t buf[], int D,int len)    
{
	 int i=0;
		switch(D)
		{ 
			case 1:				if(buf[0]==1) 
		            	  {
                     noselect = 0x01 ; basketballbot.Control_ID = Global; break;     //赋值世界坐标系速度
			              }
										else if(buf[0]==2)
										{
                     noselect = 0x02 ; basketballbot.Control_ID = Robot; break;     //赋值机器人坐标系速度
			              }
										else if(buf[0]==3)
										{
                     noselect = 0x03 ; break;     //返回里程
			              }
			default:break;
		}
	if(noselect == 0x01 || noselect == 0x02)			
			{						
				for(i=0;i<12;i++)									     			//记录速度
				{
					radBufferRS485[i] = buf[i+1] ;								
				}			
			}	
	    
} 

void start_dc(void)	    //电机速度的赋值
{	
     
 	  u8 byte1[4],byte2[4];
	  if(noselect == 0x01) 	//世界坐标系	
		{			
		byte1[0] = radBufferRS485[0];
		byte1[1] = radBufferRS485[1];
		byte1[2] = radBufferRS485[2];
		byte1[3] = radBufferRS485[3];	
    memcpy(&basketballbot.globel_expected_speed.x,byte1,sizeof(int));	  //x轴速度
		basketballbot.globel_expected_speed.x=xiansu(basketballbot.globel_expected_speed.x);
			
		byte1[0] = radBufferRS485[4];
		byte1[1] = radBufferRS485[5];
		byte1[2] = radBufferRS485[6];
		byte1[3] = radBufferRS485[7];		
   	memcpy(&basketballbot.globel_expected_speed.y,byte1,sizeof(int));   //y轴速度
		basketballbot.globel_expected_speed.y=xiansu(basketballbot.globel_expected_speed.y);
										   
		byte1[0] = radBufferRS485[8];
		byte1[1] = radBufferRS485[9];
		byte1[2] = radBufferRS485[10];
		byte1[3] = radBufferRS485[11];
    memcpy(&basketballbot.globel_expected_speed.z,byte1,sizeof(int));	 //角速度
		basketballbot.globel_expected_speed.z=xiansu(basketballbot.globel_expected_speed.z);			
		}		
		
		else if(noselect == 0x02)  //机器人坐标系
		{			
		byte2[0] = radBufferRS485[0];
		byte2[1] = radBufferRS485[1];
		byte2[2] = radBufferRS485[2];
		byte2[3] = radBufferRS485[3];	
    memcpy(&basketballbot.robot_expected_speed.x,byte2,sizeof(int));	  //x轴速度
		basketballbot.robot_expected_speed.x=xiansu(basketballbot.robot_expected_speed.x);
			
		byte2[0] = radBufferRS485[4];
		byte2[1] = radBufferRS485[5];
		byte2[2] = radBufferRS485[6];
		byte2[3] = radBufferRS485[7];		
   	memcpy(&basketballbot.robot_expected_speed.y,byte2,sizeof(int));   //y轴速度
		basketballbot.robot_expected_speed.y=xiansu(basketballbot.robot_expected_speed.y);
										   
		byte2[0] = radBufferRS485[8];
		byte2[1] = radBufferRS485[9];
		byte2[2] = radBufferRS485[10];
		byte2[3] = radBufferRS485[11];
    memcpy(&basketballbot.robot_expected_speed.z,byte2,sizeof(int));	 //角速度
		basketballbot.robot_expected_speed.z=xiansu(basketballbot.robot_expected_speed.z);			
		}		
}

void send(void)
{
	uint16_t checksumsend2=0x10;
	char c_transition[4],i;
	float f_transition=0;
	LED0=!LED0;
	if(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=RESET)    //现在没有数据在发送成立
	{	
		
		if(noselect == 0x01 || noselect == 0x02)
		 {
			start_dc();		
			//LED1=0;
			noselect=0;
		 }
		else if(noselect == 0x03)
		 {
		  USART1_SendChar(0xff);
			USART1_SendChar(0xff);
			USART1_SendChar(0x01);
			USART1_SendChar(0x00);
			USART1_SendChar(0x0d);
			USART1_SendChar(0x02);
			//basketballbot.real_position.x
			f_transition = basketballbot.real_position.x;
			memcpy( c_transition, &f_transition,sizeof(float));
			for(i = 0;i < 4;i++)
			{
				USART1_SendChar(c_transition[i]);
				checksumsend2 += c_transition[i];
			}
			//basketballbot.real_position.y
			f_transition = basketballbot.real_position.y;
			memcpy( c_transition, &f_transition,sizeof(float));
			for(i = 0;i < 4;i++)
			{
				USART1_SendChar(c_transition[i]);
				checksumsend2 += c_transition[i];
			}
			
			checksumsend2=checksumsend2%255;
			USART1_SendChar(checksumsend2);
			noselect=0;
		 }			
	}
   // while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);				
}
