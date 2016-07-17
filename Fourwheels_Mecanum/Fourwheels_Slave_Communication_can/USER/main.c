#include "key.h"
#include "lcd.h" 
#include "queue_handle_data.h"

robot basketballbot;         //����һ��������
volatile Queue rx_queue;     //����һ����Ϣ����
void init(void);
#define MAX_DATA_LEN 100
/************************************************
 ALIENTEKս��STM32������ʵ��26
 CANͨ��ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
{	
	 uint8_t data;
	 static uint16_t checksum;
	 uint8_t  buffer[MAX_DATA_LEN] = {0};
	 uint16_t cur=0;
	 uint8_t datalen1;
	 uint16_t data_len;
	 enum Recstate								   		//״̬�� 
	{
		RECFF1,RECFF2,SENDID,RECID,RECLEN1,RECLEN2,RECSEL,RECCHECK
	} rs485Recstate = RECFF1;
	/*******************
	��ʼ��
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
					cur = 0;								//У��λ����
				}
	
				break;
	
			case RECFF2:
				if (data == 0xff)
					rs485Recstate = RECID;
				else
					rs485Recstate = RECFF1;
				break;
	
			case RECID:				 					
			     if(data==0x01)	                       //�豸���0x01�����뺽��
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
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();	//LED�˿ڳ�ʼ�� 
	TIM3_Int_Init(719,4999);//T=0.05s
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200������λ������
	queue_init(&rx_queue);	
}
