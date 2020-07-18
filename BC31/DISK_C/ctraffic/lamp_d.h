#ifndef __lamp_d_h__
    #define __lamp_d_h__

/*常规仿真模式的交通灯控制函数(被intell函数调用)*/
void control_norlamp_d(struct LAMP *pl,int *flag);

/*智能仿真模式的交通灯控制函数(被intell函数调用)*/
void control_intlamp_d(struct CAR *p,int n,struct LAMP *pl,int g[],int *flag);

#endif