#ifndef __menu_h__
    #define __menu_h__

/*按钮下菜单行数定义*/    
#define CZSM_NUM 7
#define GNJS_NUM 6
#define GYTD_NUM 5

/*初始化路面相关数据*/
#define RIN_X0   140
#define RIN_Y0   100
#define RIN_LEN  400
#define RIN_WID  280
#define RIN_RWID 100

/*给外部调用的函数*/
/******界面首函数**********/
void menu(void);

/********十字路口车初始化界面**************/
int Win_CarInit_s(void);

/********丁字路口车初始化界面**************/
int Win_CarInit_d(void);

/*********十字路口智能与常规仿真选择界面************/
int Win_IntOrNor_s(int car_num[],struct CAR *car);

/*********丁字路口智能与常规仿真选择界面************/
int Win_IntOrNor_d(int car_num[],struct CAR *car);

#endif