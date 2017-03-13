#ifndef __I2C_SLAVE_H
#define __I2C_SLAVE_H
#include "stm8s.h"

#define ADDR_LEN_16    0
#define MAX_BUFFER  32

//I2C EEROM 的读取过程
//1\ 主机START
//2\ 主机发送 从机地址+写功能
//   从机ACK
//3\ 主机发送 从机内的地址（写入从机) 起始地址
//   从机ACK
//4\ 主机发送 主机START
//5\ 主机发送 从机地址+读命令
//   从机ACK
//7\ 主机读取 ..。
//   主机ACK
//8\ 主机STOP

//I2C EEROM 的写入过程
//1\ 主机START
//2\ 主机发送 从机地址+写功能
//   从机ACK
//3\ 主机发送 从机内的地址（写入从机) 起始地址
//   从机ACK
//4\ 主机发送 主机START
//5\ 主机发送 从机地址+写命令
//   从机ACK
//7\ 主机写入 ...
//   从机ACK
//8\ 主机STOP

//RxBuf[0] = 主机写入的低地址
//RxBuf[1] = 主机写入的高地址
//RxBuf[2] = 主机写入的数据1（可以是命令）
//RxBuf[3] = 主机写入的数据2 
//...

//TxBuf[0]  = 读取的数据区1
//TxBuf[1]  = 读取的数据区2
//TxBuf[2]  = 读取的数据区3

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
