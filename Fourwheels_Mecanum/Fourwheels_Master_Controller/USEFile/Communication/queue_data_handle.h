#ifndef _QUEUE_DATA_HANDLE_H
#define _QUEUE_DATA_HANDLE_H
#include "timer.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "string.h"
#include "queue.h"
#include "mydata.h"
#include "usart.h"
#include "usart2.h"
#include "usart3.h"

#define MAX_DATA_LEN 100

extern volatile Queue rx_queue; 
extern robot basketballbot;

void handle_data(uint8_t buf[], int D,int len);//��λ�����ݴ���
void start_dc(void);	          //����ٶȵĸ�ֵ
void send(void);                //����ִ������ظ�
#endif
