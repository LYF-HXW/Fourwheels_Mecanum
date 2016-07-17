#include "sys.h"
#include "usart2.h"	
#include "led.h"
#include "queue.h"
#include "mydata.h"
extern robot basketballbot;
uint8_t  buffer_Gyro[9] = {0};
u8 a=0;
enum sta							   		//状态机 
	{
		RECFF1,RECLEN1,ADDRESS,COMMAND,RECSEL,RECCHECK
	} Gyro_sta = RECFF1;
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
#if EN_USART2_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目 
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3 

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2

}

float TF_Gyro(uint8_t a,uint8_t b,uint8_t c)
{
		float angle;
		uint8_t Gyro_angle[6];
		Gyro_angle[0]=a/16;
		Gyro_angle[1]=a%16;
		Gyro_angle[2]=b/16;
		Gyro_angle[3]=b%16;
		Gyro_angle[4]=c/16;
		Gyro_angle[5]=c%16;
		angle=(float)(Gyro_angle[1]*10000+Gyro_angle[2]*1000+Gyro_angle[3]*100+Gyro_angle[4]*10+Gyro_angle[5])/100;
		return angle;
}

void USART2_SendChar(u8 b)
{
	 USART_SendData(USART2,b);
	 while (USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
}

void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	uint8_t data_Gyro;
	static uint16_t checksum_Gyro,datalen_Gyro,cur_Gyro=0,ID;
	
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
		
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	 {
				data_Gyro = USART_ReceiveData(USART2);   
				switch(Gyro_sta)
				{
					case RECFF1:
						if (data_Gyro== 0x68)	  
						{	
							Gyro_sta = RECLEN1;	
							checksum_Gyro=0;		
							cur_Gyro = 0;								//校验位清零
						}
						else
							Gyro_sta = RECFF1;
						break;
						
					case RECLEN1:				 				
						checksum_Gyro += data_Gyro;
						datalen_Gyro  = data_Gyro ;
						Gyro_sta = ADDRESS;	  
					 break;
					
					case ADDRESS:
						if(data_Gyro==0x00)	                      
			        {
					    checksum_Gyro += data_Gyro;
					    Gyro_sta = COMMAND;
				      }
				   else
					   Gyro_sta = RECFF1;	  
						break;
					 
					case COMMAND:
							ID=data_Gyro;
						if(data_Gyro==0x84)	                       
			        {
					    checksum_Gyro += data_Gyro;
					    Gyro_sta = RECSEL;
				      }
				   else if(data_Gyro==0x28)
						{
							checksum_Gyro += data_Gyro;
					    Gyro_sta = RECSEL;
						}
						else
					   Gyro_sta = RECFF1;	
						break;
					 
					 case RECSEL:
				    checksum_Gyro += data_Gyro;
				    buffer_Gyro[cur_Gyro++] = data_Gyro;
				    if(cur_Gyro >= datalen_Gyro-4)
					  Gyro_sta = RECCHECK;
					 break;
						
						case RECCHECK:
				     checksum_Gyro =checksum_Gyro%256;
							if(data_Gyro == checksum_Gyro)
							{		
								a=!a;								
								if(ID==0x84)
								basketballbot.real_position.z = TF_Gyro(buffer_Gyro[6],buffer_Gyro[7],buffer_Gyro[8]);				//TF
								checksum_Gyro=0;	
								Gyro_sta = RECFF1;					
							}
				
							else
								Gyro_sta = RECFF1;
							break;
						default:
							Gyro_sta = RECFF1;
				}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	 }
		
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}
#endif	
