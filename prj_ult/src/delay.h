
#ifndef __DELAY_H
#define __DELAY_H
//֧�ֲ�ͬʱ��Ƶ��
//�ṩdelay_us,delay_ms������ʱ����. 
////////////////////////////////////////////////////////////////////////////////
void delay_init(u8 clk); //��ʱ������ʼ��
void delay_us(u16 nus);  //us����ʱ����,���65536us.
void delay_ms(u32 nms);  //ms����ʱ����

#endif