/***********************************************************
*                   *本文件功能：丁字口车辆控制             *
*                   *作者：李鑫                            *
*                   *最终修改时间：2011.11.4                *
************************************************************/

#include <math.h>
#include <stdio.h>
#include <graphics.h>
#include "all.h"
#include "car_s.h"
#include "car_d.h"


/*****************************************************
*函数名：void do_straight_d                          *
*功能：丁字口控制车辆直行的函数                       *
*参数：*pcar车辆首地址，*p当前车地址，*pl交通灯首指针  *
*注：被control_single_car_d调用                      *
******************************************************/
void do_straight_d(struct CAR *pcar,int n,struct CAR *p,struct LAMP *pl)
{
    int i=0;                   
    struct CAR *pa=pcar;                           //接收首指针 
    int stopx[2]={BXO1-2*RY-RR-D,BXO1+2*RY+RR+D};  //西东向停车线
    int limit_rx[4],limit_ry[4];                       
    for (i=0;i<4;i++)                              //初始化限定数组
    {
        limit_rx[i]=BXO1-(3*RY/2)+RY*i;            //南北路4条道限定
        limit_ry[i]=BYO1-(3*RX/2)+RX*i;            //东西路4条道限定
    }

    switch(p->justment)
    {
        case 11:                                  //east     
                if((pl+1)->sc==LIGHTGREEN)        //绿灯情况下
                {
                    pre_scan(pa,n,p);             //扫描前方路况信息
		    do_alarm(p);                  //警报检测
                    p->y=limit_ry[0];             //东直道位置限定
                    p->x -= (p->speed);           //步进，以即时速度为步进长度
                }
                else                              //红黄灯的情况下
                {
                    if((p->x > stopx[1])&&(p->x < (stopx[1]+W)))   //在停车线的邻域内
                    {
                        p->speed=0;
                        p->y=limit_ry[0];          //东直道位置限定
                        p->x -= (p->speed);        //步进完成直线行驶，以即时速率大小为步进单位长度
                    }
                    else                           //过了停车线
                    {
                        pre_scan(pa,n,p);
                        do_alarm(p);
                        p->y=limit_ry[0];
                        p->x -= (p->speed);
                    }
                }
                break;
        
        case 31:
                if(pl->sc==LIGHTGREEN) 
                {
                    pre_scan(pa,n,p);
                    do_alarm(p);
                    p->y=limit_ry[2];
                    p->x += (p->speed);
                }
                else                   
                {
                    if((p->x < stopx[0])&&(p->x > (stopx[0]-W)))
                    {
                        p->speed=0;
                        p->y=limit_ry[2];
                        p->x += (p->speed);	 
                    }
                    else                      
                    {
                        pre_scan(pa,n,p);
                        do_alarm(p);
                        p->y=limit_ry[2];
                        p->x += (p->speed);
                    }
                }
                break;
    }   
}


/*****************************************************
*******函数名：void do_turn_d                        *
*******功能：丁字口控制车辆转弯的函数                 *
*******参数：*p当前车地址                            *
*******重要数据：stdx、stdy公转圆心，r1、r2半径       *
*******注：被do_left_d，do_right_d调用               *
******************************************************/
void do_turn_d(struct CAR *p)
{
    int i=p->count,sp=p->speed,r1=RR+RY/2+D,r2=RR+5*RY/2+D;  //大小公转半径
    int stdx[2]={BXO1-2*RY-RR-D,BXO1+2*RY+RR+D};             //圆心坐标的大小x
    int stdy=BYO1+2*RX+RR+D;                                 //圆心坐标的大小y
    double t=P/180;                                          //角度转弧度

    if((i*t*sp)<P/2)     //count为转过一个弯所需的步数，由1开始累加，sp为一步走的像素数
    { 
       p->count++;          
       i=p->count;
       switch(p->justment)
       {
        case 12:                              //东左路
 	        p->x=stdx[1]-r2*sin(i*t*sp);  //x始终小于stdx
	        p->y=stdy-r2*cos(i*t*sp);     //y始终小于stdy
                p->angle +=sp*t;              //逆时针角度增加
	        break;

        case 20:                              //南右路
 	        p->x=stdx[1]-r1*cos(i*t*sp);
	        p->y=stdy-r1*sin(i*t*sp);
                p->angle -=sp*t;
	        break;

        case 22:                              //南左路
 	        p->x=stdx[0]+r2*cos(i*t*sp);
	        p->y=stdy-r2*sin(i*t*sp);
                p->angle +=sp*t;
	        break;

        case 30:                              //西右路
 	        p->x=stdx[0]+r1*sin(i*t*sp);
	        p->y=stdy-r1*cos(i*t*sp);
                p->angle -=sp*t;
	        break;
       }
    }
}


/*********************************************************
*******函数名：void do_left_d                             *
*******功能：丁字口控制车辆左转的函数                      *
*******参数：*pcar车辆首地址，*p当前车地址，*pl交通灯首指针* 
*******注：被control_single_car_d调用                     *
***********************************************************/
void do_left_d(struct CAR *pcar,int n,struct CAR *p,struct LAMP *pl)
{                         
    struct CAR *pa=pcar;
    int i=0;
    int stopx[2]={BXO1-2*RY-RR-D,BXO1+2*RY+RR+D}; //停车线
    int stopy=BYO1+2*RX+RR+D;                     //停车线
    int limit_rx[4],limit_ry[4];
    for (i=0;i<4;i++)                             //初始化限定数组
    {
       limit_rx[i]=BXO1-(3*RY/2)+RY*i;
       limit_ry[i]=BYO1-(3*RX/2)+RX*i;
    }

    switch(p->justment)
    {
        case 12:
                if((pl+1)->lc==LIGHTGREEN)    //左转灯是绿灯 
                {    
                    if(p->x > stopx[1])       //在停车线内
                    {
                        pre_scan(pa,n,p); 
                        do_alarm(p);
                        p->y=limit_ry[1];
                        p->x -= (p->speed);
                    }
                    else if((p->x <=stopx[1])&&(p->y<stopy))  //在转弯中    
                    {
                        p->speed=1*RATE;
                        do_turn_d(p);
                    }
                    else if(p->y>=stopy)
                    {
                        ex_scan(pa,n,p);      //转弯后扫描前方路况信息
                        do_alarm(p);
                        p->x=limit_rx[1];
                        p->y += (p->speed);
                        p->angle=P;
                    }
                }
                else                            //为红黄灯
                {
                    if((p->x >= stopx[1])&&(p->x < (stopx[1]+W))) //在停车线的邻域内
                    {
                        p->speed=0;
                        p->y=limit_ry[1];
                        p->x -= (p->speed);
                    }
                    else if(p->x >=( stopx[1]+W))                 //未过停车线
                    {
                        pre_scan(pa,n,p); 
                        do_alarm(p);
                        p->y=limit_ry[1];
                        p->x -= (p->speed);
                    }
                    else if((p->x < stopx[1])&&(p->y < stopy))   //过了停车线
                    {
                        p->speed=1*RATE;
                        do_turn_d(p);
                    }
                    else if(p->y >= stopy)//转弯后
                    {
                        ex_scan(pa,n,p);//转弯后扫描前方路况信息
                        do_alarm(p);
                        p->x=limit_rx[1];
                        p->y += (p->speed);
                        p->angle=-P;
                    }
                }   
                break;

        case 22:
                if((pl+2)->lc==LIGHTGREEN)//左转灯是绿灯，可以通行
                {    
                    if(p->y > stopy)
                    {
                        pre_scan(pa,n,p);//扫描前方路况信息
                        do_alarm(p);
                        p->x=limit_rx[2];
                        p->y -= (p->speed);
                    }
                    else if((p->y <=stopy)&&(p->x>stopx[0]))      
                    {
                        p->speed=1*RATE;
                        do_turn_d(p);
                    }
                    else if(p->x<=stopx[0])
                    {
                        ex_scan(pa,n,p);//转弯后扫描前方路况信息
                        do_alarm(p);
                        p->y=limit_ry[1];
                        p->x -= (p->speed);
                        p->angle=P/2;
                    }
                }   
                else 
                {
                    if(p->y >= stopy&&(p->y<stopy+W))//在停车线的邻域内
                    {
                        p->speed=0;
                        p->x=limit_rx[2];
                        p->y -= (p->speed);                
                    }
                    else if(p->y >= stopy+W)      //未过停车线
                    {
                        pre_scan(pa,n,p);       //扫描前方路况信息
                        do_alarm(p);
                        p->x=limit_rx[2];
                        p->y -= (p->speed);
                    }
                    else if((p->y < stopy)&&(p->x > stopx[0]))//过了停车线
                    {
                        p->speed=1*RATE;
                        do_turn_d(p);
                    }
                    else if(p->x <= stopx[0])          //转过弯
                    {
                        ex_scan(pa,n,p);//转弯后扫描前方路况信息
                        do_alarm(p);
                        p->y=limit_ry[1];
                        p->x -= (p->speed);
                        p->angle=P/2;
                    }
                }
                break;
    }
}


/*********************************************************
*******函数名：void do_right_d                             *
*******功能：丁字口控制车辆右转的函数                      *
*******参数：*pcar车辆首地址，*p当前车地址，*pl交通灯首指针*                            
*******注：被control_single_car_d调用                     *
***********************************************************/
void do_right_d(struct CAR *pcar,int n,struct CAR *p,struct LAMP *pl)
{
    struct CAR *pa=pcar;
    int i=0;
    int stopx[2]={BXO1-2*RY-RR-D,BXO1+2*RY+RR+D};
    int stopy=BYO1+2*RX+RR+D;              //用于停车判断交通灯的停车线
    int limit_rx[4],limit_ry[4];
    for (i=0;i<4;i++)                      //初始化限定数组
    {
        limit_rx[i]=BXO1-(3*RY/2)+RY*i;
        limit_ry[i]=BYO1-(3*RX/2)+RX*i;
    }

    switch(p->justment)
    {                              
        case 20:
                if((pl+2)->rc==LIGHTGREEN)       
                {
                    if(p->y > stopy)
                    {
                        pre_scan(pa,n,p); 
                        do_alarm(p); 
                        p->x=limit_rx[3];
                        p->y -= (p->speed);
                    }
                    else if((p->y <=stopy)&&(p->x <stopx[1]))      
                    {
                        p->speed=1*RATE;
                        do_turn_d(p);
                    }
                    else if(p->x>=stopx[1])
                    {
                        ex_scan(pa,n,p); 
                        do_alarm(p);  
                        p->y=limit_ry[3];
                        p->x += (p->speed);
                        p->angle=3*P/2;
                    }
                }
                break;

        case 30:
                if(pl->rc==LIGHTGREEN) 
                {
                    if(p->x < stopx[0])
                    {
                        pre_scan(pa,n,p); 
                        do_alarm(p);
                        p->y=limit_ry[3];
                        p->x += (p->speed);
                    }
                    else if((p->x >=stopx[0])&&(p->y<stopy))      
                    {
                        p->speed=1*RATE;
                        do_turn_d(p);
                    }
                    else if(p->y>=stopy)
                    {
                        ex_scan(pa,n,p);       
                        do_alarm(p);
                        p->x=limit_rx[0];
                        p->y += (p->speed);
                        p->angle=P;
                    }
                }
                break;
    }
}


/*******************************************************************
*******函数名：void control_single_car_d                            *
*******功能：丁字口控制单辆车运行的函数                              *
*******参数：*pp车辆首地址，n为车辆总数，*p当前车地址，*pl交通灯首指针*                            
*******注：被control_car_d调用                                      *
*********************************************************************/
void control_single_car_d(struct CAR *pp,int n,struct CAR *p,struct LAMP *pl)
{                       
    if((p->justment==11)||(p->justment==31))       //1为直行车道
        do_straight_d(pp,n,p,pl);            
    else if((p->justment==20)||(p->justment==30))  //0为右转车道
        do_right_d(pp,n,p,pl);     
    else  if((p->justment==12)||(p->justment==22))  //2为左转车道
        do_left_d(pp,n,p,pl);      
}


/*******************************************************************
*******函数名：void control_car_d                                   *
*******功能：丁字口控制全部车运行的函数                              *
*******参数：*p车辆首地址，n为车辆总数，*pl交通灯首指针              *                            
*******注：被fz函数调用                                             *
*********************************************************************/
void control_car_d(struct CAR *p,struct LAMP *pl,int n)
{
    int i;
    struct CAR *pc=NULL;
    pc=p;                    //保存首地址
    for(i=0;i<n;i++)
    {
        control_single_car_d(pc,n,p,pl);
        p++;
    }
}



