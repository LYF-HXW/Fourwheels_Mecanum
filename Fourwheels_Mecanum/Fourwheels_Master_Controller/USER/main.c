#include "stm32f10x.h"
#include "queue_data_handle.h"
#define MAX_DATA_LEN 100
//����һ��������
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();	//LED�˿ڳ�ʼ�� 	
	TIM3_Int_Init(719,4999);  //���ж�0.03
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200������λ������
	uart2_init(9600);  //������������
	uart3_init(9600);
	ENCODE_Init();  //��������ʼ��
	queue_init(&rx_queue);	
	basketballbot.Control_ID = Global;
}

