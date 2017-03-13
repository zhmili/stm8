
#include "includes.h"
//ULT 003 PD4 - 触发上升沿
//ULT 003 PD3 - 触发下降沿
//    003 PD2 - 输出触发 
//ULT 003 PC3 - 485Enable脚

extern TULT ULT;

void ult_init()
{
  GPIO_WriteLow(GPIOD, GPIO_PIN_2);
  delay_init(SYS_CLK_MHZ);
}

void cacu_dist()
{
  float fdist_mm;
  if(ULT.cap_val2 <= ULT.cap_val1)
  {
    ULT.dist_mm = -1;
  }
  else
  {
    fdist_mm =  13.60*(ULT.cap_val2 - ULT.cap_val1);
    ULT.dist_mm = (uint16_t)(fdist_mm + 0.5);
  }
  
#if PRINT_ON
  printf("get dist : %d \n\r", ULT.dist_mm);
#endif
}

void trig()
{
  int i; 
  tim2_int_en(DISABLE);

  GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
  for(i = 0; i < 45; i++);
  
 // delay_us(30);
  TIM2_SetCounter(0);
  GPIO_WriteLow(GPIOD, GPIO_PIN_2);
  ULT.bt_60_ms = 0;
  
  delay_us(4);
  tim2_int_en(ENABLE);
  
  
#if PRINT_ON
  printf("trig start ....");
#endif
}





