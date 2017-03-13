#ifndef __SERVO_H
#define __SERVO_H
//16分频
// (1M/50)*1000000
#define SER_FREQ_50Hz   9999  //50hz 
#define LOC_LOC         2

#define SERVO_BASE      500   //上电瞬间在中心点

#define SERVO_ADDR      0x500     

#define SERVO_TIM       TIM2
#define SERVO_TIM_CH_H    CCR3H
#define SERVO_TIM_CH_L    CCR3L



typedef struct {
  u16 servo_id;
  
  u8* ploc;
}TSERVO;




void ServoInit();


#endif