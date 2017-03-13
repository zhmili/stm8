#ifndef __I2C_SLAVE_H
#define __I2C_SLAVE_H
#include "stm8s.h"

#define ADDR_LEN_16    0
#define MAX_BUFFER  32

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


typedef enum i2c_cd{
  
  GET_8ADDR_DT = 0,
  SET_CMD = 1
    
}EI2C_CMD;



typedef struct i2c_parm{  
 u8 RxBuf[MAX_BUFFER];
 u8 RxLoc;
 u8 TxBuf[MAX_BUFFER];
 u8 TxLoc;
 
}TI2C_PARM;


extern TI2C_PARM I2C_PARM;

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
