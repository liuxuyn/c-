#ifndef __init_s_h__
    #define __init_s_h__

/*************十字路口车辆初始化****************/
void init_car_s(int pnum[],int n,struct CAR p[]);

/************丁字路口交通灯初始化***************/
void init_lamp_s(struct LAMP lamp[]);

/*********十字路口车辆清零************/
void car_zero_s(struct CAR *p);

#endif