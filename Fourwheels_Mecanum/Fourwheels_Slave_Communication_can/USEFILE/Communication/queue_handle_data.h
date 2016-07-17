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
#include "can.h" 
#include "Motor.h"
#include "timer.h"

extern volatile Queue rx_queue; 
extern robot basketballbot;

void handle_data(uint8_t buf[]);
#endif
