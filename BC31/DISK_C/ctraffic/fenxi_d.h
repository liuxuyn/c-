#ifndef __fenxi_d_h__
    #define __fenxi_d_h__
    
/*********分析函数***********/
int fenxi_d(struct CAR *car,struct CAR *car1,struct TM *ntm,struct TM *itm,int n);

/*******检测所有车是否都驶出桌面********/
int check_off_d(struct CAR *car,int n);

#endif