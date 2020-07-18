/***************************************************************
*           *本文件为丁字口分析功能函数集合                     *
*           *车辆信息，条形图，超速车牌，优化率                 *
*           *作者：李鑫                                        *
*           *最终修改时间：2010.11.4                           *
****************************************************************/

#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <graphics.h>
#include "all.h"
#include "drawtool.h"
#include "fenxi_d.h"

/*******************************************************
*函数名：void fenxi_tiao_d                             *
*功能：画分析条形图                                    *
*参数说明：ntm为常规仿真时间结构指针，itm为智能时间      *
********************************************************/
void fenxi_tiao_d(struct TM *ntm,struct TM *itm)
{
    int i=0;
    int ntime=0,itime=0;
    float rate=0;
    char  r[6]={'\0','\0','\0','\0','\0','\0'};
    char *ch[21]={"0","5","10","15","20","25","30","35","40","45","50",
		  "55","60","65","70","75","80","85","90","95","100"};
    char ch1[4],ch2[4];
    ntime=ntm->minute*60+ntm->second;
    itime=itm->minute*60+itm->second;
    if(ntime<100)
    {
        ch1[0]=ntime/10+'0';
        ch1[1]=ntime%10+'0';
        ch1[2]='\0';
    }
    else 
    {
        ch1[0]=ntime/100+'0';
        ch1[1]=(ntime%100)/10+'0';
        ch1[2]=ntime%10+'0';
        ch1[3]='\0';
    }
    if(itime<100)
    {
        ch2[0]=itime/10+'0';
        ch2[1]=itime%10+'0';
        ch2[2]='\0';
    }
    else
    {
        ch2[0]=itime/100+'0';
        ch2[1]=(itime%100)/10+'0';
        ch2[2]=itime/10+'0';
        ch2[3]='\0';
    }
    settextstyle(0,0,1);
    setcolor(BLACK);
    //画xy轴
    line(60,350,480,350);
    outtextxy(483,345,"x");
    line(60,350,60,445);
    outtextxy(50,437,"y");
    //画箭头
    line(480,350,473,347);
    line(480,350,473,353);
    line(60,445,57,438);
    line(60,445,63,438);	
    //画点
    for(i=0;i<21;i++)  //x轴
    {
        pot(60+i*20,350);
        outtextxy(60+i*20-4,350-11,ch[i]);
    }
    //y轴上点
    pot(60,350+15);
    pot(60,350+40);
    word_write(18,350+23,"智能",BLACK,12);
    pot(60,350+55);
    pot(60,350+80);
    word_write(18,350+63,"常规",BLACK,12);
    //画条形图
    settextstyle(0,0,1);
    setfillstyle(1,YELLOW);
    setcolor(BLACK);
    bar(60,365,60+itime*4,390);
    rectangle(60,365,60+itime*4,390);
    outtextxy(60+itime*4+5,375,ch2);	
    setfillstyle(1,RED);
    bar(60,405,60+ntime*4,430);
    rectangle(60,405,60+ntime*4,430);
    outtextxy(60+ntime*4+5,415,ch1);
    //优化率
    word_write(545,344,"优化率:",BLACK,16);
    if(itime!=0&&ntime!=0)
    {
        rate=((float)(ntime-itime))/ntime;
        if(rate>=0)
        {	
            r[0]=((int)(rate*100))/10+'0';
            r[1]=((int)(rate*100))%10+'0';
            r[2]='.';
            r[3]=((int)(rate*1000))%10+'0';
            r[4]='%';
            r[5]='\0';
            settextstyle(0,0,2);
            setcolor(YELLOW);
            outtextxy(540,370,r);
        }
        if(rate<0)
        {
            rate=rate*(-1);
            r[0]='-';
            r[1]=((int)(rate*100))/10+'0';
            r[2]=((int)(rate*100))%10+'0';
            r[3]='.';
            r[4]=((int)(rate*1000))%10+'0';
            r[5]='%';
            r[6]='\0';
            settextstyle(0,0,2);
            setcolor(YELLOW);
            outtextxy(540-15,370,r);
        }
    }	
}


/*******************************************************
*函数名：void fenxi_spn_d                              *
*功能：显示超速车牌号                                   *
*参数说明：car为车辆结构数组首地址，n为车辆总数          *
********************************************************/
void fenxi_spn_d(struct CAR *car,int n)
{
    int i=0,num=0;
    char ch[CAR_SPMAX][3];
    for(i=0;i<CAR_SPMAX;i++)
    {
        ch[i][0]='\0';
        ch[i][1]='\0';
        ch[i][2]='\0';
    }
    num=0;
    for(i=0;i<n;i++)
    {
        if(car[i].spflag==1)
        {
            if(car[i].cnum<10)
            {
                ch[num][0]='0';
                ch[num][1]=car[i].cnum+'0';
                ch[num][2]='\0';
            }
            else
            {
                ch[num][0]=car[i].cnum/10+'0';
                ch[num][1]=car[i].cnum%10+'0';
                ch[num][2]='\0';
            }
            num++;
        }	
    }
    setcolor(MAGENTA);
    rectangle(568,64,625,292);
    rectangle(569,65,624,291);
    line(568,64+25,625,64+25);
    line(568,64+26,625,64+26);
    line(568,90+25,625,90+25);
    line(568,90+26,625,90+26);
    word_write(569+4,64+5,"超速车",BLACK,16);
    word_write(569+4,90+5,"车牌号",BLACK,16);
    settextstyle(0,0,1);
    setcolor(RED);
    for(i=0;i<num;i++)
    {
        outtextxy(567+20,125+i*15,ch[i]);
    }
}

/*******************************************************
*函数名：void fenxi_bk_d                               *
*功能：画分析界面通用模板并显示数据                     *
*参数说明：ch,ch1,ch2为二维数组首地址，存储车辆数据     *
********************************************************/
void fenxi_bk_d(char ch[][3],char ch1[][3],char ch2[][3])
{
    int i=0,j=0;
    init_VGA();
    cleardevice();
    setbkcolor(BLACK);
    setfillstyle(1,MAGENTA);
    bar(STARTX,STARTY,ENDX,ENDY);  //洋红边框
    setfillstyle(1,LIGHTGRAY);
    bar(STARTX+2,STARTY+2,ENDX-2,ENDY-2);
    word_write(ENDX/2-16*3,STARTY+10,"《仿真分析》",BLACK,16);
    word_write(5,35,"以下是本次仿真的车辆数据（按路口，车道和车速统计）：",BLACK,16);
	
    //表头
    Mline(45,68,508+16*3+5,68);	                //   |
    word_write(170,70,"慢速车    中速车    快速车   合  计",BLACK,16);
    //东路   //横坐标  170       282       394        508
    word_write(50,110,"东路",BLACK,16);
    Mline(45,88,508+16*3+5,88);	
    word_write(100,90,"右行",BLUE,16);
    Mline(90,108,508+15,108);
    word_write(100,110,"直行",YELLOW,16);
    Mline(90,128,508+15,128);
    word_write(100,130,"左行",RED,16);  //两路相隔15
    Mline(45,148,508+16*3+5,148);
    //南路
    word_write(50,180,"南路",BLACK,16);
    Mline(45,158,508+16*3+5,158);
    word_write(100,160,"右行",BLUE,16);
    Mline(90,178,508+15,178);
    word_write(100,180,"直行",YELLOW,16);
    Mline(90,198,508+15,198);
    word_write(100,200,"左行",RED,16);
    Mline(45,218,508+16*3+5,218);
    //西路
    word_write(50,250,"西路",BLACK,16);
    Mline(45,228,508+16*3+5,228);
    word_write(100,230,"右行",BLUE,16);
    Mline(90,248,508+15,248);
    word_write(100,250,"直行",YELLOW,16);
    Mline(90,268,508+15,268);
    word_write(100,270,"左行",RED,16);
    Mline(45,288,508+16*3+5,288);
    //画竖线
    Mline(45,68,45,288);
    Mline(90,88,90,288);
    Mline(148,68,148,288);
    Mline(282-16*2,68,282-16*2,288);
    Mline(394-32,68,394-32,288);
    Mline(508-32,68,508-32,288);
    Mline(508+15,88,508+15,288);
    Mline(508+48+5,68,508+48+5,288);
    //画斜线
    Mline(45,68,148,88);
    //画粗隔线
    setfillstyle(1,MAGENTA);
    bar(45,148,508+16*3+5,158);
    bar(45,218,508+16*3+5,228);
    //画四外边框
    setcolor(MAGENTA);
    rectangle(43,66,508+55,290);
    rectangle(42,65,508+56,291);
    rectangle(41,64,508+57,292);
    //输出数据
    //东直
    settextstyle(0,0,1);
    setcolor(BLACK);
    outtextxy(170+16,90+20+6,ch[0]);
    outtextxy(282+16,90+20+6,ch[1]);
    outtextxy(394+16,90+20+6,ch[2]);
    outtextxy(508-12,90+20+6,ch1[0]);
    //东左
    outtextxy(170+16,90+2*20+6,ch[3]);
    outtextxy(282+16,90+2*20+6,ch[4]);
    outtextxy(394+16,90+2*20+6,ch[5]);
    outtextxy(508-12,90+2*20+6,ch1[1]);
    //南右
    outtextxy(170+16,90+3*20+10+6,ch[6]);
    outtextxy(282+16,90+3*20+10+6,ch[7]);
    outtextxy(394+16,90+3*20+10+6,ch[8]);	
    outtextxy(508-12,90+3*20+10+6,ch1[2]);
    //南左
    outtextxy(170+16,90+5*20+10+6,ch[9]);
    outtextxy(282+16,90+5*20+10+6,ch[10]);
    outtextxy(394+16,90+5*20+10+6,ch[11]);
    outtextxy(508-12,90+5*20+10+6,ch1[3]);
    //西右
    outtextxy(170+16,90+6*20+20+6,ch[12]);
    outtextxy(282+16,90+6*20+20+6,ch[13]);
    outtextxy(394+16,90+6*20+20+6,ch[14]);
    outtextxy(508-12,90+6*20+20+6,ch1[4]);		
    //西左
    outtextxy(170+16,90+7*20+20+6,ch[15]);
    outtextxy(282+16,90+7*20+20+6,ch[16]);
    outtextxy(394+16,90+7*20+20+6,ch[17]);
    outtextxy(508-12,90+7*20+20+6,ch1[5]);	
    //输出每个路口的车辆总数
    for(i=0,j=0;i<3;i++)
    {
        outtextxy(508+24,110+j*70+6,ch2[i]);
        j++;
    }
}

/************************************************************
*函数名：void count_spnum_d                                 *
*功能：统计每种车速的车                                     *
*参数说明：n为车辆数组首地址，ch为二维数组首地址，存储车辆数据*
*************************************************************/
void count_spnum_d(int n[],char (* ch)[3])
{
    int i=0;
    for(i=0;i<18;i++)
    {
        if(n[i]<10)
        {
            ch[i][0]=n[i]+'0';
            ch[i][1]=ch[i][2]='\0';
        }
        else
        {
            ch[i][0]=n[i]/10+'0';
            ch[i][1]=n[i]%10+'0';
            ch[i][2]='\0';
        }
    }
}

/*************************************************************
*函数名：void count_012num_d                                  *
*功能：统计每个车道的车数                                     *
*参数说明：n为车辆数组首地址，ch1为二维数组首地址，存储车辆数据 *
*************************************************************/
void count_012num_d(int n[],char (* ch1)[3])
{
    int i=0;
    for(i=0;i<6;i++)
    {
        if((n[3*i]+n[3*i+1]+n[3*i+2])<10)
        {
            ch1[i][0]=(n[3*i]+n[3*i+1]+n[3*i+2])+'0';
            ch1[i][1]=ch1[i][2]='\0';
        }
        else
        {
            ch1[i][0]=(n[3*i]+n[3*i+1]+n[3*i+2])/10+'0';
            ch1[i][1]=(n[3*i]+n[3*i+1]+n[3*i+2])%10+'0';
            ch1[i][2]='\0';
        }
    }
}

/*************************************************************
*函数名：void count_rdnum_d                                  *
*功能：统计3个路口的车数                                     *
*参数说明：n为车辆数组首地址，ch2为二维数组首地址，存储车辆数据 *
*************************************************************/
void count_rdnum_d(int n[],char (* ch2)[3])
{
    int i=0;
    int f[3]={0,0,0};
    for(i=0;i<3;i++)
    f[i]=n[6*i]+n[6*i+1]+n[6*i+2]+n[6*i+3]+n[6*i+4]+n[6*i+5];

    for(i=0;i<3;i++)
    {
        if(f[i]<10)
        {
            ch2[i][0]=f[i]+'0';
            ch2[i][1]='\0';
        }
        else
        {
            ch2[i][0]=f[i]/10+'0';
            ch2[i][1]=f[i]%10+'0';
            ch2[i][2]='\0';
        }
    }
}


/**********************************************************************
*函数名：int fenxi_d                                                  *
*功能：统计3个路口的车数                                              *
*参数说明：car为车辆数组结构首地址，car1为当前，ntm,itm时间，n为车辆总数 *
***********************************************************************/
int fenxi_d(struct CAR *car,struct CAR *car1,struct TM *ntm,struct TM *itm,int n)
{
    int i=0,key=0;
    int num[18];  //用于记录
    char ch[18][3],ch1[6][3],ch2[3][3]; //用于输出
    for(i=0;i<18;i++)   //赋初值
        num[i]=0;
    for(i=0;i<n;i++)
    {
        switch(car[i].justment)
        {
            case 11:
                    if(car[i].std_speed==1*RATE)  num[0]++; 
                    if(car[i].std_speed==2*RATE)  num[1]++; 
                    if(car[i].std_speed==3*RATE)  num[2]++; 
                    break;
            case 12:
                    if(car[i].std_speed==1*RATE)  num[3]++; 
                    if(car[i].std_speed==2*RATE)  num[4]++; 
                    if(car[i].std_speed==3*RATE)  num[5]++; 
                    break;
            case 20:
                    if(car[i].std_speed==1*RATE)  num[6]++; 
                    if(car[i].std_speed==2*RATE)  num[7]++; 
                    if(car[i].std_speed==3*RATE)  num[8]++; 
                    break;
            case 22:
                    if(car[i].std_speed==1*RATE)  num[9]++; 
                    if(car[i].std_speed==2*RATE)  num[10]++; 
                    if(car[i].std_speed==3*RATE)  num[11]++; 
                    break;
            case 30:
                    if(car[i].std_speed==1*RATE)  num[12]++; 
                    if(car[i].std_speed==2*RATE)  num[13]++; 
                    if(car[i].std_speed==3*RATE)  num[14]++; 
                    break;
            case 31:
                    if(car[i].std_speed==1*RATE)  num[15]++; 
                    if(car[i].std_speed==2*RATE)  num[16]++; 
                    if(car[i].std_speed==3*RATE)  num[17]++; 
                    break;
        }
    }

    count_spnum_d(num,ch);  //记录每种速度的车
    count_012num_d(num,ch1);//记录每条车道的车
    count_rdnum_d(num,ch2); //记录每条路的车
    fenxi_bk_d(ch,ch1,ch2);  //输出
    fenxi_spn_d(car1,n);    //显示超速车车牌
    fenxi_tiao_d(ntm,itm);  //画条形图

    while(1)
    {
        if(kbhit())
        {
            key=bioskey(0);
            if(key==BACK)
            {
                closegraph();
                return EXIT;
            }
        }
    }
}

/**********************************************************************
*函数名：int check_off_d                                              *
*功能：检测所有车是否都驶出桌面                                        *
*参数说明：car为车辆结构数组首地址，n为车辆总数                         *
***********************************************************************/
int check_off_d(struct CAR *car,int n)
{
    int i=0;
    for(i=0;i<n;i++)     //flag==1说明该车驶离了桌面
    {
        switch(car[i].justment)
        {
            case 20:
            case 31:if(car[i].x-D-8>BX)
                        car[i].flag=1;
                    break;
            case 12:
            case 30:if(car[i].y-D-8>BY)
                        car[i].flag=1;
                    break;
            case 11:
            case 22:if(car[i].x+D+8<0)    //不加8会留个车尾
                        car[i].flag=1;
                    break;
        }
    } 
    for(i=0;i<n;i++)
    {
        if(car[i].flag==0)
            break;
    }
    if(i>=n)   return 1;
    else     return 0;  
}