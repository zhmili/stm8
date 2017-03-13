#ifndef __NODE_H
#define __NODE_H

#define BROAD_ADDR    0
#define DEFAULT_ADDR  255

typedef enum
{
 NO = 0,
 WHILE = 1,
 WHILE_END = 2,
 FOR = 3,
 FOR_END = 4,
 IF = 5,
 IF_END = 6,
 VOID_FUN = 7,                                                                  //无返回值的函数
 RETURN_FUN = 8,                                                                //有返回值的函数
 VOID_SEQ_FUN = 9,                                                              //有返回值自定义函数序列
 RETURN_SEQ_FUN = 10                                                            //无返回值的自定义函数序列
 
}ENODE_TYPE;

typedef enum
{
  COMM_RUN = 0,
  SET_ADDR,
  RUN_DISP_ON,
  RUN_DISP_OFF,
  SPEAK_ON,
  SPEAK_OFF,
  ALARM_ON,
  ALARM_OFF
}ESYS_CTR;

typedef struct {                                                                //0 地址 开始
   unsigned short type;                                                         //1 ENODE_TYPE
   unsigned short fun_loc;                                                      //2决定是哪号函数
   unsigned short parm_num;                                                     //3实际参数个数 
   unsigned short parms[3];                                                     //4 5 6 最多参数3个
   unsigned short parms_kind[3];                                                //      三种输入参数各是什么类型
   unsigned short parms_mlev[3];                                                //      三种开关的数值量级，乘以几表示
   unsigned short fun_return;                                                   //7 函数返回值，如果函数是有返回值的，直接将返回值放入此处 做为判断
   unsigned short addr;                                                         //8 设置的模块地址
   unsigned short next_exist;                                                   //9 下一个模块是否存在            
}TNodePar;

typedef struct {
   unsigned short ctr;
}TNodeCtr;


typedef struct {
  TNodePar node_par;
  TNodeCtr node_ctr;
}TSYS;

#endif