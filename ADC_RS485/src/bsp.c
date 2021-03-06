
#include"includes.h"

/* Private functions ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/
u8 BlinkSpeed = 6;
int NumberOfStart;
int CheckFlag = 1;

Tanalog analog;

/**
  ******************************************************************************
  * @brief Initialize all the TS keys
  * @par Parameters:
  * None
  * @retval void None  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void ExtraCode_Init(void)
{
  u8 i;
  /* All keys are implemented and enabled */
  
  for (i = 0; i < NUMBER_OF_SINGLE_CHANNEL_KEYS; i++)
  {
    sSCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sSCKeyInfo[i].Setting.b.ENABLED = 1;
    sSCKeyInfo[i].DxSGroup = 0x01; /* Put 0x00 to disable the DES on these pins */
  }

#if NUMBER_OF_MULTI_CHANNEL_KEYS > 0
  for (i = 0; i < NUMBER_OF_MULTI_CHANNEL_KEYS; i++)
  {
    sMCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sMCKeyInfo[i].Setting.b.ENABLED = 1;
    sMCKeyInfo[i].DxSGroup = 0x01; /* Put 0x00 to disable the DES on these pins */
  }
#endif

  enableInterrupts();
}


/**
  ******************************************************************************
  * @brief Adjustable led blinking speed using touch sensing keys
  * KEY1: LED1 is blinking
  * KEY1: LED1 is blinking faster
  * KEY1: LED1 don't blink anymore
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void ExtraCode_StateMachine(void)
{
  if ((TSL_GlobalSetting.b.CHANGED) && (TSLState == TSL_IDLE_STATE))
  {
    TSL_GlobalSetting.b.CHANGED = 0;

    if (sSCKeyInfo[0].Setting.b.DETECTED) /* KEY 1 touched */
    {
      BlinkSpeed++;
      BlinkSpeed = BlinkSpeed % 3;
    }
  }

  switch (BlinkSpeed)
  {
    case 0 :
      GPIO_WriteHigh(GPIOD, GPIO_PIN_0);
      break;

    case 1 :
      if (TSL_Tick_Flags.b.User1_Flag_100ms == 1)
      {
        Delay(&Toggle, 2*MilliSec);
      }
      break;

    case 2 :
      if (TSL_Tick_Flags.b.User1_Flag_100ms == 1)
      {
        Delay(&Toggle, 1*MilliSec);
      }
      break;

    default :
      if (TSL_Tick_Flags.b.User1_Flag_100ms == 1)
      {
        Delay(&Toggle, 1*Sec);
      }
  }
 
}

/**
  ******************************************************************************
  * @brief Configures clocks
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void CLK_Configuration(void)
{
  /* Fmaster = 16MHz */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

/**
  ******************************************************************************
  * @brief Configures GPIOs
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void GPIO_Configuration(void)
{
  /* GPIOD reset */
  GPIO_DeInit(GPIOD);
  /* Configure PD0 (LED1) as output push-pull low (led switched on) */
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOA, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOA, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);
}


/**
  ******************************************************************************
  * @brief Delay before completing the action
  * @param[in] function action() to be performed once the delay past
 * @param[in]
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void Delay(void action(void), int NumberofTIMCycles)
{
  if ((CheckFlag) != 0)
    NumberOfStart = NumberofTIMCycles;
  if (NumberOfStart != 0)
  {
    TSL_Tick_Flags.b.User1_Start_100ms = 1;
    CheckFlag = 0;
  }
  if (TSL_Tick_Flags.b.User1_Flag_100ms)
  {
    TSL_Tick_Flags.b.User1_Flag_100ms = 0;
    NumberOfStart--;
  }
  if (NumberOfStart == 0)
  {
    action();
    CheckFlag = 1;
  }
}


/**
  ******************************************************************************
  * @brief Toggle PD0 (Led LD1)
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
int i;
void Toggle(void)
{ 
  i++;
  if(i>200)
  {
    i=0;
  GPIO_WriteReverse(GPIOA, GPIO_PIN_6);
  }
}

void UART2_Configuration(void)
{
  UART2_DeInit();
  UART2_Init((u32)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
  UART2_ITConfig(UART2_IT_TC, DISABLE);
  UART2_ITConfig(UART2_IT_TXE, DISABLE);
  
  UART2_ITConfig(UART2_IT_RXNE, ENABLE);
  UART2_Cmd(ENABLE);
}

/**
  * @brief  Configure TIM4 to generate an update interrupt each 1ms 
  * @param  None
  * @retval None
  */
void TIM4_Configuration(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */
  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
  /* enable interrupts */
}

void ITC_Configuration()
{
   ITC_SetSoftwarePriority(ITC_IRQ_TIM4_OVF, ITC_PRIORITYLEVEL_3);
  // ITC_SetSoftwarePriority(ITC_IRQ_UART2_TX, ITC_PRIORITYLEVEL_2);
   ITC_SetSoftwarePriority(ITC_IRQ_UART2_RX, ITC_PRIORITYLEVEL_1); 
   enableInterrupts(); 
}

void GetAnalogData(Tanalog* t_analog)
{
  u8 i;
  u32 add;
  u16 *pb,*pc,*pd,mid;
  u8 min_ch,max_ch;
  u16* p = (u16*) t_analog;
  pb = pc = pd = p;
  pb++;// 线路板上的 （9通道 第一位对应实际 芯片第8路（0-8），8通道扩展部分 第一通道（对应 芯片第0通道)
  pc++;
  pd++;
  min_ch = max_ch = 1;
  
     *p++ = ADC1_GetBufferValue(9);
    for(i=0;i<8;i++)
    {
      *p++ = ADC1_GetBufferValue(i);
      add =+ *p;
    }

    mid = *pb++;
    for(i=0;i<7;i++)
    {
      if(mid < *pb)
      {}
      else
      {
      mid = *pb;
      max_ch++;
      }
      pb++;
    }
    
    t_analog->an_max_1_8 = mid;
    t_analog->an_max_chx_1_8 = max_ch;
    
    mid = *pc++;
    for(i = 0; i<7 ; i++)
    {
      if(mid > *pc)
      {}
      else
      {
        mid = *pc;
        min_ch++;
      }
      pc++;
    }
    t_analog->an_min_1_8 = mid;
    t_analog->an_min_chx_1_8 = min_ch; 
}







/****************** (c) 2008  STMicroelectronics ******************************/
