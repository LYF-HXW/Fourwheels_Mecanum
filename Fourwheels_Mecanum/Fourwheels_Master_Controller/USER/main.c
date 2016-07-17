#include "stm32f10x.h"
#include "queue_data_handle.h"
#define MAX_DATA_LEN 100
//定义一个机器人
robot basketballbot;

volatile Queue rx_queue;
void init(void);

 int main(void)
 {	
	 uint8_t data;
	 static uint16_t checksum;
	 uint8_t  buffer[MAX_DATA_LEN] = {0};
	 int cur=0;
	 int device;
	 uint8_t datalen1;
	 short data_len;
	 enum Recstate								   		//状态机 
	{
		RECFF1,RECFF2,SENDID,RECID,RECLEN1,RECLEN2,RECSEL,RECCHECK
	} rs485Recstate = RECFF1;
	/*******************
	初始化
	******************/
	init();
	
	 while(1)
	{
		if(queue_empty(rx_queue))
			            continue;

		data = (uint8_t)queue_get(&rx_queue);
  
		switch (rs485Recstate) 
		{
			case RECFF1:
				if (data == 0xff)	  
				{	
					rs485Recstate = RECFF2;	
					checksum=0;		
					cur = 0;								//校验位清零
				}
	
				break;
	
			case RECFF2:
				if (data == 0xff)
					rs485Recstate = RECID;
				else
					rs485Recstate = RECFF1;
				break;
	
	
			case RECID:				 					
			     if(data==0x01)	                       //设备编号0x01底盘与航迹
			        {
							device=1;
					    checksum += data;
					    rs485Recstate = RECLEN1;
							
				      }
				else
					rs485Recstate = RECFF1;	  
				break;
	
			case RECLEN1:				 				
				checksum += data;
				datalen1 = data;
				rs485Recstate = RECLEN2;	  
				break;
		
			case RECLEN2:	
				checksum += data;			 				
				data_len = (short)datalen1 << 8	 | data;
				rs485Recstate = RECSEL;	  
				break;
	
			case RECSEL:
				checksum += data;
				buffer[cur++] = data;
				if(cur >= data_len)
					rs485Recstate = RECCHECK;
				break;
	
			case RECCHECK:
				checksum=checksum%255;
				
				if(data == checksum)
				{			
					handle_data(buffer,device, data_len);
					
  				send();				
					checksum=0;	
					rs485Recstate = RECFF1;	 
				}
				
				else
					rs485Recstate = RECFF1;
				break;
			 default:
					rs485Recstate = RECFF1;
			}	   	 
		}	
	
}
 
void init()
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();	//LED端口初始化 	
	TIM3_Int_Init(719,4999);  //主中断0.03
	uart_init(9600);	 //串口初始化为115200，读上位机数据
	uart2_init(9600);  //读陀螺仪数据
	uart3_init(9600);
	ENCODE_Init();  //编码器初始化
	queue_init(&rx_queue);	
	basketballbot.Control_ID = Global;
}

