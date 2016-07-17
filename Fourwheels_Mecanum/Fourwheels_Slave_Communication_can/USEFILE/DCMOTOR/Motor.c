#include "Motor.h"

/*********************
进制转换函数，将10进制转换为16进制，形参N为待转换值，转换完后的值放入指针h对应的数组中
********************/ 
void itoh(int N, uint8_t *h)   
{
    uint8_t a[10]={0};
    int count=0;
    while(N != 0)
    {
       a[count++]=N&0xf;
       N>>=4;
			if(count==8) break;
    }
		
    *h=(a[1]<<4)|a[0];
    *(h+1)=(a[3]<<4)|a[2];
    *(h+2)=(a[5]<<4)|a[4];
    *(h+3)=(a[7]<<4)|a[6];
}

/*********************
发送角速度到驱动核
*********************/ 
u8 Can_send_motorx(float v,u8 UID)  
{
	u8 mbox;
	u16 i=0;
	uint8_t b[4]={0};
	CanTxMsg TxMessageBuffer;
	
	TxMessageBuffer.StdId=UID;	 
	TxMessageBuffer.ExtId=UID;
	TxMessageBuffer.RTR=0;	              // 传输消息的帧类型为数据帧（还有远程帧）
	TxMessageBuffer.IDE=0;	              // 消息标志符实验标准标识符
	TxMessageBuffer.DLC=8;					       // 发送两帧，一帧8位
	TxMessageBuffer.Data[0]=0x08;			     // 1or2or3请求和回复和控制
	TxMessageBuffer.Data[1]=UID;			     // 驱动器ID
	TxMessageBuffer.Data[2]=0x90;          //速度指令
  TxMessageBuffer.Data[3]=0x00;
	itoh((int)v, b);                      /*********10进制转16进制***********/
	TxMessageBuffer.Data[4]=*b;
	TxMessageBuffer.Data[5]=*(b+1);
	TxMessageBuffer.Data[6]=*(b+2);
	TxMessageBuffer.Data[7]=*(b+3);
	
	i=0;	
  do{	
	mbox = CAN_Transmit(CAN1, &TxMessageBuffer);   //把期望角速度发给驱动板
	i++;
	delay_us(200);
  }while((mbox==CAN_TxStatus_NoMailBox)&&i<0xfff);	//邮箱满重发
	i=0;	
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束	
  if(i>=0XFFF)return 1;
  return 0;
}
/********************
速度发送给驱动盒
********************/
void send_speed()
{
	 static u8 Motor_cnt = 0;
	 Motor_cnt++;
	 if(Motor_cnt%4 == 0)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M1 ,0x30);//驱动盒1的ID：0x36
			}
	 else if(Motor_cnt%4 == 1)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M2 ,0x32);//驱动盒2的ID：0x32
			}
	 else if(Motor_cnt%4 == 2)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M3 ,0x34);//驱动盒3的ID：0x30
			}
	 else if(Motor_cnt%4 == 3)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M4 ,0x30);//驱动盒4的ID：0x34
			}	
}
