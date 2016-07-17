#ifndef __usart3_h
#define __usart3_h
#include "stm32f10x.h"
#include <stdio.h>
#include "queue.h"
#include "mydata.h"

#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������2����	
#define USART3_REC_LEN  			200  	//�����������ֽ��� 200

void uart3_init(u32 bound);
void USART3_SendChar(u8 b);
void send_speed(void);
#endif
