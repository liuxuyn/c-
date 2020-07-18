#ifndef __init_d_h__
    #define __init_d_h__

/*********丁字口车辆初始化总函数***********/
void init_car_d(int pnum[],int n,struct CAR p[]);

/***********丁字口交通灯初始化**************/
void init_lamp_d(struct LAMP lamp[]);

/********丁字口车辆位置清零********/
void car_zero_d(struct CAR *p);


#endif