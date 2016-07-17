#include "Motor.h"

/*********************
����ת����������10����ת��Ϊ16���ƣ��β�NΪ��ת��ֵ��ת������ֵ����ָ��h��Ӧ��������
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
���ͽ��ٶȵ�������
*********************/ 
u8 Can_send_motorx(float v,u8 UID)  
{
	u8 mbox;
	u16 i=0;
	uint8_t b[4]={0};
	CanTxMsg TxMessageBuffer;
	
	TxMessageBuffer.StdId=UID;	 
	TxMessageBuffer.ExtId=UID;
	TxMessageBuffer.RTR=0;	              // ������Ϣ��֡����Ϊ����֡������Զ��֡��
	TxMessageBuffer.IDE=0;	              // ��Ϣ��־��ʵ���׼��ʶ��
	TxMessageBuffer.DLC=8;					       // ������֡��һ֡8λ
	TxMessageBuffer.Data[0]=0x08;			     // 1or2or3����ͻظ��Ϳ���
	TxMessageBuffer.Data[1]=UID;			     // ������ID
	TxMessageBuffer.Data[2]=0x90;          //�ٶ�ָ��
  TxMessageBuffer.Data[3]=0x00;
	itoh((int)v, b);                      /*********10����ת16����***********/
	TxMessageBuffer.Data[4]=*b;
	TxMessageBuffer.Data[5]=*(b+1);
	TxMessageBuffer.Data[6]=*(b+2);
	TxMessageBuffer.Data[7]=*(b+3);
	
	i=0;	
  do{	
	mbox = CAN_Transmit(CAN1, &TxMessageBuffer);   //���������ٶȷ���������
	i++;
	delay_us(200);
  }while((mbox==CAN_TxStatus_NoMailBox)&&i<0xfff);	//�������ط�
	i=0;	
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���	
  if(i>=0XFFF)return 1;
  return 0;
}
/********************
�ٶȷ��͸�������
********************/
void send_speed()
{
	 static u8 Motor_cnt = 0;
	 Motor_cnt++;
	 if(Motor_cnt%4 == 0)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M1 ,0x30);//������1��ID��0x36
			}
	 else if(Motor_cnt%4 == 1)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M2 ,0x32);//������2��ID��0x32
			}
	 else if(Motor_cnt%4 == 2)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M3 ,0x34);//������3��ID��0x30
			}
	 else if(Motor_cnt%4 == 3)
			{
			delay_us(200);
			Can_send_motorx( basketballbot.single_expected_speed.M4 ,0x30);//������4��ID��0x34
			}	
}
