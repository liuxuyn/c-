/***************************************************************
*                *本文件为十字路口交通灯控制                    *
*                *作者：国悦婷                                 *
*                *最终修改时间：2011.11.4                      *
****************************************************************/

#include <graphics.h>
#include "all.h"
#include "lamp_s.h"

        
/**********************************************************
*函数名：void lighten_lamp_s                              *
*功能：丁字口执行交通灯颜色切换的函数                      *
*参数：pl为交通灯结构数组首地址，k为切换的编号，            *
*      color为切换的颜色                                   *
************************************************************/
void lighten_lamp_s(struct LAMP *pl,int k,int color)
{
        //sc表示直行灯的颜色，lc表示左灯的颜色    
    switch(k)//初始色都是红灯，k是灯的flag标志，将其切换为color指示的颜色    
    {
        case 1:
                pl->sc=(pl+2)->sc=color;//只切换东西直行
                pl->lc=(pl+2)->lc=RED;
                (pl+1)->sc=(pl+3)->sc=RED;
                (pl+1)->lc=(pl+3)->lc=RED;
                break;

        case 2: 
                pl->lc=(pl+2)->lc=color;//只切换东西左向
                pl->sc=(pl+2)->sc=RED;
                (pl+1)->sc=(pl+3)->sc=RED;
                (pl+1)->lc=(pl+3)->lc=RED;
                break;

        case 3:
                (pl+1)->sc=(pl+3)->sc=color;//只切换南北直行
                (pl+1)->lc=(pl+3)->lc=RED;
                pl->sc=(pl+2)->sc=RED;
                pl->lc=(pl+2)->lc=RED;
                break;

        case 4:
                (pl+1)->lc=(pl+3)->lc=color;//只切换南北左向
                (pl+1)->sc=(pl+3)->sc=RED;
                pl->sc=(pl+2)->sc=RED;
                pl->lc=(pl+2)->lc=RED;
                break;
        default:
                break;
    }
}


/**********************************************************
*函数名：void control_norlamp_s                           *
*功能：丁字口普通仿真模式的交通灯的控制函数                 *
*参数：pl为交通灯结构数组首地址，k为切换的编号，            *
*      color为切换的颜色                                   *
************************************************************/
void control_norlamp_s(struct LAMP *pl,int *flag)
{
    static int t=0;
      
    if(*flag==0)                       //lighten中1234分别为东西直，东西左，南北直，南北左
    {
    	++t;//t为计数器
    	switch(t)
        {
            case 1:
                    lighten_lamp_s(pl,1,LIGHTGREEN);//开东西向直行灯为绿灯
                    break;
            case  TGREEN:
                    lighten_lamp_s(pl,1,YELLOW);//开东西直行为黄灯
                    break;
            case TGREEN+TYELLOW:
                    lighten_lamp_s(pl,2,LIGHTGREEN);//将东西左灯转换为绿色
                    break;
            case 2*TGREEN+TYELLOW:
                    lighten_lamp_s(pl,2,YELLOW);//开东西左向为黄灯
                    break;
            case 2*TGREEN+2*TYELLOW:
                    lighten_lamp_s(pl,3,LIGHTGREEN);//开南北直为绿灯
                    break;
            case 3*TGREEN+2*TYELLOW:
                    lighten_lamp_s(pl,3,YELLOW);//开南北直为黄灯
                    break;
            case 3*TGREEN+3*TYELLOW:
                    lighten_lamp_s(pl,4,LIGHTGREEN);//开南北左行为绿灯
                    break;
            case 4*TGREEN+3*TYELLOW:
                    lighten_lamp_s(pl,4,YELLOW);//开南北左行为黄灯
                    break;
            case 4*TGREEN+4*TYELLOW:
                    t=0;//计数器清零
                    break;
            default:
                    break;
        }
    }
    if(*flag==1)
        t=0;
}

/**********************************************************
*函数名：void check_number_s                              *
*功能：丁字口检查各个路口车辆数目的函数                     *
*参数： n为车辆数目，p为车结构数组首指针，
*             g为时间记录数组首地址                        *
*注被：control_intlamp_s调用                               *
************************************************************/
void check_number_s(int n,struct CAR *p,int g[])
{
    int i=0;
    int c[8]={0,0,0,0,0,0,0,0},a[4]={0,0,0,0}; 
    int lx[4]={BXO-3*RY-RR-20*D,BXO-3*RY-RR,BXO+3*RY+RR,BXO+3*RY+RR+20*D};
    int ly[4]={BYO-3*RX-RR-20*D,BYO-3*RX-RR,BYO+3*RX+RR,BYO+3*RX+RR+20*D};//探测界限待定
	
    for(i=0;i<n;i++)
    {
        switch((p+i)->justment)
        {
		  //算法：逐辆车依次检查在哪个路口，然后在相应的数组上累加
            case 11:
                    if( ( (p+i)->x>lx[2] )&&( (p+i)->x<lx[3] ) )
                        c[0]++;
                    break;
            case 31:
                    if( ( (p+i)->x<lx[1] )&&( (p+i)->x>lx[0] ))
                        c[1]++;
                    break;
            case 12:
                    if( ( (p+i)->x>lx[2] )&&( (p+i)->x<lx[3] ))
                        c[2]++;
                    break;
            case 32:
                    if( ( (p+i)->x<lx[1] )&&( (p+i)->x>lx[0] ))
                        c[3]++;
                    break;
            case 21:
                    if( ( (p+i)->y>ly[2] )&&( (p+i)->y<ly[3] ))
                        c[4]++;
                    break;
            case 41:
                    if( ( (p+i)->y<ly[1] )&&( (p+i)->y>ly[0] ))
                        c[5]++;
                    break;
            case 22:
                    if( ( (p+i)->y>ly[2] )&&( (p+i)->y<ly[3] ))
                        c[6]++;
                    break;
            case 42:
                    if( ( (p+i)->y<ly[1] )&&( (p+i)->y>ly[0] ))
                        c[7]++;
                    break;
        }
    }
    for(i=0;i<4;i++)
    {
        if(c[2*i]>c[2*i+1])  
            a[i]=c[2*i];
        else  
            a[i]=c[2*i+1];
    }
    for(i=0;i<4;i++)
    {
        if(a[i]==0)  g[i]=0;
        if((a[i]>0)&&(a[i]<=LEVEL1))
            g[i]=TGREEN-REDUCE;
        if((a[i]>LEVEL1)&&(a[i]<=LEVEL2) )
            g[i]=TGREEN;
        if((a[i]>LEVEL2)&&(a[i]<=LEVEL3) )
            g[i]=TGREEN+DELAY;				
    }
}

/**********************************************************
*函数名：void control_intlamp_s                           *
*功能：十字口智能仿真模式的交通灯控制函数                   *
*参数：pl为交通灯结构数组首地址，n为车辆总数，            *
*      g时间记录数组首地址，flag清零标志位                  *
*注被：intell调用                                          *
************************************************************/
void control_intlamp_s(struct CAR *p,int n,struct LAMP *pl,int g[],int *flag)
{
    static int t=0;		      
    //t为计数器
    ++t;
     
    if(t==1)
    {	
        check_number_s(n,p,g); 
        lighten_lamp_s(pl,1,LIGHTGREEN);//开东西向直行灯为绿灯
    }    

    if(t==g[0])
        lighten_lamp_s(pl,1,YELLOW); //开东西直行为黄灯
    if(t==(g[0]+TYELLOW))
        lighten_lamp_s(pl,2,LIGHTGREEN);//开东西左向为绿灯
					  
    if(t==(g[0]+TYELLOW+g[1]))
        lighten_lamp_s(pl,2,YELLOW);//开东西左向为黄灯

    if(t==(g[0]+2*TYELLOW+g[1]))
        lighten_lamp_s(pl,3,LIGHTGREEN);//开南北直行为绿灯
					
    if(t==(g[0]+2*TYELLOW+g[1]+g[2]))
        lighten_lamp_s(pl,3,YELLOW);//开南北直行为黄灯					
 
    if(t==(g[0]+3*TYELLOW+g[1]+g[2]))          
        lighten_lamp_s(pl,4,LIGHTGREEN);// 南北左灯转换为绿色
						
    if(t==(g[0]+3*TYELLOW+g[1]+g[2]+g[3]))
        lighten_lamp_s(pl,4,YELLOW);//开南北左向为黄灯
							  
    if(t==(g[0]+4*TYELLOW+g[1]+g[2]+g[3]))  
        t=0;           //循环完一次，计时器清零

    if(*flag==1)
        t=0;  //计时器清零
}