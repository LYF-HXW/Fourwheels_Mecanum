#ifndef _QUEUE_DATA_HANDLE_H
#define _QUEUE_DATA_HANDLE_H

#include "delay.h"
#include "sys.h"
#include "led.h"
#include "string.h"
#include "queue.h"
#include "usart.h" 
#include "Motor.h"
#include "mydata.h"

extern volatile Queue rx_queue; 
extern motor speed;

void handle_data(uint8_t buf[]);
#endif
