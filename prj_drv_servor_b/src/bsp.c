
#include"includes.h"

/* Private functions ---------------------------------------------------------*/
#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int putchar (char c)
#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#endif /* _RAISONANCE_ */


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
#if 0
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
#endif

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
//  GPIO_DeInit(GPIOD);
  /* Configure PD0 (LED1) as output push-pull low (led switched on) */
#ifdef STM8S003

    /* Initialize I/O in Input Mode with Interrupt for Joystick */
//  GPIO_Init(GPIOD, GPIO_PIN_4,GPIO_MODE_IN_FL_IT);              //pd4 为下降沿中断
  
#if 0
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);//
  GPIO_Init(GPIOD, GPIO_PIN_3|GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);     
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_IN_PU_NO_IT);//发送数据IO  
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);//接受数据IO  
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);//
#endif
  
#endif  
  
#ifdef STM8S105
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOA, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOA, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);
#endif 
  
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
#if 0
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
#endif

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
#if 0
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
#endif

#if 0
void tim1_cap_config(void)
{
  TIM1_ICInit( TIM1_CHANNEL_1, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI,
               TIM1_ICPSC_DIV8, 0x0);
  
  TIM1_ICInit( TIM1_CHANNEL_2, TIM1_ICPOLARITY_FALLING, TIM1_ICSELECTION_DIRECTTI,
               TIM1_ICPSC_DIV8, 0x0);
  
  /* Enable TIM1 */
  TIM1_Cmd(ENABLE);
  
  /* Clear CC1 Flag*/
  TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  /* wait a capture on CC1 */
  while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue1 = TIM1_GetCapture1();
  TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  
  /* wait a capture on cc1 */
  while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue2 = TIM1_GetCapture1();
  TIM1_ClearFlag(TIM1_FLAG_CC1);
}
#endif



//16 -> 1M -> 1us -> 63ms
//32 -> 0.5M -> 2us -> 
//64 -> 0.25M -> 4uS ->
//128-> 0.125M -> 8us -> 

void tim2_cap_config(void)
{
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_PRESCALER_128, 65535);
  //TIM2_ICPSC_DIV8 
  
  //00: No prescaler, capture is made each time an edge is detected on the capture input
  //01: Capture is made once every 2 events 
  TIM2_ICInit( TIM2_CHANNEL_1, TIM2_ICPOLARITY_RISING, TIM2_ICSELECTION_DIRECTTI,
               TIM2_ICPSC_DIV1, 0x0);
  
  TIM2_ICInit( TIM2_CHANNEL_2, TIM2_ICPOLARITY_FALLING, TIM2_ICSELECTION_DIRECTTI,
               TIM2_ICPSC_DIV1, 0x0);
  
  TIM2_ARRPreloadConfig(ENABLE);
  /* Clear CC1 Flag*/
  TIM2_ClearFlag(TIM2_FLAG_CC1);
  TIM2_ClearFlag(TIM2_FLAG_CC2);
  
  /* Enable update interrupt */
  TIM2_ITConfig(TIM2_IT_CC1, ENABLE);
  /* Enable update interrupt */
  TIM2_ITConfig(TIM2_IT_CC2, ENABLE);
  
  /* Enable TIM1 */
  TIM2_Cmd(ENABLE);
}

void tim2_int_en(FunctionalState NewState)
{
  TIM2_ITConfig(TIM2_IT_CC1, NewState);
  TIM2_ITConfig(TIM2_IT_CC2, NewState);
  TIM2_Cmd(NewState);
}



#if 0

void tim2_config(void)
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
  // 超声波最少需要5mm 对应的时间是 340mm/ms , 0.34mm/us , 精度到3mm -> 6mm测距
  // 最小间隔设置到10us , 
  // 分频系数用 128 
  - In this example we need to generate a time base equal to 50 ms
  // so TIM4_PERIOD = (0.05 * 125000 - 1) = 6249 */
  
  TIM2_TimeBaseInit(TIM2_PRESCALER_128, 6249);
  /* Clear TIM4 update flag */
  TIM2_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable TIM4 */
  TIM2_Cmd(ENABLE);
  
  /* Channel 1 PWM configuration */ 
  TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,62, TIM2_OCPOLARITY_LOW ); 
  TIM2_OC1PreloadConfig(ENABLE);
  /* enable interrupts */
}

//设置周期
//测试 1、输入 20us -> period ， pluse_value ，实际观察查是否正常 结论
//测试 2、输入 60ms -> period ,  pluse_value , 实际波形情况
void tim2_prf(uint16_t prf_10us)
{
    uint32_t period;
    uint16_t pluse_value;
    float prf_ms;
    float k;
    prf_ms = prf_10us / 100;   //ms
    
    if(prf_ms > 60)
    {
      prf_ms = 60;
    }
    
    period = prf_ms*125 - 1;
    
    k = prf_10us/PLUSE_WIDTH;
    
    if(k < 1)
    {
      pluse_value = period >> 1;
    }
    else
    {
      pluse_value = period/k;
    }
    
    period = period*(1.2);      //保留余量
    
    TIM2->ARRH = (uint8_t)(period >> 8);
    TIM2->ARRL = (uint8_t)(period);
    
    TIM2->CCR1H = (uint8_t)(pluse_value >> 8);
    TIM2->CCR1L = (uint8_t)(pluse_value);
    
    
#if PRINT_ON   
    printf("tim2_prf period:%d,pluse_value:%d  \n\r",period, pluse_value);
#endif   
}
#endif


void UART1_Configuration(void)
{
  UART1_DeInit();
  UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  UART1_ITConfig(UART1_IT_TC, DISABLE);
  UART1_ITConfig(UART1_IT_TXE, DISABLE);
 
  UART1_ITConfig(UART1_IT_RXNE, ENABLE);
  UART1_Cmd(ENABLE);
}

#ifdef STM8S105
void UART2_Configuration(void)
{
  UART2_DeInit();
  UART2_Init((u32)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
  UART2_ITConfig(UART2_IT_TC, DISABLE);
  UART2_ITConfig(UART2_IT_TXE, DISABLE);
  
  UART2_ITConfig(UART2_IT_RXNE, ENABLE);
  UART2_Cmd(ENABLE);
}

#endif

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
#ifdef STM8S003
   //ITC_SetSoftwarePriority(ITC_IRQ_PORTD, ITC_PRIORITYLEVEL_2); 
#endif    
   
#ifdef STM8S105
   ITC_SetSoftwarePriority(ITC_IRQ_UART2_RX, ITC_PRIORITYLEVEL_2); 
#endif
   
   ITC_SetSoftwarePriority(ITC_IRQ_I2C, ITC_PRIORITYLEVEL_1); 
   enableInterrupts();
  
}



#if 0
void adc_config()
{

  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,\
            ADC1_CHANNEL_0| ADC1_CHANNEL_1|ADC1_CHANNEL_2|ADC1_CHANNEL_3|ADC1_CHANNEL_4|ADC1_CHANNEL_5|ADC1_CHANNEL_6|ADC1_CHANNEL_7|ADC1_CHANNEL_8,\
            ADC1_PRESSEL_FCPU_D6, ADC1_EXTTRIG_TIM, \
            DISABLE, ADC1_ALIGN_RIGHT, \
            ADC1_SCHMITTTRIG_ALL, DISABLE);
  
  ADC1_ScanModeCmd(ENABLE);
  ADC1_Cmd(ENABLE);
  ADC1_StartConversion();
}
#endif

#if 0
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
#endif

#if 0
void slave_i2c_init()
{
  
  I2C_DeInit();
  I2C_Init(100000, localAddr, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
  I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
  I2C_Cmd(ENABLE);
  enableInterrupts();
}
#endif

/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the UART1 */
  UART1_SendData8(c);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);

  return (c);
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
  char c = 0;
#else
  int c = 0;
#endif
  /* Loop until the Read data register flag is SET */
  while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
    c = UART1_ReceiveData8();
  return (c);
}


static void Tim1_Cfg()
{
  
//TIM2 cfg
    /* Time base configuration */
  TIM1_TimeBaseInit(TIM1_PRESCALER_32, SER_FREQ_50Hz);
  
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);

}



/****************** (c) 2008  STMicroelectronics ******************************/
