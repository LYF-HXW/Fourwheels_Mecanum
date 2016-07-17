#include "key.h"
#include "main.h"
#include "lcd.h"	
#include "rs485.h"
#include "queue_handle_data.h"

motor speed;
volatile Queue rx_queue;     //生成一个消息队列
void init(void);
#define MAX_DATA_LEN 100
/************************************************
 ALIENTEK战舰STM32开发板实验25
 485通信实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

 				 	
 int main(void)
 {	 
	uint8_t data;
	static uint16_t checksum;
	uint8_t  buffer[MAX_DATA_LEN] = {0};
	uint16_t cur=0;
	uint8_t datalen1;
	uint16_t data_len;
	 enum Recstate								   		//状态机 
	{
		RECFF1,RECFF2,SENDID,RECID,RECLEN1,RECLEN2,RECSEL,RECCHECK
	} rs485Recstate = RECFF1;
	 
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
				checksum=checksum%256;
				
				if(data == checksum)
				{		
					handle_data(buffer);
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口	
	RS485_Init(115200);	//初始化RS485
	queue_init(&rx_queue);
	Speed_Init();
}
