#ifndef __fenxi_s_h__
    #define __fenxi_s_h__
    
/*********分析函数***********/
int fenxi_s(struct CAR *car,struct CAR *car1,struct TM *ntm,struct TM *itm,int n);

/*******检测所有车是否都驶出桌面********/
int check_off_s(struct CAR *car,int n);

/****检测是否超速的函数****/
void check_sp(struct CAR *p,int n);


#endif