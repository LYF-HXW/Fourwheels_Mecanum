#include "main.h"
#include "rs485.h"	

void RS485_Init(u32 bound)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//ʹ��GPIOA,Dʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //PD7�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ
 
	
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); ; //��ʼ������
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
	
  RS485_TX_EN=1;			//Ĭ��Ϊ����ģʽ
 
}
void USART_485_Send_Char(unsigned char data)
{
  while(USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	USART_SendData(USART2,data);
}


/****************************************************************************************
                                       ��λָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_RESET_ID
DRV01_RESET_ID    DRV02_RESET_ID    DRV03_RESET_ID    DRV04_RESET_ID    DRV05_RESET_ID
DRV06_RESET_ID    DRV07_RESET_ID    DRV08_RESET_ID    DRV09_RESET_ID    DRV10_RESET_ID
DRV11_RESET_ID    DRV12_RESET_ID    DRV13_RESET_ID    DRV14_RESET_ID    DRV15_RESET_ID
*****************************************************************************************/
void RS485_RoboModule_DRV_Reset(unsigned char RS485_ID)
{
    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
}


/****************************************************************************************
                                     ģʽѡ��ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_MODE_CHOICE_ID
DRV01_MODE_CHOICE_ID    DRV02_MODE_CHOICE_ID    DRV03_MODE_CHOICE_ID    DRV04_MODE_CHOICE_ID    DRV05_MODE_CHOICE_ID    
DRV06_MODE_CHOICE_ID    DRV07_MODE_CHOICE_ID    DRV08_MODE_CHOICE_ID    DRV09_MODE_CHOICE_ID    DRV10_MODE_CHOICE_ID    
DRV11_MODE_CHOICE_ID    DRV12_MODE_CHOICE_ID    DRV13_MODE_CHOICE_ID    DRV14_MODE_CHOICE_ID    DRV15_MODE_CHOICE_ID

mode��ȡֵ��Χ���£�
ENTER_PWM_MODE
ENTER_PWM_CURRENT_MODE
ENTER_PWM_VELOCITY_MODE
ENTER_PWM_POSITION_MODE
ENTER_PWM_VELOCITY_POSITION_MODE
ENTER_CURRENT_VELOCITY_MODE
ENTER_CURRENT_POSITION_MODE
ENTER_CURRENT_VELOCITY_POSITION_MODE
*****************************************************************************************/
void RS485_RoboModule_DRV_Mode_Choice(unsigned char RS485_ID,unsigned char mode)
{
    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char(mode);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
}


/****************************************************************************************
                                  PWMģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_PWM_MODE_ID
DRV01_PWM_MODE_ID    DRV02_PWM_MODE_ID    DRV03_PWM_MODE_ID    DRV04_PWM_MODE_ID    DRV05_PWM_MODE_ID
DRV06_PWM_MODE_ID    DRV07_PWM_MODE_ID    DRV08_PWM_MODE_ID    DRV09_PWM_MODE_ID    DRV10_PWM_MODE_ID
DRV11_PWM_MODE_ID    DRV12_PWM_MODE_ID    DRV13_PWM_MODE_ID    DRV14_PWM_MODE_ID    DRV15_PWM_MODE_ID

temp_pwm��ȡֵ��Χ���£�
-5000 ~ +5000
*****************************************************************************************/
void RS485_RoboModule_DRV_PWM_Mode(unsigned char RS485_ID,short temp_pwm)
{
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_pwm>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_pwm&0xff));
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
}


/****************************************************************************************
                                  PWM����ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_PWM_CURRENT_MODE_ID
DRV01_PWM_CURRENT_MODE_ID    DRV02_PWM_CURRENT_MODE_ID    DRV03_PWM_CURRENT_MODE_ID    DRV04_PWM_CURRENT_MODE_ID    DRV05_PWM_CURRENT_MODE_ID
DRV06_PWM_CURRENT_MODE_ID    DRV07_PWM_CURRENT_MODE_ID    DRV08_PWM_CURRENT_MODE_ID    DRV09_PWM_CURRENT_MODE_ID    DRV10_PWM_CURRENT_MODE_ID
DRV11_PWM_CURRENT_MODE_ID    DRV12_PWM_CURRENT_MODE_ID    DRV13_PWM_CURRENT_MODE_ID    DRV14_PWM_CURRENT_MODE_ID    DRV15_PWM_CURRENT_MODE_ID

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000

temp_current��ȡֵ��Χ���£�
-1600 ~ +1600
*****************************************************************************************/
void RS485_RoboModule_DRV_PWM_Current_Mode(unsigned char RS485_ID,short temp_pwm,short temp_current)
{
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }

    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_pwm>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_pwm&0xff));
    USART_485_Send_Char((unsigned char)((temp_current>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_current&0xff));
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
}


/****************************************************************************************
                                  PWM�ٶ�ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_PWM_VELOCITY_MODE_ID
DRV01_PWM_VELOCITY_MODE_ID    DRV02_PWM_VELOCITY_MODE_ID    DRV03_PWM_VELOCITY_MODE_ID    DRV04_PWM_VELOCITY_MODE_ID    DRV05_PWM_VELOCITY_MODE_ID
DRV06_PWM_VELOCITY_MODE_ID    DRV07_PWM_VELOCITY_MODE_ID    DRV08_PWM_VELOCITY_MODE_ID    DRV09_PWM_VELOCITY_MODE_ID    DRV10_PWM_VELOCITY_MODE_ID
DRV11_PWM_VELOCITY_MODE_ID    DRV12_PWM_VELOCITY_MODE_ID    DRV13_PWM_VELOCITY_MODE_ID    DRV14_PWM_VELOCITY_MODE_ID    DRV15_PWM_VELOCITY_MODE_ID

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000

temp_velocity��ȡֵ��Χ���£�
-2000 ~ +2000
*****************************************************************************************/
void RS485_RoboModule_DRV_PWM_Velocity_Mode(unsigned char RS485_ID,short temp_pwm,short temp_velocity)
{
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }

    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_pwm>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_pwm&0xff));
    USART_485_Send_Char((unsigned char)((temp_velocity>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_velocity&0xff));
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
}


/****************************************************************************************
                                  PWMλ��ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_PWM_POSITION_MODE_ID
DRV01_PWM_POSITION_MODE_ID    DRV02_PWM_POSITION_MODE_ID    DRV03_PWM_POSITION_MODE_ID    DRV04_PWM_POSITION_MODE_ID    DRV05_PWM_POSITION_MODE_ID
DRV06_PWM_POSITION_MODE_ID    DRV07_PWM_POSITION_MODE_ID    DRV08_PWM_POSITION_MODE_ID    DRV09_PWM_POSITION_MODE_ID    DRV10_PWM_POSITION_MODE_ID
DRV11_PWM_POSITION_MODE_ID    DRV12_PWM_POSITION_MODE_ID    DRV13_PWM_POSITION_MODE_ID    DRV14_PWM_POSITION_MODE_ID    DRV15_PWM_POSITION_MODE_ID

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000

temp_position��ȡֵ��Χ���£�
32λ�з�������
*****************************************************************************************/
void RS485_RoboModule_DRV_PWM_Position_Mode(unsigned char RS485_ID,short temp_pwm,long temp_position)
{

    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }

    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_pwm>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_pwm&0xff));
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char((unsigned char)((temp_position>>24)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>16)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_position&0xff));
}


/****************************************************************************************
                                  PWM�ٶ�λ��ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_PWM_VELOCITY_POSITION_MODE_ID
DRV01_PWM_VELOCITY_POSITION_MODE_ID    DRV02_PWM_VELOCITY_POSITION_MODE_ID    DRV03_PWM_VELOCITY_POSITION_MODE_ID    DRV04_PWM_VELOCITY_POSITION_MODE_ID    DRV05_PWM_VELOCITY_POSITION_MODE_ID
DRV06_PWM_VELOCITY_POSITION_MODE_ID    DRV07_PWM_VELOCITY_POSITION_MODE_ID    DRV08_PWM_VELOCITY_POSITION_MODE_ID    DRV09_PWM_VELOCITY_POSITION_MODE_ID    DRV10_PWM_VELOCITY_POSITION_MODE_ID
DRV11_PWM_VELOCITY_POSITION_MODE_ID    DRV12_PWM_VELOCITY_POSITION_MODE_ID    DRV13_PWM_VELOCITY_POSITION_MODE_ID    DRV14_PWM_VELOCITY_POSITION_MODE_ID    DRV15_PWM_VELOCITY_POSITION_MODE_ID

temp_pwm��ȡֵ��Χ���£�
0 ~ +5000

temp_velocity��ȡֵ��Χ���£�
0 ~ +2000

temp_position��ȡֵ��Χ���£�
32λ�з�������
*****************************************************************************************/
void RS485_RoboModule_DRV_PWM_Velocity_Position_Mode(unsigned char RS485_ID,short temp_pwm,short temp_velocity,long temp_position)
{

    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    if(temp_velocity < 0)
    {
        temp_velocity = abs(temp_velocity);
    }

    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_pwm>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_pwm&0xff));
    USART_485_Send_Char((unsigned char)((temp_velocity>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_velocity&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>24)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>16)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_position&0xff));
}


/****************************************************************************************
                                  �����ٶ�ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_CURRENT_VELOCITY_MODE_ID
DRV01_CURRENT_VELOCITY_MODE_ID    DRV02_CURRENT_VELOCITY_MODE_ID    DRV03_CURRENT_VELOCITY_MODE_ID    DRV04_CURRENT_VELOCITY_MODE_ID    DRV05_CURRENT_VELOCITY_MODE_ID
DRV06_CURRENT_VELOCITY_MODE_ID    DRV07_CURRENT_VELOCITY_MODE_ID    DRV08_CURRENT_VELOCITY_MODE_ID    DRV09_CURRENT_VELOCITY_MODE_ID    DRV10_CURRENT_VELOCITY_MODE_ID
DRV11_CURRENT_VELOCITY_MODE_ID    DRV12_CURRENT_VELOCITY_MODE_ID    DRV13_CURRENT_VELOCITY_MODE_ID    DRV14_CURRENT_VELOCITY_MODE_ID    DRV15_CURRENT_VELOCITY_MODE_ID

temp_current��ȡֵ��Χ���£�
0 ~ +1600

temp_velocity��ȡֵ��Χ���£�
-2000 ~ +2000
*****************************************************************************************/
void RS485_RoboModule_DRV_Current_Velocity_Mode(unsigned char RS485_ID,short temp_current,short temp_velocity)
{

    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    if(temp_current < 0)
    {
        temp_current = abs(temp_current);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }

    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_current>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_current&0xff));
    USART_485_Send_Char((unsigned char)((temp_velocity>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_velocity&0xff));
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
}


/****************************************************************************************
                                  ����λ��ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_CURRENT_POSITION_MODE_ID
DRV01_CURRENT_POSITION_MODE_ID    DRV02_CURRENT_POSITION_MODE_ID    DRV03_CURRENT_POSITION_MODE_ID    DRV04_CURRENT_POSITION_MODE_ID    DRV05_CURRENT_POSITION_MODE_ID
DRV06_CURRENT_POSITION_MODE_ID    DRV07_CURRENT_POSITION_MODE_ID    DRV08_CURRENT_POSITION_MODE_ID    DRV09_CURRENT_POSITION_MODE_ID    DRV10_CURRENT_POSITION_MODE_ID
DRV11_CURRENT_POSITION_MODE_ID    DRV12_CURRENT_POSITION_MODE_ID    DRV13_CURRENT_POSITION_MODE_ID    DRV14_CURRENT_POSITION_MODE_ID    DRV15_CURRENT_POSITION_MODE_ID

temp_current��ȡֵ��Χ���£�
0 ~ +1600

temp_position��ȡֵ��Χ���£�
32λ�з�������
*****************************************************************************************/
void RS485_RoboModule_DRV_Current_Position_Mode(unsigned char RS485_ID,short temp_current,long temp_position)
{
    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    if(temp_current < 0)
    {
        temp_current = abs(temp_current);
    }
    
    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_current>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_current&0xff));
    USART_485_Send_Char(0x55);
    USART_485_Send_Char(0x55);
    USART_485_Send_Char((unsigned char)((temp_position>>24)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>16)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_position&0xff));
}


/****************************************************************************************
                                  �����ٶ�λ��ģʽ�µ�����ָ��
RS485_ID��ȡֵ��Χ���£�
DRV_ALL_CURRENT_VELOCITY_POSITION_MODE_ID
DRV01_CURRENT_VELOCITY_POSITION_MODE_ID    DRV02_CURRENT_VELOCITY_POSITION_MODE_ID    DRV03_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV04_CURRENT_VELOCITY_POSITION_MODE_ID    DRV05_CURRENT_VELOCITY_POSITION_MODE_ID    DRV06_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV07_CURRENT_VELOCITY_POSITION_MODE_ID    DRV08_CURRENT_VELOCITY_POSITION_MODE_ID    DRV09_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV10_CURRENT_VELOCITY_POSITION_MODE_ID    DRV11_CURRENT_VELOCITY_POSITION_MODE_ID    DRV12_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV13_CURRENT_VELOCITY_POSITION_MODE_ID    DRV14_CURRENT_VELOCITY_POSITION_MODE_ID    DRV15_CURRENT_VELOCITY_POSITION_MODE_ID

temp_current��ȡֵ��Χ���£�
0 ~ +1600

temp_velocity��ȡֵ��Χ���£�
0 ~ +2000

temp_position��ȡֵ��Χ���£�
32λ�з�������
*****************************************************************************************/
void RS485_RoboModule_DRV_Current_Velocity_Position_Mode(unsigned char RS485_ID,short temp_current,short temp_velocity,long temp_position)
{

    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    if(temp_current < 0)
    {
        temp_current = abs(temp_current);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    if(temp_velocity < 0)
    {
        temp_velocity = abs(temp_velocity);
    }
    
    USART_485_Send_Char(0x48);
    USART_485_Send_Char(RS485_ID);
    USART_485_Send_Char((unsigned char)((temp_current>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_current&0xff));
    USART_485_Send_Char((unsigned char)((temp_velocity>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_velocity&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>24)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>16)&0xff));
    USART_485_Send_Char((unsigned char)((temp_position>>8)&0xff));
    USART_485_Send_Char((unsigned char)(temp_position&0xff));
}
