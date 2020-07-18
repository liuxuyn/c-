/****************************************************
*             *本文件为丁字口车辆及路灯初始化文件    *
*             *作者：李鑫                           *
*             *最终修改时间：2011.11.4              *
*****************************************************/

#include <graphics.h>
#include <stdlib.h>
#include "all.h"
#include "init_d.h"

/***************************************************
*函数名：void car_init_xy0_d                       *
*功能：丁字口设置车的位置                           *
*参数：p为当前车结构首地址，                        *
*      rx、ry、bx、by为车位置限制数组首地址         *
*      state为清零标志位                           *
****************************************************/
void car_init_xy0_d(struct CAR *p,int *limit_rx,int *limit_ry,int *limit_bx,int *limit_by,int state)
{
    static int count[6]={0,0,0,0,0,0};        //12个道口车的数量数组
    int i=0;
    switch(p->justment)
    {
        //50A为第一辆车距停车线的距离   30A为两辆车之间的前后车距
        case 11:
                p->y=limit_ry[0];        //在东道最右边向北转弯的直道上
                //A为车辆尺寸比率，车辆绝对长度为25，定位以车辆中心为标准
                p->x=limit_bx[2]+50*A+30*A*count[0];      
                count[0]++;              //依次往后叠放
                break;

        case 12:
                p->y=limit_ry[1];
                p->x=limit_bx[2]+50*A+30*A*count[1];
				count[1]++;
                break;

        case 20: 
                p->x=limit_rx[3];
                p->y=limit_by[2]+50*A+30*A*count[2];
                count[2]++;
                break;

        case 22: 
                p->x=limit_rx[2];
                p->y=limit_by[2]+50*A+30*A*count[3];
                count[3]++;
                break;

        case 30:
                p->y=limit_ry[3];
                p->x=limit_bx[1]-50*A-30*A*count[4];
                count[4]++;
                break;

        case 31: 
                p->y=limit_ry[2];
                p->x=limit_bx[1]-50*A-30*A*count[5];
                count[5]++;
                break;
    }
    if(state<0)
   	for(i=0;i<6;i++)
   	    count[i]=0;
}


/***************************************************
*函数名：void car_init_xy_d                        *
*功能：丁字口对车辆所在的车道位置进行初始化的函数    *
*参数：p为当前车结构首地址，                        *
*     state为清零标志位                            *
****************************************************/
int car_init_xy_d(struct CAR *p,int state)
{
    int limit_rx[4],limit_ry[4];  //用于限定车位左右偏移
    //用于运行距离的限定和随机定位的限定
    int limit_bx[4]={BXO1-BX/2,BXO1-2*RY-RR,BXO1+2*RY+RR,BXO1+BX/2};
    int limit_by[4]={BYO1-BY/2,BYO1-2*RX-RR,BYO1+2*RX+RR,BYO1+BY/2};            
    int i=0;
    for(i=0;i<4;i++)
    {
        limit_rx[i]=BXO1-(3*RY/2)+RY*i;  //y路 也就是南北路车在x方向上的位置限制
        limit_ry[i]=BYO1-(3*RX/2)+RX*i;  //x路 也就是东西路车在y方向上的位置限制
    }
    car_init_xy0_d(p,limit_rx,limit_ry,limit_bx,limit_by,state);
    return 1;
}


/***************************************************
*函数名：int car_init_judge_d                      *
*功能：丁字口判断出过程控制的参数justment           *
*参数：p为当前车结构首地址，                        *
****************************************************/
int car_init_judge_d(struct CAR *p)
{
    //justment由两位数组成，
    //首位代表当前所处的路径，1234代表东南西北道路
    //末尾代表将要进行的转向，012分别表示向右中左转的车道

    switch(p->dirt1)
    {
        case 1:        //车头朝向正西方，即在东一路上 
               if(p->dirt2==2) p->justment=12;
               if(p->dirt2==3) p->justment=11;
               break;

        case 2:        //车头朝向正北方，即在南二路上
               if(p->dirt2==1) p->justment=20;
               if(p->dirt2==3) p->justment=22;
               break;

        case 3:        //车头朝向正东方，即在西三路上
               if(p->dirt2==1) p->justment=31;
               if(p->dirt2==2) p->justment=30;
               break;
    }
    return 1;
}

/***************************************************
*函数名：int car_init_dir_random_d                 *
*功能：丁字口随机生成车辆转向的函数                 *
*参数：p为当前车结构首地址，                        *
****************************************************/
int car_init_dir_random_d(struct CAR *p)
{
    int a,b;
    a=random(1001);
    b=(a%3)+1;
    p->dirt2=b;
    while((p->dirt1)==(p->dirt2))  //避免dir1和dir2重合
    {
        a=random(1001);
        b=(a%3)+1;
        p->dirt2=b;
    }
    return 1;
}


/***************************************************
*函数名：int single_car_init_d                     *
*功能：丁字口初始化车速已定的单个车辆的函数         *
*参数：p为当前车结构首地址，                        *
****************************************************/
int single_car_init_d(struct CAR *p)
{
    p->justment=0;             //初始化车位  用于debug时看是否赋值
    p->alarm=0;                //车前警报设置为空
    p->count=0;                //已经转过的角度            

    car_init_dir_random_d(p);  //由该函数初始化基础参数要转向的路dir2
    car_init_judge_d(p);       //由该函数根据dir1,dir2判断得到所在路口及车道，记录在justment中
    car_init_xy_d(p,1);        //根据以上两个函数得到的参数，进行判断，得到车子的初始位置
    return 1;                  //成功执行

}

/***************************************************
*函数名：int init_car_choice_d                     *
*功能：丁字口初始化车角度颜色路函数                *
*参数：p为车结构数组首地址，a为车数量数组首地址      *
****************************************************/
int init_car_choice_d(struct CAR p[],int a[])
{
    int i=0;
    //东路车初始化
    for(i=0;i<a[0];i++)
    {
        p[i].color=LIGHTGREEN;               //东路车是亮绿色
        p[i].dirt1=1;                        //1234分别表示东南西北
        p[i].angle=P/2;                      //车头方向
        single_car_init_d(&p[i]);              //初始化其他参数
    }

    //南路车初始化
    for(i=a[0];i<(a[0]+a[1]);i++)
    {
        p[i].color=LIGHTRED;                //南路车是亮红色
        p[i].dirt1=2;
        p[i].angle=0;
        single_car_init_d(&p[i]);
    }

    //西路车初始化
    for(i=a[0]+a[1];i<(a[0]+a[1]+a[2]);i++)
    {
        p[i].color=BLACK;                   //西路车是黑色
        p[i].dirt1=3;
        p[i].angle=3*P/2;
        single_car_init_d(&p[i]);
    }
    return 1;
}


/***************************************************
*函数名：void init_car_d                           *
*功能：丁字口初始化车总函数                         *
*参数：p为车结构数组首地址，pnum为车数量数组首地址   *
*      n为车数量总数                               *
****************************************************/
void init_car_d(int pnum[],int n,struct CAR p[])
{
    int i,a[3];                  //a[]为保存各路口车数的数组
    int spn=0;
    randomize();
    for(i=0;i<n;i++)             //所有车辆车速初始化
    {
        p[i].speed=(random(1001)%3+1)*RATE;
        if(p[i].speed>=3*RATE)
        {
            spn++;
            if(spn>CAR_SPMAX)
            {
                p[i].speed=2*RATE;
                spn=CAR_SPMAX;
            }
        }
        p[i].std_speed=p[i].speed;
        p[i].flag=0;               //flag==1时表示驶离桌面
        p[i].spflag=0;
        p[i].cnum=i;
    }

    for(i=0;i<3;i++)              //保存四个路口车数量，防止原数据被修改
    {
        a[i]=pnum[i];
    }
    init_car_choice_d(p,a);         //除了车辆速度以外的其他数据初始化
}


/***************************************************
*函数名：void init_lamp_d                          *
*功能：丁字口初始化交通灯总函数                     *
*参数：lamp为交通灯结构数组首地址                   *
****************************************************/
void init_lamp_d(struct LAMP lamp[])
{
    int i,j;
	
    //用于限定交通灯所在位置的数组 东西北
    int lamp_x[3]={BXO1+2*RY+RR+H,BXO1-2*RY-RR-H,BXO1+2*RY};
    int lamp_y[3]={BYO1+2*RX,BYO1-2*RX,BYO1-2*RX-H};

    lamp[0].flag=1;            //给每个交通灯定下标志号
    lamp[1].flag=3;
    lamp[2].flag=4;
	
    for(i=0;i<3;i++)
    {
        lamp[i].rc = LIGHTGREEN;      //右转灯都赋为绿灯
        lamp[i].sc = lamp[i].lc=RED;  //直行灯和左转灯都赋为红灯
        lamp[i].x = lamp_x[i];
        lamp[i].y = lamp_y[i];
    }
}

/***************************************************
*函数名：void car_zero_d                           *
*功能：丁字口交通灯清零函数                         *
*参数：p为当前车结构地址                            *
****************************************************/
void car_zero_d(struct CAR *p)
{
    car_init_xy_d(p,-1);
}