/**
  ******************************************************************************
  * @file main.c
  * @brief Adjustable LED blinking speed using STM8S-DISCOVERY touch sensing key
  * Application example.
  * @author STMicroelectronics - MCD Application Team
  * @version V2.0.0
  * @date 15-MAR-2011
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2008 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
extern Tanalog analog;
/* Public functions ----------------------------------------------------------*/

/**
  ******************************************************************************
  * @brief Main function.
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
TULT ULT;
int i;
void main(void)
{
  /* Configures clocks */
  CLK_Configuration();
  
  /* Configures GPIOs */
  GPIO_Configuration();
  
  //I2C_Init(100000, 0xA0, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16); 
  //I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
  
  ITC_Configuration();
  
#ifdef STM8S003
  UART1_Configuration();
#endif
  Init_I2C();
  
  while(1)
  {
    
    
    
  }
  
#if 0
    TIM4_Configuration();
    
    ult_init();
    
  #ifdef STM8S105
    UART2_Configuration();
  #endif
    
    tim2_cap_config();
    
    ITC_Configuration();
    
    modbusInit();
    
  #if PRINT_ON
    printf("sys start! \n\r");
  #endif
    GPIO_WriteLow(GPIOD, GPIO_PIN_2);
    
    //trig();
    ULT.once_ready = 1;
    
    /* Initialize Touch Sensing library */
    //TSL_Init();
    
    /* Initialize all the Touch Sensing keys */
    //ExtraCode_Init();
    
    /* Start the 100ms timebase Timer */
    //TSL_Tick_Flags.b.User1_Start_100ms = 1;
    
    for (;;)
    {
     //UART2_SendData8(1);
      timeProc();
      checkComm0Modbus();
      
  #if 1
      if(ULT.once_ready)
      {
        cacu_dist();
        
        if(ULT.cap_val2 - ULT.cap_val1 > 0)
        {
        delay_us((ULT.cap_val2 - ULT.cap_val1)*2);
        }
        else
        {
          delay_ms(MAX_DIS_MS);
        }
        trig();
      }
  #endif
      
  #if 0    
      if(!ULT.once_ready)             //防止发出数据接收不到
      {
        if(ULT.bt_60_ms >= MAX_DIS_MS)
        {
          ULT.dist_mm = ERR_UP_DIS_MM;
          ULT.not_rec_time++;
          ULT.once_ready = 1;
        }
      }
  #endif

    
   /* User code */
   //ExtraCode_StateMachine();
   /* Main function of the Touch Sensing library */
   //TSL_Action();
  }
 #endif
}

