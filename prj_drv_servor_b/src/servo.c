
#include "includes.h"

TSERVO SERVO;




/******************************************************************************************
* 函数功能	: 
* 输入参数	: 
* 返回数值	: 
*******************************************************************************************/

#if 0
static void Port_Cfg()
{
  GPIO_Init(GPIOA, PO3|POM5_2, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOB, POM3_2|POM2_2|PO1|PO2|POM1_2|POM2_1|POM1_1, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOC, PO4|POM4_2|POM5_1|POM4_1, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, POM6_1|POM6_2|EN485, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOE, POM1_1, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOF, POM3_1, GPIO_MODE_OUT_PP_LOW_FAST);
  
  CMOTOR1(0);
  CMOTOR1_2(0);
  CMOTOR2(0);
  CMOTOR2_2(0)
  CMOTOR3(0);
  CMOTOR3_2(0)
  CMOTOR4(0);
  CMOTOR4_2(0);
  CMOTOR5(0);
  CMOTOR5_2(0)
  CMOTOR6(0);
  CMOTOR6_2(0);
  IO1(0);
  IO2(0);
  IO3(0);
  IO4(0);
  
  
}
#endif


static void Tim2_Cfg()
{
  
//TIM2 cfg
    /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_32, SER_FREQ_50Hz);
  
  /* PWM1 Mode configuration: Channel2 */ 
  TIM2_OC3Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,MOT_CLK_LOW, TIM1_OCPOLARITY_LOW);
  TIM2_OC3PreloadConfig(ENABLE);
  
  TIM2_ARRPreloadConfig(ENABLE);
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);

}



/******************************************************************************************
* 函数功能	: 伺服电机设置
* 输入参数	: s	1-6 伺服电机编号
*		: p  	0-1000	设置伺服电机输入的转动量
* 返回数值	: void
* 说明          :舵机参数  0.5ms - 2.5ms 之间
*1000 - 20ms    
*1000 - 20ms     200 - 0.4ms 250 - 0.5ms  500 - 1ms 750 - 1.5ms  1000 - 2ms 1250 - 2.5ms 1350 -2.6ms
*200 -1200 --    Futaba S3003
*那英特 0 - 4800 --> 0 - 1000
*******************************************************************************************/
/*注意		:																		   */
/*版本时间	: 20080926 																   */
void servo(int p)
{
  static unsigned int i;
  i = p+250;
  SERVO_TIM->SERVO_TIM_CH_H = (i>>8)&(0x0FF); 
  SERVO_TIM->SERVO_TIM_CH_L = (i&0x0FF);  
  
  
}

//16M 50HZ
//TIM1 counter clock = TIMxCLK / (Prescaler +1) 
//                   = 16M/32 = 500K  
//                              ->Prescaler = 31
//                                                      
//TIMx ARR Register = 10000 => TIMx Frequency = TIMxcounter clock/(9999 + 1)= 500K/10000 = 50HZ
//
//                              ->ARR = 9999


//TIM1 counter clock = TIMxCLK / (Prescaler +1) 
//                    
//                              ->Prescaler = 0
//                                                      
//TIMx ARR Register = 10000 => TIMx Frequency = TIMxcounter clock/(9999 + 1)= 500K/10000 = 50HZ
//
//                              ->ARR = 9999

//16M 16K -> 160000Hz   16000/(x+1) = 16  ->ARR = 
//   16x+16 = 16000 -> 1x+1 = 1000 -> x = 999

//PWM 




void ServoInit()
{
  
 Tim2_Cfg();
 SERVO.servo_id = SERVO_ADDR;
 
 I2C_INF.RxBuf[LOC_LOC] = (SERVO_BASE&0xFF);
 I2C_INF.RxBuf[LOC_LOC+1] = ((SERVO_BASE>>8)&0xFF);
 
 SERVO.ploc = (s8*)(I2C_INF.RxBuf + LOC_LOC);
 
 I2C_INF.TxBuf[0] = (SERVO.servo_id&0x0ff);
 I2C_INF.TxBuf[1] = ((SERVO.servo_id >> 8)&0x0ff);  
   
}


void ServoRun()
{
  static unsigned int p;
  
  while(1)
  {
#if 1
    p = SERVO.ploc[0] + SERVO.ploc[1]<<8;
    
    servo(SERVO.ploc[0] + (SERVO.ploc[1]<<8));
    printf("ServoRun\n\r"); 
#endif
  }

}





