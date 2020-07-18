#ifndef __car_s_h__
    #define __car_s_h__

/************十字路口车辆控制总函数***************/
void control_car_s(struct CAR *p,struct LAMP *pl,int n);

/*************检测前方路况信息*****************/
void pre_scan(struct CAR pa[],int n,struct CAR *p);

/**************转完后检测前方路况******************/
void ex_scan(struct CAR *pa,int n,struct CAR *p);

/************警报检测******************/
void do_alarm(struct CAR *p);
    
#endif