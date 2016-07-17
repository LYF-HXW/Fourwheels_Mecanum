#ifndef __usart2_h
#define __usart2_h
#include "stm32f10x.h"
#include <stdio.h>
#include "queue.h"
#include "mydata.h"

#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������2����	
#define USART2_REC_LEN  			200  	//�����������ֽ��� 200

void uart2_init(u32 bound);
void USART2_SendChar(u8 b);
float TF_Gyro(uint8_t a,uint8_t b,uint8_t c);
#endif
