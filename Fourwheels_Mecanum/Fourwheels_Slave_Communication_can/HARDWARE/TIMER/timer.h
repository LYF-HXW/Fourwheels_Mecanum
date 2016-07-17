#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "led.h"
#include "usart.h"
#include "mydata.h"


extern robot basketballbot;

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
#endif
