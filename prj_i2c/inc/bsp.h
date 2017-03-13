/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H
#define __BSP_H

#define PRINT_ON    0
#define SYS_CLK_MHZ 16


/* Private typedef -----------------------------------------------------------*/

typedef            void      CPU_VOID;
typedef            char      CPU_CHAR;                          /*  8-bit character                                     */
typedef  unsigned  char      CPU_BOOLEAN;                       /*  8-bit boolean or logical                            */
typedef  unsigned  char      CPU_INT08U;                        /*  8-bit unsigned integer                              */
typedef    signed  char      CPU_INT08S;                        /*  8-bit   signed integer                              */
typedef  unsigned  short     CPU_INT16U;                        /* 16-bit unsigned integer                              */
typedef    signed  short     CPU_INT16S;                        /* 16-bit   signed integer                              */
typedef  unsigned  long      CPU_INT32U;                        /* 32-bit unsigned integer                              */
typedef    signed  long      CPU_INT32S;                        /* 32-bit   signed integer                              */
typedef            float     CPU_FP32;                          /* 32-bit floating point                                */
typedef            double    CPU_FP64;                          /* 64-bit floating point                                */



typedef struct analog{
  u16 an_ch1;             //0x8000
  u16 an_ch2;             //0x8001
  u16 an_ch3;             //0x8002
  u16 an_ch4;             //
  u16 an_ch5;
  u16 an_ch6;
  u16 an_ch7;
  u16 an_ch8;
  u16 an_ch9;
  u16 an_ave_1_8;
  u16 an_max_1_8;
  u16 an_max_chx_1_8;
  u16 an_min_1_8;
  u16 an_min_chx_1_8;

}Tanalog;



/* Private define ------------------------------------------------------------*/
#define MilliSec       1
#define Sec           10

// from os_cfg.h
#define OS_Q_EN                   1    /* Enable (1) or Disable (0) code generation for QUEUES         */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void CLK_Configuration(void);
void GPIO_Configuration(void);
void ExtraCode_Init(void);
void ExtraCode_StateMachine(void);
void Delay(void action(void), int NumberofTIMCycles);
void Toggle(void);
void ITC_Configuration(void);
void TIM4_Configuration(void);
void UART2_Configuration(void);
void GetAnalogData(Tanalog* t_analog);

#endif