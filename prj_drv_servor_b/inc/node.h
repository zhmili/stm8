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
 VOID_FUN = 7,                                                                  //�޷���ֵ�ĺ���
 RETURN_FUN = 8,                                                                //�з���ֵ�ĺ���
 VOID_SEQ_FUN = 9,                                                              //�з���ֵ�Զ��庯������
 RETURN_SEQ_FUN = 10                                                            //�޷���ֵ���Զ��庯������
 
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

typedef struct {                                                                //0 ��ַ ��ʼ
   unsigned short type;                                                         //1 ENODE_TYPE
   unsigned short fun_loc;                                                      //2�������ĺź���
   unsigned short parm_num;                                                     //3ʵ�ʲ������� 
   unsigned short parms[3];                                                     //4 5 6 ������3��
   unsigned short parms_kind[3];                                                //      ���������������ʲô����
   unsigned short parms_mlev[3];                                                //      ���ֿ��ص���ֵ���������Լ���ʾ
   unsigned short fun_return;                                                   //7 ��������ֵ������������з���ֵ�ģ�ֱ�ӽ�����ֵ����˴� ��Ϊ�ж�
   unsigned short addr;                                                         //8 ���õ�ģ���ַ
   unsigned short next_exist;                                                   //9 ��һ��ģ���Ƿ����            
}TNodePar;

typedef struct {
   unsigned short ctr;
}TNodeCtr;


typedef struct {
  TNodePar node_par;
  TNodeCtr node_ctr;
}TSYS;

#endif