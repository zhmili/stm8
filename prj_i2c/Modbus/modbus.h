#ifndef __MODBUS_H__
#define __MODBUS_H__



typedef  unsigned char  uint8 ;	
typedef unsigned long	uint32;
typedef  unsigned  short uint16;

#define RS485_SEND      GPIO_WriteHigh(GPIOC, GPIO_PIN_3);

#define RS485_RECEIVE   GPIO_WriteLow(GPIOC, GPIO_PIN_3);

#define UART_TIME_REC_OUT   5



void timeInterrupt(void);
void modbusInit(void);
void timeProc(void);
void commIntProc(void);
void beginSend(void);
void checkComm0Modbus(void);
void readCoil(void);
void readRegisters(void);
void forceSingleCoil(void);
void presetSingleRegister(void);
void presetMultipleRegisters(void);
void forceMultipleCoils(void);
uint16 getRegisterVal(uint16 addr,uint16 *tempData);
uint16 setRegisterVal(uint16 addr,uint16 tempData);
uint16 getCoilVal(uint16 addr,uint16 *tempData);
uint16 setCoilVal(uint16 addr,uint16 tempData);
u16* GetAddress(u16 address);


#endif