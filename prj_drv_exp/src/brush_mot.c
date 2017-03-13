
#include "includes.h"

TBRUSH_MOT_CFG BRUSH_MOT_CFG;


/******************************************************************************************
* 函数功能	: 
* 输入参数	: 
* 返回数值	: 
*******************************************************************************************/
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


/******************************************************************************************
* 函数功能	: 
* 输入参数	: 
* 返回数值	: 
*******************************************************************************************/
static void Tim_Cfg()
{ 
  TIM1_DeInit();
   
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, MOT_FREQ_16K, 0);
  
  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  
  TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
               MOT_CLK_LOW, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET); 
  
  /*TIM1_Pulse = CCR2_Val*/
  TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE, MOT_CLK_LOW,
               TIM1_OCPOLARITY_LOW, TIM1_OCPOLARITY_LOW, TIM1_OCIDLESTATE_SET, 
               TIM1_OCNIDLESTATE_RESET);

  /*TIM1_Pulse = CCR3_Val*/
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
               MOT_CLK_LOW, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET);
  
  /* TIM1 counter enable */
  TIM1_Cmd(ENABLE);
  
  /* TIM1 Main Output Enable */
  TIM1_CtrlPWMOutputs(ENABLE);
  
  
 //TIM2 cfg
    /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, MOT_FREQ_16K);
  
  /* PWM1 Mode configuration: Channel1 */ 
  TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,MOT_CLK_LOW, TIM1_OCPOLARITY_LOW);
  TIM2_OC1PreloadConfig(ENABLE);
  
  /* PWM1 Mode configuration: Channel2 */ 
  TIM2_OC2Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,MOT_CLK_LOW, TIM1_OCPOLARITY_LOW);
  TIM2_OC2PreloadConfig(ENABLE);
  
  /* PWM1 Mode configuration: Channel3 */         
  TIM2_OC3Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,MOT_CLK_LOW, TIM1_OCPOLARITY_LOW);
  TIM2_OC3PreloadConfig(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
  
}


/******************************************************************************************
* 函数功能	: 
* 输入参数	: 
* 返回数值	: 
*******************************************************************************************/
void BrushMotInit()
{
  Port_Cfg();
  Tim_Cfg();
  BRUSH_MOT_CFG.pMtReset = (u8*)(I2C_INF.RxBuf + MOTRES_LOC);
  BRUSH_MOT_CFG.pMtCmd = (u8*)(I2C_INF.RxBuf + MTCMD_LOC);
  BRUSH_MOT_CFG.pSpeed = (s8*)(I2C_INF.RxBuf + SPEED_LOC);
  BRUSH_MOT_CFG.pMtDlyMs = (u16*)(I2C_INF.RxBuf + DLY_LOC);
  BRUSH_MOT_CFG.pIOCmd = (u8*)(I2C_INF.RxBuf + IOCMD_LOC);
  I2C_INF.TxBuf[0] = (BRUSH_MOT_CFG.MotId&0x0ff);
  I2C_INF.TxBuf[1] = ((BRUSH_MOT_CFG.MotId >> 8)&0x0ff);
}


/******************************************************************************************
* 函数功能	: 
* 输入参数	: 
* 返回数值	: 
*******************************************************************************************/
void IO_Oper(int id, int x)
{
  switch(id)
  {

  case 1:
        IO1(x)
          break;
  case 2:
        IO2(x)
          break;
  case 3:
        IO3(x);
          break;

  case 4:
        IO4(x);
          break;
  default: 
          break;      
  }
}





/******************************************************************************************
* 函数功能	: 停止一个电机
* 输入参数	: id  需要被关闭的电机，1，2，3，4 
* 返回数值	: 无 
*******************************************************************************************/
/*注意		 :																		   */
/*版本时间	 : 20080926 																   */
/*版本时间	 : 20080929 00 控制信号时为关断									   */
void off(int id)
{
  
switch(id)
{

case 1:
	CMOTOR1(0);
	CMOTOR1_2(0);
	break;
case 2:
	CMOTOR2(0);
	CMOTOR2_2(0);
	break;
case 3:
	CMOTOR3(0);
	CMOTOR3_2(0);
	break;

case 4:
	CMOTOR4(0);
	CMOTOR4_2(0);
	break;
case 5:
	CMOTOR5(0);
	CMOTOR5_2(0);
	break;
case 6:
	CMOTOR6(0);
	CMOTOR6_2(0);
	break;

default: 
        break;      

}
}


/******************************************************************************************
* 函数功能	: 以功率级别p启动电机m
* 输入参数	: m   所要启动的电机1-4
*				  p    所要设置的功率级别100到反向全功率级别-100
* 返回数值	: 无
*******************************************************************************************/
/*注意		:																		   */
/*版本时间	: 20080926 								   */
/*版本时间	 : 20080929 00 控制信号时为关断									   */
/*版本时间      : 20081015 motor2和motor4 极性相反，驱动板设置所致      */
/*版本时间      : 20090224 motor2和motor4 级性在反，修正为 20080926 设置*/

void motor(int m, int p)
{	
  u8 x;
  u8 y;
  u8 i2c_w_ret;
  u16 absp;
  int op ;     
  op = p;
  if(op == 0)
  {
    x = 0;
    y = 0;
  }else if(op<0){
    x = 0;
    y = 1;	
  }else{
    x = 1;
    y = 0;
  }
   
   absp = abs(op)*10 - 2;     // 简单处理 2000 - 2 = 1999 20080921
        
   switch(m)                     
   {
       case 6:
	CMOTOR6(x);
	CMOTOR6_2(y);
        TIM2->CCR3H = (uint8_t)(absp >> 8);
        TIM2->CCR3L = (uint8_t)(absp);
	break;
	
	case 5:
	CMOTOR5(x);
	CMOTOR5_2(y);
        TIM2->CCR2H = (uint8_t)(absp >> 8);
        TIM2->CCR2L = (uint8_t)(absp);
	break;
 
	case 4:
	CMOTOR4(x);
	CMOTOR4_2(y);
        TIM2->CCR1H = (uint8_t)(absp >> 8);
        TIM2->CCR1L = (uint8_t)(absp);
	break;   
          
       case 3:
	CMOTOR3(x);
	CMOTOR3_2(y);
        TIM1->CCR3H = (uint8_t)(absp >> 8);
        TIM1->CCR3L = (uint8_t)(absp);
	break;
	
	case 2:
	CMOTOR2(x);
	CMOTOR2_2(y);
        TIM1->CCR2H = (uint8_t)(absp >> 8);
        TIM1->CCR2L = (uint8_t)(absp);
	break;
 
	case 1:
	CMOTOR1(x);
	CMOTOR1_2(y);
        TIM1->CCR1H = (uint8_t)(absp >> 8);
        TIM1->CCR1L = (uint8_t)(absp);
	break;
	
	default: 
          break;
   }
}


void Mot_Reset()
{
  int i;
        TIM2->CCR3H = (uint8_t)(MOT_CLK_LOW >> 8);
        TIM2->CCR3L = (uint8_t)(MOT_CLK_LOW);

        TIM2->CCR2H = (uint8_t)(MOT_CLK_LOW >> 8);
        TIM2->CCR2L = (uint8_t)(MOT_CLK_LOW);

        TIM2->CCR1H = (uint8_t)(MOT_CLK_LOW >> 8);
        TIM2->CCR1L = (uint8_t)(MOT_CLK_LOW);

        TIM1->CCR3H = (uint8_t)(MOT_CLK_LOW >> 8);
        TIM1->CCR3L = (uint8_t)(MOT_CLK_LOW);

        TIM1->CCR2H = (uint8_t)(MOT_CLK_LOW >> 8);
        TIM1->CCR2L = (uint8_t)(MOT_CLK_LOW);
	
        TIM1->CCR1H = (uint8_t)(MOT_CLK_LOW >> 8);
        TIM1->CCR1L = (uint8_t)(MOT_CLK_LOW);
	
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
  
  for(i = 0; i < FAN_NUM; i++)
  {
    BRUSH_MOT_CFG.pIOCmd[0] = 0;
  }

#if 0
  for(i = 0; i< MOT_NUM;i++)
  {
  
  BRUSH_MOT_CFG.pMtCmd[i] = MT_NOCMD;
  BRUSH_MOT_CFG.pSpeed[i] = MOT_CLK_LOW;
  }
#endif
  
}

/******************************************************************************************
* 函数功能	: 
* 输入参数	: 
* 返回数值	: 
*******************************************************************************************/
void BrushMotRun()
{
  u8 i;
  
  static s8 spt;
  
  while(1)
  {

    if(BRUSH_MOT_CFG.pMtReset[0] == MT_RES)
    {
      Mot_Reset();
      BRUSH_MOT_CFG.pMtReset[0] = MT_NRES;
    }

    
    for(i = 0; i < MOT_NUM; i++)
    {
       switch(BRUSH_MOT_CFG.pMtCmd[i])
       {
       case MT_RUN:
         motor(i + 1, BRUSH_MOT_CFG.pSpeed[i]);
         if(i == 0)
         {
         printf("MT1_RUN \n\r");
         }
         else if(i== 1)
         {
         printf("MT2_RUN \n\r");
         }
          else if(i== 2)
         {
         printf("MT3_RUN \n\r");
         }
         break;
       
       case MT_STOP:
         off(i + 1);
         printf("MT_STOP \n\r");
         break;
         
       case MT_RUN_DLY:
         
         //printf("MT_RUN_DLY \n\r");
         break;
       
       
       default:
         break;
       }
       BRUSH_MOT_CFG.pMtCmd[i] = MT_NOCMD;
     }
     
     for(i = 0; i < FAN_NUM; i++)
     {
      IO_Oper(i+1 , BRUSH_MOT_CFG.pIOCmd[i]);
     }
  }
}


