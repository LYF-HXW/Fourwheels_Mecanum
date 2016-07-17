#include"stm32f10x.h"
#include "timer.h"
#include "led.h"
#include "usart.h"
#include "usart2.h"
#include "usart3.h"	
#include "transform.h"
#include "mydata.h"
void send(void);
extern robot basketballbot;
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	static char i = 0;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		i++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(i == 9){LED1 = !LED1;i = 0;}
		send_speed();
		move_base_control();
		}
}






void ENCODE_Init(void)			// TIM2 4的编码器模式
{
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_ICInitTypeDef TIM_ICInitStructure;
	
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);	   //很重要的一条必须加上复用功能
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
		//--------------------------TIM2 CHI1 CHI2---PA0 PA1;
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		//--------------------------TIM4 CHI1 CHI2---PB6 PB7;
	 	GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//--------------------中断优先级
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);


	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

		//---------------------------------------------------TIM2 CHI1 CHI2
  	TIM_DeInit(TIM2);
  	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  	TIM_TimeBaseStructure.TIM_Prescaler =(4*ENCODER_PPR)-1;  
  	TIM_TimeBaseStructure.TIM_Period = 2000-1;  	    	
 	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 
  	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

  	TIM_ICStructInit(&TIM_ICInitStructure);
  	TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);


 //------------------------------------------------TIM4 CHI1 CHI2
  	TIM_DeInit(TIM4);
  	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  	TIM_TimeBaseStructure.TIM_Prescaler =(4*ENCODER_PPR)-1;  
  	TIM_TimeBaseStructure.TIM_Period = 2000-1;  	    		
 	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
  	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

  	TIM_ICStructInit(&TIM_ICInitStructure);
  	TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);    
   

	  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	  TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	 
 
  	TIM_Cmd(TIM2, ENABLE);
	  TIM_Cmd(TIM4, ENABLE);  
}

void TIM2_IRQHandler(void)	   //----TIM2 PA0,1		编码器数据读取
{	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	if((TIM2->CR1 & 0x0010)==0)  			
	basketballbot.count1++;
	else   
	basketballbot.count1--;	
}

void TIM4_IRQHandler(void)	   //----TIM4  PB6,7			编码器数据读取
{	
 TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	if((TIM4->CR1 & 0x0010)==0)  			
	basketballbot.count2++;  
	else   
	basketballbot.count2--; 
}

