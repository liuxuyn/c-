/***********************************************************
*          *本文件为十字仿真总控制文件                      *
*          *作者：李鑫                                     *
*          *最终修改时间：2011.11.5                        *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <bios.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include "all.h"
#include "drawtool.h"
#include "readbmp.h"
#include "init_s.h"
#include "fz_s.h"
#include "fenxi_s.h"
#include "car_s.h"
#include "lamp_s.h"

/****************************************************
*函数名：void time_zero_s                           *
*功能：计时归零                                     * 
*参数：count计数，tm为时间结构指针                   *
*****************************************************/
void time_zero_s(int *count,struct TM *tm)
{
	*count=0;
	tm->minute=0;
	tm->second=0;
}

/****************************************************
*函数名：void drawpage1_s                           *
*功能：十字口仿真画第一页                            * 
*参数： p为车辆结构数组首地址，pl为交通灯结构首地址   *
*    n为车辆总数，ntm，itm为时间结构指针，count技术，*
*      tg绿灯时间                                   *
*****************************************************/
void drawpage1_s(struct CAR *p,struct LAMP *pl,int n,struct TM *ntm,int *count,int *tg)
{
    int i=0;
    setactivepage(1);
    draw_road_s();
    draw_gg_s(count,ntm,tg);
    for(i=0;i<n;i++)
        draw_car(&p[i]);
    for(i=0;i<4;i++)
        draw_lamp_s(&pl[i]);
    setvisualpage(1);
}

/****************************************************
*函数名：void drawpage0_s                           *
*功能：十字口仿真画第零页                            * 
*参数： p为车辆结构数组首地址，pl为交通灯结构首地址   *
*    n为车辆总数，ntm，itm为时间结构指针，count技术，*
*      tg绿灯时间                                   *
*****************************************************/
void drawpage0_s(struct CAR *p,struct LAMP *pl,int n,struct TM *ntm,int *count,int *tg)
{
    int i=0;
    setactivepage(0);
    draw_road_s();
    draw_gg_s(count,ntm,tg);
    for(i=0;i<n;i++)
        draw_car(&p[i]);
    for(i=0;i<4;i++)
        draw_lamp_s(&pl[i]);
    setvisualpage(0);
}

/****************************************************
*函数名：int normal_s                               *
*功能：十字口常规仿真                                * 
*参数： p为车辆结构数组首地址，pl为交通灯结构首地址   *
*    n为车辆总数，ntm，itm为时间结构指针，count技术，*
*             reflag为重播标志位                    *
*****************************************************/
int normal_s(struct CAR *p,struct LAMP *pl,int n,int *reflag,struct TM *ntm,struct TM *itm)
{
    int key=0,f=0,time=1;
    int i=0,j=0,count=0;
    struct CAR recar[CAR_MAX * 4];
    struct LAMP relamp[4];
    int tg[4]={TGREEN,TGREEN,TGREEN,TGREEN};
    *reflag=0;       //重播标志位
    ntm->minute=0;   //计时清零
    ntm->second=0;
  
    for(i=0;i<n;i++) //车辆及红绿灯数据备份
        recar[i]=p[i];
    for(j=0;j<4;j++)
        relamp[j]=pl[j];
		
    //整个动画的操作
    while(1)
    {
        delay(8);
        drawpage1_s(recar,relamp,n,ntm,&count,tg);
        control_car_s(recar,relamp,n);
        control_norlamp_s(relamp,reflag);
        while(f==0)            //仿真开始时的开始操作
        {
            if(time==1)
            {
                draw_play(BXO-3*RY-FW-10,BY-FH-20,0);
                time=0;
            }
            if(kbhit())
            {
                key=bioskey(0);
                if(key==START)
                    f=1;
                if(key==ESC)
                {
                    readbmp("wenjian\\byebye.bmp");
                    exit(0);
                }
                if(key==BACK)
                {
                    *reflag=1;
                    time_zero_s(&count,ntm);
                    control_norlamp_s(relamp,reflag);
                    return EXIT;
                }
            }
        }
        delay(8);
        drawpage0_s(recar,relamp,n,ntm,&count,tg);
        control_car_s(recar,relamp,n);
        control_norlamp_s(relamp,reflag);

        if(kbhit())
        {
            key=bioskey(0);
            switch(key)
            {
                case ESC:
                         readbmp("wenjian\\byebye.bmp");
                         exit(0);
                         break;

                case BACK:
                          *reflag=1;
                          time_zero_s(&count,ntm);
                          control_norlamp_s(relamp,reflag);
                          return EXIT;

                case PAUSE:
                           draw_play(BXO-3*RY-FW-10,BY-FH-20,0);
                           while(1)
                           {
                               if(kbhit())
                               {
                                   key=bioskey(0);
                                   if(key==ESC)
                                   {
                                       readbmp("wenjian\\byebye.bmp");
                                       exit(0);
                                       break;
                                   }
                                   if(key==START)					                                       break;
                                   if(key==REPLAY)
                                   {
                                       *reflag=1;
                                       time_zero_s(&count,ntm);
                                       draw_replay(BXO+3*RY+10,BY-FH-20,1);
                                       control_norlamp_s(relamp,reflag);
                                       return 1;
                                   }
                                   if(key==BACK)
                                   {
                                       *reflag=1;
                                       time_zero_s(&count,ntm);
                                       control_norlamp_d(relamp,reflag);
                                       return EXIT;
                                   }
                               }
                           }
                           break;

                case REPLAY:
                            *reflag=1;
                            time_zero_s(&count,ntm);
                            draw_replay(BXO+3*RY+10,BY-FH-20,1);
                            control_norlamp_s(relamp,reflag);
                            return 1;
            }
        }
        if(check_off_s(recar,n))
        {
     	     draw_fenxi();
     	     while(1)
     	     {
                 if(kbhit())
                 {
                     key=bioskey(0);
                     if(key==ENTER)
                     {
                         closegraph();
                         fenxi_s(p,recar,ntm,itm,n);
                         init_EGA();
                         break;
                     }
                     if(key==REPLAY)
                     {
                         *reflag=1;
                         time_zero_s(&count,ntm);
                         draw_replay(BXO+3*RY+10,BY-FH-20,1);
                         control_norlamp_s(relamp,reflag);
                         return 1;
                     } 
                     if(key==ESC)
                     {
                         readbmp("wenjian\\byebye.bmp");
                         exit(0);
                     } 
                     if(key==BACK)
                     {
                         *reflag=1;
                         control_norlamp_s(relamp,reflag);
                         return EXIT;
                     }				
                 }
             }
        }
        check_sp(recar,n);
    }
}

/****************************************************
*函数名：int intell_s                              *
*功能：十字口智能仿真                                * 
*参数： p为车辆结构数组首地址，pl为交通灯结构首地址   *
*    n为车辆总数，ntm，itm为时间结构指针，count技术，*
*             reflag为重播标志位               *
*****************************************************/
int intell_s(struct CAR *p,struct LAMP *pl,int n,int *reflag,struct TM *ntm,struct TM *itm)
{
    int key=0,f=0,time=1;
    int i=0,j=0,count=0;
    struct CAR recar[CAR_MAX * 4];
    struct LAMP relamp[4];
    int tg[4]={0,0,0,0};  // 智能仿真扫描时存储绿灯时间
    *reflag=0;       //重播标志位
    itm->minute=0;   //计时清零
    itm->second=0;

    for(i=0;i<n;i++) //车辆及红绿灯数据备份
        recar[i]=p[i];
    for(j=0;j<4;j++) 
        relamp[j]=pl[j];

    //整个动画的操作
    while(1)
    {
        delay(8);
        drawpage1_s(recar,relamp,n,itm,&count,tg);
        control_car_s(recar,relamp,n);
        control_intlamp_s(recar,n,relamp,tg,reflag);
        while(f==0)            //仿真开始时的开始操作
        {
            if(time==1)
            {
                draw_play(BXO-3*RY-FW-10,BY-FH-20,0);
                time=0;
            }
            if(kbhit())
            {
                key=bioskey(0);
                if(key==START)
                    f=1;
                if(key==ESC)
                {
                    readbmp("wenjian\\byebye.bmp");
                    exit(0);
                }
                if(key==BACK)
                {
                    *reflag=1;
                    time_zero_s(&count,itm);
                    control_intlamp_s(recar,n,relamp,tg,reflag);
                    return EXIT;
                }
            }
        }
        delay(8);
        drawpage0_s(recar,relamp,n,itm,&count,tg);
        control_car_s(recar,relamp,n);
        control_intlamp_s(recar,n,relamp,tg,reflag);

        if(kbhit())
        {
            key=bioskey(0);
            switch(key)
            {
                case ESC:
                         readbmp("wenjian\\byebye.bmp");
                         exit(0);
                         break;

                case BACK:
                          *reflag=1;
                          time_zero_s(&count,itm);
                          control_intlamp_s(recar,n,relamp,tg,reflag);
                          return EXIT;

                case PAUSE:
                           draw_play(BXO-3*RY-FW-10,BY-FH-20,0);
                           while(1)
                           {
                               if(kbhit())
                               {
                                   key=bioskey(0);
                                   if(key==ESC)
                                   {
                                       readbmp("wenjian\\byebye.bmp");
                                       exit(0);
                                       break;
                                   }
                                   if(key==START)					                                       break;
                                   if(key==REPLAY)
                                   {
                                       *reflag=1;
                                       time_zero_s(&count,itm);
                                       draw_replay(BXO+3*RY+10,BY-FH-20,1);
                                       control_intlamp_s(recar,n,relamp,tg,reflag);
                                       return 1;
                                   }
                                   if(key==BACK)
                                   {
                                       *reflag=1;
                                       time_zero_s(&count,itm);
                                       control_intlamp_s(recar,n,relamp,tg,reflag);
                                       return EXIT;
                                   }
                               }
                           }
                           break;
                   
                case REPLAY:
                            *reflag=1;
                            time_zero_s(&count,itm);
                            draw_replay(BXO+3*RY+10,BY-FH-20,1);
                            control_intlamp_s(recar,n,relamp,tg,reflag);
                            return 1;
            }
        }
        if(check_off_s(recar,n))
        {
     	     draw_fenxi();
     	     while(1)
     	     {
                 if(kbhit())
                 {
                     key=bioskey(0);
                     if(key==ENTER)
                     {
                         closegraph();
                         fenxi_s(p,recar,ntm,itm,n);
                         init_EGA();
                         break;
                     }
                     if(key==REPLAY)
                     {
                         *reflag=1;
                         time_zero_s(&count,itm);
                         draw_replay(BXO+3*RY+10,BY-FH-20,1);
                         control_intlamp_s(recar,n,relamp,tg,reflag);
                         return 1;
                     } 
                     if(key==ESC)
                     {
                         readbmp("wenjian\\byebye.bmp");
                         exit(0);
                     } 
                     if(key==BACK)
                     {
                         *reflag=1;
                         control_intlamp_s(recar,n,relamp,tg,reflag);
                         return EXIT;
                     }	 					
                 }
             }
        }
        check_sp(recar,n);
    }
}

/****************************************************
*函数名：int start_s                                 *
*功能：十字口仿真                                     * 
*参数： p为车辆结构数组首地址，pl为交通灯结构首地址    *
*     ntm，itm为时间结构指针 ，pnum为车辆数目数组首地址*
*     lampflag为仿真模式标志位                       *
*****************************************************/
int start_s(int *pnum,struct CAR *p,struct LAMP *pl,int lampflag,struct TM *ntm,struct TM *itm)
{

    int nreflag=0,ireflag=0;           //是否重播标志位
    int state=0;                       //int flag=EXITSTATE;
    int n=pnum[0]+pnum[1]+pnum[2]+pnum[3];
    init_lamp_s(pl);//交通灯初始化

    while(1)
    {
        if(lampflag==1&&ireflag==0)
        {
            state=intell_s(p,pl,n,&ireflag,ntm,itm);//智能仿真运行
            if(state==EXIT)
            {
            	state=0;
            	return EXIT;
            }
        }

        if(lampflag==0&&nreflag==0)
        {
            state=normal_s(p,pl,n,&nreflag,ntm,itm);//常规仿真运行
            if(state==EXIT)
            {
            	state=0;
            	return EXIT;
            }
        }
       
        //重播时执行的函数
        if(nreflag==1)        //常规仿真重播
        {
            state=normal_s(p,pl,n,&nreflag,ntm,itm);
            if(state==EXIT)
            {
                 state=0;
                 return EXIT;
            }
        }
        if(ireflag==1)   // 智能仿真重播
        {
            state=intell_s(p,pl,n,&ireflag,ntm,itm);
            if(state==EXIT)
            {
                state=0;
                return EXIT;
            }
        }       
    }
}

/*********************************************************
*函数名：int fz_s                                         *
*功能：十字口仿真总函数                                    * 
*参数：car_num为车辆数目数组首地址，car为车辆结构数组首地址 *
*     ntm，itm为时间结构指针 ，pnum为车辆数目数组首地址    *
*     lampflag为仿真模式标志位                            *
**********************************************************/
int fz_s(int *car_num,int lampflag,struct CAR *car,struct TM *ntm,struct TM *itm)
{
    int state=0;
    struct LAMP lamp[4];
    init_EGA();
    state=start_s(car_num,car,lamp,lampflag,ntm,itm);
    if(state==EXIT)
    { 
    	state=0;	
    	closegraph();
    	return EXIT;
    }
    else return 0;
}