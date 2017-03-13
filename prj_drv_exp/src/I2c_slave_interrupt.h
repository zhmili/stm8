#ifndef __I2C_SLAVE_H
#define __I2C_SLAVE_H

#include "includes.h"

#define MAX_BUFFER     32

//I2C EEROM �Ķ�ȡ����
//1\ ����START
//2\ �������� �ӻ���ַ+д����
//   �ӻ�ACK
//3\ �������� �ӻ��ڵĵ�ַ��д��ӻ�) ��ʼ��ַ
//   �ӻ�ACK
//4\ �������� ����START
//5\ �������� �ӻ���ַ+������
//   �ӻ�ACK
//7\ ������ȡ ..��
//   ����ACK
//8\ ����STOP

//I2C EEROM ��д�����
//1\ ����START
//2\ �������� �ӻ���ַ+д����
//   �ӻ�ACK
//3\ �������� �ӻ��ڵĵ�ַ��д��ӻ�) ��ʼ��ַ
//   �ӻ�ACK
//4\ �������� ����START
//5\ �������� �ӻ���ַ+д����
//   �ӻ�ACK
//7\ ����д�� ...
//   �ӻ�ACK
//8\ ����STOP

//RxBuf[0] = ����д��ĵ͵�ַ
//RxBuf[1] = ����д��ĸߵ�ַ
//RxBuf[2] = ����д�������1�����������
//RxBuf[3] = ����д�������2 
//...

//TxBuf[0]  = ��ȡ��������1
//TxBuf[1]  = ��ȡ��������2
//TxBuf[2]  = ��ȡ��������3

//TxBuf[2]  = 
//TxBuf[2]  = 
//......

//brush_mot 

//RxBuf[0] = ����д��ĵ�ַ 8λģʽ
//RxBuf[1] = ����

//RxBuf[2] = ����д������� ���1 �������������ֹͣ, ��ʱ����
//RxBuf[3] = ����д������� ���2 �������������ֹͣ, ��ʱ����
//RxBuf[4] = ����д������� ���3 �������������ֹͣ, ��ʱ����
//RxBuf[5] = ����д������� ���4 �������������ֹͣ, ��ʱ����
//RxBuf[6] = ����д������� ���5 �������������ֹͣ, ��ʱ����
//RxBuf[7] = ����д������� ���6 �������������ֹͣ, ��ʱ����

//RxBuf[8] = ����д������� ���1 pwmֵ �����ٷֱ�
//RxBuf[9] = ����д������� ���2 pwmֵ
//RxBuf[10] = ����д������� ���3 pwmֵ
//RxBuf[11] = ����д������� ���4 pwmֵ
//RxBuf[12] = ����д������� ���5 pwmֵ
//RxBuf[13] = ����д������� ���6 pwmֵ

//RxBuf[14] = ����д������� ���1 dlyֵ ��8λ
//RxBuf[15] = ����д������� ���1 dlyֵ ��8λ
//RxBuf[16] = ����д������� ���2 dlyֵ ��8λ
//RxBuf[17] = ����д������� ���2 dlyֵ ��8λ
//RxBuf[18] = ����д������� ���3 dlyֵ ��8λ
//RxBuf[19] = ����д������� ���3 dlyֵ ��8λ

//RxBuf[20] = ����д������� ���4 dlyֵ ��8λ
//RxBuf[21] = ����д������� ���4 dlyֵ ��8λ
//RxBuf[22] = ����д������� ���5 dlyֵ ��8λ
//RxBuf[23] = ����д������� ���5 dlyֵ ��8λ
//RxBuf[24] = ����д������� ���6 dlyֵ ��8λ
//RxBuf[25] = ����д������� ���6 dlyֵ ��8λ

//RxBuf[26] = ����д������� ����1 ����
//RxBuf[27] = ����д������� ����2 ����
//RxBuf[28] = ����д������� ����3 ����
//RxBuf[29] = ����д������� ����4 ����
//RxBuf[30] = ϵͳ��λ����

//TxBuf[0]  = ��ȡ��������1  ģ������
//TxBuf[1]  = ��ȡ��������2  ģ������
//TxBuf[2]  = ��ȡ��������3  
//TxBuf[3]  = ��ȡ��������4
//TxBuf[4]  = ��ȡ��������5
//TxBuf[5]  = ��ȡ��������4
//TxBuf[6]  = ��ȡ��������5
//TxBuf[7]  = ��ȡ��������4
//TxBuf[8]  = ��ȡ��������5



typedef struct i2c_inf{  
 u8 RxBuf[MAX_BUFFER];
 u8 RxLoc;
 u8 TxBuf[MAX_BUFFER];
 u8 TxLoc;
}TI2C_INF;


extern TI2C_INF I2C_INF;

/********************** EXTERNAL FUNCTION **********************************/  
	void transaction_begin(void);
	void transaction_end(void);
	void byte_received(u8 u8_RxData);
	u8 byte_write(void);
	void Init_I2C(void);
#if 0
	#ifdef _RAISONANCE_
		void I2C_Slave_check_event(void) interrupt 19;
	#endif
	#ifdef _COSMIC_ 
			@far @interrupt void I2C_Slave_check_event(void);
	#endif
#else
        void I2C_Slave_check_event(void);            
#endif                       
	
/********************** I2C configuration variables *****************************/  
	/* Define I2C Address mode ---------------------------------------------------*/
	#define I2C_slave_7Bits_Address

	/* Define Slave Address  -----------------------------------------------------*/
	#ifdef I2C_slave_10Bits_Address
		#define SLAVE_ADDRESS 0x3F0
	#endif 

	#ifdef I2C_slave_7Bits_Address
		#define SLAVE_ADDRESS 0xA0
	#endif
        
	
#endif /*__I2C_SLAVE_H*/


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
