#ifndef __menu_h__
    #define __menu_h__

/*��ť�²˵���������*/    
#define CZSM_NUM 7
#define GNJS_NUM 6
#define GYTD_NUM 5

/*��ʼ��·���������*/
#define RIN_X0   140
#define RIN_Y0   100
#define RIN_LEN  400
#define RIN_WID  280
#define RIN_RWID 100

/*���ⲿ���õĺ���*/
/******�����׺���**********/
void menu(void);

/********ʮ��·�ڳ���ʼ������**************/
int Win_CarInit_s(void);

/********����·�ڳ���ʼ������**************/
int Win_CarInit_d(void);

/*********ʮ��·�������볣�����ѡ�����************/
int Win_IntOrNor_s(int car_num[],struct CAR *car);

/*********����·�������볣�����ѡ�����************/
int Win_IntOrNor_d(int car_num[],struct CAR *car);

#endif