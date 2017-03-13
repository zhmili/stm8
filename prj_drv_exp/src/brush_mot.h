#ifndef __BRUSH_MOT_H
#define __BRUSH_MOT_H

#define MOT_FREQ_16K   999                      //主时钟16M  16M/(MOT_FREQ_16K +1) = 16K
#define MOT_CLK_LOW    0
#define MOT_CLK_HIGH   (MOT_FREQ_16K+1)         

#define MOT_NUM  6
#define FAN_NUM  4

#define MTCMD_LOC 2
#define SPEED_LOC 8
#define DLY_LOC  14
#define IOCMD_LOC 26
#define MOTRES_LOC 30


//PA
#define PO3       GPIO_PIN_1
#define POM5_2    GPIO_PIN_2
#define T2_3      GPIO_PIN_3

//PF
#define POM3_1   GPIO_PIN_4

//PB
#define POM3_2   GPIO_PIN_7      
#define POM2_2   GPIO_PIN_6  

#define PO1      GPIO_PIN_3
#define PO2      GPIO_PIN_2
#define POM1_2   GPIO_PIN_1
#define POM2_1   GPIO_PIN_0
//PE
#define POM1_1   GPIO_PIN_5

//PC
#define T1_1     GPIO_PIN_1
#define T1_2     GPIO_PIN_2
#define T1_3     GPIO_PIN_3
#define PO4      GPIO_PIN_4
#define POM4_2   GPIO_PIN_5
#define POM5_1   GPIO_PIN_6
#define POM4_1   GPIO_PIN_7

//PD
#define POM6_1     GPIO_PIN_0
#define POM6_2     GPIO_PIN_2
#define T2_2       GPIO_PIN_3
#define T2_1       GPIO_PIN_4
#define EN485      GPIO_PIN_7


///////////////////////////////
#define CMOTOR1(x)    (x?(GPIOE->ODR |= (uint8_t)POM1_1):(GPIOE->ODR &= (uint8_t)(~POM1_1)));
#define CMOTOR1_2(x)  (x?(GPIOB->ODR |= (uint8_t)POM1_2):(GPIOB->ODR &= (uint8_t)(~POM1_2)));

#define CMOTOR2(x)    (x?(GPIOB->ODR |= (uint8_t)POM2_1):(GPIOB->ODR &= (uint8_t)(~POM2_1)));
#define CMOTOR2_2(x)  (x?(GPIOB->ODR |= (uint8_t)POM2_2):(GPIOB->ODR &= (uint8_t)(~POM2_2)));

#define CMOTOR3(x)    (x?(GPIOF->ODR |= (uint8_t)POM3_1):(GPIOF->ODR &= (uint8_t)(~POM3_1)));
#define CMOTOR3_2(x)  (x?(GPIOB->ODR |= (uint8_t)POM3_2):(GPIOB->ODR &= (uint8_t)(~POM3_2)));

#define CMOTOR4(x)    (x?(GPIOC->ODR |= (uint8_t)POM4_1):(GPIOC->ODR &= (uint8_t)(~POM4_1)));
#define CMOTOR4_2(x)  (x?(GPIOC->ODR |= (uint8_t)POM4_2):(GPIOC->ODR &= (uint8_t)(~POM4_2)));

#define CMOTOR5(x)    (x?(GPIOC->ODR |= (uint8_t)POM5_1):(GPIOC->ODR &= (uint8_t)(~POM5_1)));
#define CMOTOR5_2(x)  (x?(GPIOA->ODR |= (uint8_t)POM5_2):(GPIOA->ODR &= (uint8_t)(~POM5_2)));

#define CMOTOR6(x)    (x?(GPIOD->ODR |= (uint8_t)POM6_1):(GPIOD->ODR &= (uint8_t)(~POM6_1)));
#define CMOTOR6_2(x)  (x?(GPIOD->ODR |= (uint8_t)POM6_2):(GPIOD->ODR &= (uint8_t)(~POM6_2)));

#define IO1(x)        (x?(GPIOB->ODR |= (uint8_t)PO1):(GPIOB->ODR &= (uint8_t)(~PO1)));
#define IO2(x)        (x?(GPIOB->ODR |= (uint8_t)PO2):(GPIOB->ODR &= (uint8_t)(~PO2)));
#define IO3(x)        (x?(GPIOA->ODR |= (uint8_t)PO3):(GPIOA->ODR &= (uint8_t)(~PO3)));
#define IO4(x)        (x?(GPIOC->ODR |= (uint8_t)PO4):(GPIOC->ODR &= (uint8_t)(~PO4)));



///////////////////////////////

typedef enum{
  MT_NOCMD = 0,
  MT_RUN = 1,
  MT_STOP = 2,
  MT_RUN_DLY = 3,
  MT_RESET = 4
}EMOT_CMD;

typedef enum{
  MT_NRES =0,
  MT_RES = 1
}EMT_RES;

typedef enum{
  IO_SET = 0,
  IO_RESET = 1,
}EIO_CMD;

typedef struct brush_mot{
  u16 MotId;                                    //模块名称 为rob0 自动识别的编号
  u8* pMtReset;
  u8* pMtCmd;
  s8* pSpeed;
  u16* pMtDlyMs;
  u8* pIOCmd;
}TBRUSH_MOT_CFG;





#endif