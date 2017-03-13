#ifndef __ULT_H__
#define __ULT_H__


//340mm/ms 
#define CAP_TIM_BASE_US             8
#define SOUND_SPEED_MM_PER_US       340     //340mm/ms  -> 340um/us -> 2720um/8us
                                            //1360/8us 
#define SOUND_SPEED_MM_PER_8US      27.20  //42.500?!
#define SOUND_SPEED_MM_PER_8US_HALF 13.60

#define MAX_DIS_MS                  60
#define ERR_UP_DIS_MM               90000


typedef struct {
  uint16_t cap_val1;
  uint16_t cap_val2;
  uint16_t dist_mm;
  uint16_t once_ready;
  uint16_t trg_start_time;
  uint16_t bt_60_ms;
  uint16_t not_rec_time;
}TULT;




#endif