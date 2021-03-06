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
TSYS SYS;

void main(void)
{
  int b;
  /* Configures clocks */
  CLK_Configuration();

  /* Configures GPIOs */
  GPIO_Configuration();
  
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,\
            ADC1_CHANNEL_0| ADC1_CHANNEL_1|ADC1_CHANNEL_2|ADC1_CHANNEL_3|ADC1_CHANNEL_4|ADC1_CHANNEL_5|ADC1_CHANNEL_6|ADC1_CHANNEL_7|ADC1_CHANNEL_8,\
            ADC1_PRESSEL_FCPU_D6, ADC1_EXTTRIG_TIM, \
            DISABLE, ADC1_ALIGN_RIGHT, \
            ADC1_SCHMITTTRIG_ALL, DISABLE);
  
  ADC1_ScanModeCmd(ENABLE);
  ADC1_Cmd(ENABLE);
  ADC1_StartConversion();
  
  TIM4_Configuration();
  
  UART2_Configuration();
  
  ITC_Configuration();
  
  modbusInit();
  
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
   // GetAnalogData(&analog);
    
    switch(SYS.node_ctr.ctr)
    {
      case COMM_RUN:
        comm_run();
        break;
        
      case SET_ADDR:
        
        SYS.node_ctr.ctr = COMM_RUN;
        break;
      
     case RUN_DISP_ON:
       
        break;
     
     case RUN_DISP_OFF:
        break;
        
     case SPEAK_ON:
        break;
    
     case SPEAK_OFF:
        break;
        
     case  ALARM_ON:
      break;
      
     case ALARM_OFF:
      break;
    
     case default:
      break;
   }
    
    
   /* User code */
   //ExtraCode_StateMachine();
   /* Main function of the Touch Sensing library */
   //TSL_Action();
    
  }
}

