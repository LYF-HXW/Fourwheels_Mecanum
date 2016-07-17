#include "sys.h"
#include "usart3.h"	
#include "led.h"
#include "queue.h"
#include "mydata.h"
extern robot basketballbot;
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
#if EN_USART3_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART3_RX_BUF[USART3_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目 
void uart3_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART2
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11 

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3

}

void USART3_SendChar(u8 b)
{
	 USART_SendData(USART3,b);
	 while (USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
}

void send_speed()
{	
	uint16_t checksumsend2=0x11;
	char c_transition[4],i;
	float f_transition=0;
	if(USART_GetFlagStatus(USART3, USART_FLAG_TC)!=RESET)    //现在没有数据在发送成立
	{		
			USART3_SendChar(0xff);
			USART3_SendChar(0xff);
			USART3_SendChar(0x01);
			USART3_SendChar(0x00);
			USART3_SendChar(0x10);
			f_transition = basketballbot.single_expected_speed.M1;
			memcpy( c_transition, &f_transition,sizeof(float));
			for(i = 0;i < 4;i++)
			{
				USART3_SendChar(c_transition[i]);
				checksumsend2 += c_transition[i];
			}
			
			f_transition = basketballbot.single_expected_speed.M2;
			memcpy( c_transition, &f_transition,sizeof(float));
			for(i = 0;i < 4;i++)
			{
				USART3_SendChar(c_transition[i]);
				checksumsend2 += c_transition[i];
			}
			
			f_transition = basketballbot.single_expected_speed.M3;
			memcpy( c_transition, &f_transition,sizeof(float));
			for(i = 0;i < 4;i++)
			{
				USART3_SendChar(c_transition[i]);
				checksumsend2 += c_transition[i];
			}
			
			f_transition = basketballbot.single_expected_speed.M4;
			memcpy( c_transition, &f_transition,sizeof(float));
			for(i = 0;i < 4;i++)
			{
				USART3_SendChar(c_transition[i]);
				checksumsend2 += c_transition[i];
			}
			checksumsend2=checksumsend2%256;
			USART3_SendChar(checksumsend2);
	}
		
}
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
		
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	 {
		 
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	 }
		
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}
#endif	
