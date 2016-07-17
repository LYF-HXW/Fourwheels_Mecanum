#include"stm32f10x.h"

#ifndef AX_H
#define AX_H

#define	OK                      0x00// ����״̬�������ָ�����
#define	ResServoPosInfo         0x01// ������λ����Ϣ
#define	CheckError              0x02// У��λ����
#define	InvalidPosition         0x03// �����ɾ��λ�ó��ִ���
#define	NoSuchServo             0x04// û������������
#define	NoSuchType              0x05// û���������ݰ�����
#define	NoSuchInstructionType 	0x06// û������ָ������
#define NoSuchFile              0x07// û��fianlfile�ļ�
#define HaveFile                0x08// ����finalfile�ļ�,��û�ж�������
#define HaveActionFrame         0x09// �ļ��д��ڶ�������
#define ServoIDNumber           0x0a// �������ͨ��ID��
#define UpLoadActionsNameType   0x0b// �ظ���λ�����Ѿ��洢��΢�������б�

void getServoConnective(void);
void disableServo(uint8_t *p, uint8_t num);
void enableServo(uint8_t *p, uint8_t num);
void getServoPosition(uint8_t *p, uint8_t num);
void moveServoPosition(uint8_t *p, uint8_t num);
void moveServoPosWithSpeed(uint8_t *p, uint8_t num);
void playMicroAction(uint8_t *p, uint16_t poolSize);
void Packet_Reply(USART_TypeDef* USARTx, unsigned char InstrType,						 //lengthֻ����data�ĳ���
		unsigned char * data, unsigned int length);

void TxPacketBroadSynWrite(uint8_t bInstruction, uint8_t bParameterLength);
uint8_t axSendSpeed(uint8_t bID, uint16_t target_speed);

uint8_t TxPacket(uint8_t bID, uint8_t bInstruction, uint8_t bParameterLength);
uint8_t RxPacket(uint8_t bRxPacketLength);

uint8_t axPing(uint8_t bID);
uint8_t axTorqueOn(uint8_t bID);
uint8_t axTorqueOff(uint8_t bID);

void axTorqueOffAll(void);
void axTorqueOnAll(void);
uint8_t axSendPosition(uint8_t bID, uint16_t target_pos, uint16_t target_speed);
uint16_t axReadPosition(uint8_t bID);

//--- Control Table Address ---
//EEPROM AREA
#define P_MODEL_NUMBER_L      0									  //�ͺŴ���L
#define P_MODOEL_NUMBER_H     1									  //�ͺŴ���H
#define P_VERSION             2									  //�̼��汾
#define P_ID                  3									  //ID����ֵ
#define P_BAUD_RATE           4									  //������
#define P_RETURN_DELAY_TIME   5									  //�����ӳ�ʱ��
#define P_CW_ANGLE_LIMIT_L    6									  //��С�Ƕ�L
#define P_CW_ANGLE_LIMIT_H    7									  //��С�Ƕ�H
#define P_CCW_ANGLE_LIMIT_L   8									  //���Ƕȣ�L����CCW������ʱ�룩
#define P_CCW_ANGLE_LIMIT_H   9									  //���Ƕȣ�H��
#define P_SYSTEM_DATA2        10								  //��������
#define P_LIMIT_TEMPERATURE   11							      //��ߵĽ����¶�
#define P_DOWN_LIMIT_VOLTAGE  12								  //��͵Ľ��޵�ѹ
#define P_UP_LIMIT_VOLTAGE    13								  //��ߵĽ��޵�ѹ
#define P_MAX_TORQUE_L        14								  //���ת����L
#define P_MAX_TORQUE_H        15								  //���ת����H
#define P_RETURN_LEVEL        16								  //״̬�����̶�
#define P_ALARM_LED           17								  //LED ���� ��������
#define P_ALARM_SHUTDOWN      18								  //����Ť�ؾ���
#define P_OPERATING_MODE      19
#define P_DOWN_CALIBRATION_L  20
#define P_DOWN_CALIBRATION_H  21
#define P_UP_CALIBRATION_L    22
#define P_UP_CALIBRATION_H    23

#define P_TORQUE_ENABLE         (24)							 //����Ť��
#define P_LED                   (25)						  	//LED
#define P_CW_COMPLIANCE_MARGIN  (26)						   //˳ʱ�����Ա߾�
#define P_CCW_COMPLIANCE_MARGIN (27)						   //��ʱ�����Ա߾�
#define P_CW_COMPLIANCE_SLOPE   (28)						   //˳ʱ������б��
#define P_CCW_COMPLIANCE_SLOPE  (29)						   //��ʱ���ŷ�б��
#define P_GOAL_POSITION_L       (30)						   // Ŀ��λ�ã��ͣ�
#define P_GOAL_POSITION_H       (31)						   // Ŀ��λ�ã��ߣ�
#define P_GOAL_SPEED_L          (32)					 	  // �˶��ٶȣ��ͣ�
#define P_GOAL_SPEED_H          (33)					     // �˶��ٶȣ��ߣ�
#define P_TORQUE_LIMIT_L        (34)					    // Ť�����ƣ��ͣ�
#define P_TORQUE_LIMIT_H        (35)					   //Ť�����ƣ��ߣ�
#define P_PRESENT_POSITION_L    (36)					  //  ��ǰλ�ã��ͣ�
#define P_PRESENT_POSITION_H    (37)				     //	��ǰλ�ã��ߣ�
#define P_PRESENT_SPEED_L       (38)				    //  ��ǰ�ٶȣ��ͣ�
#define P_PRESENT_SPEED_H       (39)				   //	��ǰ�ٶȣ��ߣ�
#define P_PRESENT_LOAD_L        (40)				  //	��ǰ���أ��ͣ�
#define P_PRESENT_LOAD_H        (41)			     //	    ��ǰ���أ��ߣ�
#define P_PRESENT_VOLTAGE       (42)			    //	    ��ǰ��ѹ
#define P_PRESENT_TEMPERATURE   (43)			   //       ��ǰ�¶�
#define P_REGISTERED_INSTRUCTION (44)
#define P_PAUSE_TIME            (45)
#define P_MOVING (46)
#define P_LOCK                  (47)
#define P_PUNCH_L               (48)
#define P_PUNCH_H               (49)

//--- Instruction ---
#define INST_PING           0x01						//��ͨ�Լ�����,�޲����������õ�״̬���ݰ�	  
#define INST_READ           0x02					   	//���ݶ�ȡ,��ȡ���Ʊ��е���ֵ
#define INST_WRITE          0x03						//����д��,����Ʊ���д����ֵ
#define INST_REG_WRITE      0x04						//д��Ĵ���,������д�����ƣ����ڲ���ָ�����֮ǰ���ڱ���ģʽ.ע���д��ָ�������д��ָ�����ƣ���������ָ�����ɵ�ʱ���ǲ�ͬ��
#define INST_ACTION         0x05						//����,����д���ָ�� ,�����ո�ָ���ִ��INST_REG_WRITE�����ݣ������ӳ٣������ͬ�������޷���״̬��
#define INST_RESET          0x06						//��λ,��Dynamixel����Ŀ��Ʊ���ֵ��������������ֵ
#define INST_DIGITAL_RESET  0x07
#define INST_SYSTEM_READ    0x0C
#define INST_SYSTEM_WRITE   0x0D
#define INST_SYNC_WRITE     0x83						// ͬʱд��,����ͬʱ���ƶ��Dynamixel���
#define INST_SYNC_REG_WRITE 0x84

#define CLEAR_BUFFER gbRxBufferReadPointer = gbRxBufferWritePointer
#define DEFAULT_RETURN_PACKET_SIZE 6
#define BROADCASTING_ID 0xfe

#define  AX_TXD  GPIO_SetBits(GPIOB,GPIO_Pin_12); GPIO_ResetBits(GPIOB,GPIO_Pin_13);
#define  AX_RXD  GPIO_SetBits(GPIOB,GPIO_Pin_13); GPIO_ResetBits(GPIOB,GPIO_Pin_12);
//#define  AX_TXD  GPIO_SetBits(GPIOB,GPIO_Pin_12);
//#define  AX_RXD  GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define ACTION_COMPLETE 0
#define ACTION_ERROR 1

#define AX_MAX_NUM 10//�������ţ��������ֻ����0��AX_MAX_NUM-1��
#define PNULL 0

#define DEFAULTSPEED 512
extern volatile uint8_t gbpParameter[];
extern volatile uint8_t gbpRxBuffer[];
extern volatile unsigned char gbpRxInterruptBuffer[];
extern volatile unsigned char gbRxBufferWritePointer;
//volatile uint8_t gbRxBufferReadPointer;
void changeServoID(uint8_t *p, uint8_t num);

#endif
