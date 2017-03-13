#ifndef __I2C_SLAVE_H
#define __I2C_SLAVE_H

#include "includes.h"

#define MAX_BUFFER     32

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

//brush_mot 

//RxBuf[0] = 主机写入的地址 8位模式
//RxBuf[1] = 保留

//RxBuf[2] = 主机写入的数据 电机1 控制命令，开启，停止, 延时控制
//RxBuf[3] = 主机写入的数据 电机2 控制命令，开启，停止, 延时控制
//RxBuf[4] = 主机写入的数据 电机3 控制命令，开启，停止, 延时控制
//RxBuf[5] = 主机写入的数据 电机4 控制命令，开启，停止, 延时控制
//RxBuf[6] = 主机写入的数据 电机5 控制命令，开启，停止, 延时控制
//RxBuf[7] = 主机写入的数据 电机6 控制命令，开启，停止, 延时控制

//RxBuf[8] = 主机写入的数据 电机1 pwm值 正负百分比
//RxBuf[9] = 主机写入的数据 电机2 pwm值
//RxBuf[10] = 主机写入的数据 电机3 pwm值
//RxBuf[11] = 主机写入的数据 电机4 pwm值
//RxBuf[12] = 主机写入的数据 电机5 pwm值
//RxBuf[13] = 主机写入的数据 电机6 pwm值

//RxBuf[14] = 主机写入的数据 电机1 dly值 低8位
//RxBuf[15] = 主机写入的数据 电机1 dly值 高8位
//RxBuf[16] = 主机写入的数据 电机2 dly值 低8位
//RxBuf[17] = 主机写入的数据 电机2 dly值 高8位
//RxBuf[18] = 主机写入的数据 电机3 dly值 低8位
//RxBuf[19] = 主机写入的数据 电机3 dly值 高8位

//RxBuf[20] = 主机写入的数据 电机4 dly值 低8位
//RxBuf[21] = 主机写入的数据 电机4 dly值 高8位
//RxBuf[22] = 主机写入的数据 电机5 dly值 低8位
//RxBuf[23] = 主机写入的数据 电机5 dly值 高8位
//RxBuf[24] = 主机写入的数据 电机6 dly值 低8位
//RxBuf[25] = 主机写入的数据 电机6 dly值 高8位

//RxBuf[26] = 主机写入的数据 风扇1 命令
//RxBuf[27] = 主机写入的数据 风扇2 命令
//RxBuf[28] = 主机写入的数据 风扇3 命令
//RxBuf[29] = 主机写入的数据 风扇4 命令
//RxBuf[30] = 系统复位命令

//TxBuf[0]  = 读取的数据区1  模块名低
//TxBuf[1]  = 读取的数据区2  模块名高
//TxBuf[2]  = 读取的数据区3  
//TxBuf[3]  = 读取的数据区4
//TxBuf[4]  = 读取的数据区5
//TxBuf[5]  = 读取的数据区4
//TxBuf[6]  = 读取的数据区5
//TxBuf[7]  = 读取的数据区4
//TxBuf[8]  = 读取的数据区5



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
