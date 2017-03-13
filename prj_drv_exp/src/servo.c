
#include "includes.h"

/*
#define CCR1_Val  ((uint16_t)444)
#define CCR2_Val  ((uint16_t)444)
#define CCR3_Val  ((uint16_t)444)
#define CCR4_Val  ((uint16_t)444)
*/
#define CCR1_Val  ((uint16_t)5000)
#define CCR2_Val  ((uint16_t)5000)
#define CCR3_Val  ((uint16_t)5000)
#define CCR4_Val  ((uint16_t)5000)



void PortInit()
{
  


}



#if 0
void Tim2_Cfg()
{
  TIM2_PSCR=0x07;               //Timer2时钟128分频，计算一次8us
  TIM2_ARRH=25;                 //自动重装的值
  TIM2_ARRL=196;                //PWM周期为20000us
  TIM2_CCER1=bit0 | bit4;       // high level,OC1
  TIM2_CCMR1=bit3|bit5|bit6;  //MODE 
  TIM2_CCR1H=0x00;            //占空比
  TIM2_CCR1L=0x00; 

  TIM2_CCER1 |= 0x10;   //开启OC2信号输出脚
  TIM2_CCMR2 = 0x60;   //PWM1模式  
  TIM2_CCMR2 |= 0x08;   //输出比较2预装载使能
  TIM2_CCR2H=0x00;            //占空比
  TIM2_CCR2L=0x00; 
  
  TIM2_IER=0x00;             //更新中断使能 
  TIM2_CR1=bit0;            //enable counter 
}
#endif


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

static void Tim1_Cfg()
{
  TIM1_DeInit();
    
  /* Time Base configuration */
  /*
  TIM1_Period = 4095
  TIM1_Prescaler = 0
  TIM1_CounterMode = TIM1_COUNTERMODE_UP
  TIM1_RepetitionCounter = 0
  */
   TIM1_TimeBaseInit(31, TIM1_COUNTERMODE_UP, 9999, 0);
  
  //TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 888, 0);
  
  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  
  /*
  TIM1_OCMode = TIM1_OCMODE_PWM2
  TIM1_OutputState = TIM1_OUTPUTSTATE_ENABLE
  TIM1_OutputNState = TIM1_OUTPUTNSTATE_ENABLE
  TIM1_Pulse = CCR1_Val
  TIM1_OCPolarity = TIM1_OCPOLARITY_LOW
  TIM1_OCNPolarity = TIM1_OCNPOLARITY_HIGH
  TIM1_OCIdleState = TIM1_OCIDLESTATE_SET
  TIM1_OCNIdleState = TIM1_OCIDLESTATE_RESET
  
  */
  TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
               CCR1_Val, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET); 
  
  /*TIM1_Pulse = CCR2_Val*/
  TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, CCR2_Val,
               TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, 
               TIM1_OCNIDLESTATE_RESET);

  /*TIM1_Pulse = CCR3_Val*/
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
               CCR3_Val, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET);

  /*TIM1_Pulse = CCR4_Val*/
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, CCR4_Val, TIM1_OCPOLARITY_LOW,
               TIM1_OCIDLESTATE_SET);

  /* TIM1 counter enable */
  TIM1_Cmd(ENABLE);

  /* TIM1 Main Output Enable */
  TIM1_CtrlPWMOutputs(ENABLE);
}


void ServoInit()
{
 Tim1_Cfg();
 
}

