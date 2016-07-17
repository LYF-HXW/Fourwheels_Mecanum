#ifndef __usart3_h
#define __usart3_h
#include "stm32f10x.h"
#include <stdio.h>
#include "queue.h"
#include "mydata.h"

#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口2接收	
#define USART3_REC_LEN  			200  	//定义最大接收字节数 200

void uart3_init(u32 bound);
void USART3_SendChar(u8 b);
void send_speed(void);
#endif
