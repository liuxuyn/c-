/***************************************************************
*           *本文件为十字口分析功能函数集合                     *
*           *车辆信息，条形图，超速车牌，优化率                 *
*           *作者：李鑫                                        *
*           *最终修改时间：2010.11.4                           *
****************************************************************/

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <bios.h>
#include "all.h"
#include "drawtool.h"
#include "fenxi_s.h"

/*******************************************************
*函数名：void fenxi_tiao_s                             *
*功能：画分析条形图                                    *
*参数说明：ntm为常规仿真时间结构指针，itm为智能时间      *
********************************************************/
void fenxi_tiao_s(struct TM *ntm,struct TM *itm)
{
    int i=0;
    int ntime=0,itime=0;
    float rate=0;
    char  r[5]={'\0','\0','\0','\0','\0'};
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
    line(60,380,480,380);
    outtextxy(483,375,"x");
    line(60,380,60,475);
    outtextxy(50,467,"y");
    //画箭头
    line(480,380,473,377);
    line(480,380,473,383);
    line(60,475,57,468);
    line(60,475,63,468);	
    //画点
    for(i=0;i<21;i++)  //x轴
    {
        pot(60+i*20,380);
        outtextxy(60+i*20-4,380-11,ch[i]);
    }
    //y轴上点
    pot(60,380+15);
    pot(60,380+40);
    word_write(18,380+23,"智能",BLACK,12);
    pot(60,380+55);
    pot(60,380+80);
    word_write(18,380+63,"常规",BLACK,12);
    //画条形图
    settextstyle(0,0,1);
    setfillstyle(1,YELLOW);
    setcolor(BLACK);
    bar(60,395,60+itime*4,420);
    rectangle(60,395,60+itime*4,420);
    outtextxy(60+itime*4+5,405,ch2);	
    setfillstyle(1,RED);
    bar(60,435,60+ntime*4,460);
    rectangle(60,435,60+ntime*4,460);
    outtextxy(60+ntime*4+5,445,ch1);
    //优化率
    word_write(545,374,"优化率:",BLACK,16);
    if(itime!=0&&ntime!=0)
    {
        rate=((float)(ntime-itime))/ntime;
        r[0]=((int)(rate*100))/10+'0';
        r[1]=((int)(rate*100))%10+'0';
        r[2]='.';
        r[3]=((int)(rate*1000))%10+'0';
        r[4]='%';
        r[5]='\0';
        settextstyle(0,0,2);
        setcolor(YELLOW);
        outtextxy(540,400,r);
    }	
}


/*******************************************************
*函数名：void fenxi_spn_s                             *
*功能：显示超速车牌号                                   *
*参数说明：car为车辆结构数组首地址，n为车辆总数          *
********************************************************/
void fenxi_spn_s(struct CAR *car,int n)
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
     rectangle(568,64,625,362);
     rectangle(569,65,624,361);
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
*函数名：void fenxi_bk_s                              *
*功能：画分析界面通用模板并显示数据                     *
*参数说明：ch,ch1,ch2为二维数组首地址，存储车辆数据     *
********************************************************/
void fenxi_bk_s(char ch[][3],char ch1[][3],char ch2[][3])
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
    //北路
    word_write(50,320,"北路",BLACK,16);
    Mline(45,298,508+16*3+5,298);
    word_write(100,300,"右行",BLUE,16);
    Mline(90,318,508+15,318);
    word_write(100,320,"直行",YELLOW,16);
    Mline(90,338,508+15,338);
    word_write(100,340,"左行",RED,16);
    Mline(45,358,508+16*3+5,358);
    //画竖线
    Mline(45,68,45,358);
    Mline(90,88,90,358);
    Mline(148,68,148,358);
    Mline(282-16*2,68,282-16*2,358);
    Mline(394-32,68,394-32,358);
    Mline(508-32,68,508-32,358);
    Mline(508+15,88,508+15,358);
    Mline(508+48+5,68,508+48+5,358);
    //画斜线
    Mline(45,68,148,88);
    //画粗隔线
    setfillstyle(1,MAGENTA);
    bar(45,148,508+16*3+5,158);
    bar(45,218,508+16*3+5,228);
    bar(45,288,508+16*3+5,298);
    //画四外边框
    setcolor(MAGENTA);
    rectangle(43,66,508+55,360);
    rectangle(42,65,508+56,361);
    rectangle(41,64,508+57,362);
    //输出数据
    settextstyle(0,0,1);
    setcolor(BLACK);
    for(i=0,j=0;i<12;i++)
    {
        if(i!=0&&i%3==0)    j++;
        //输出每行每种车速车的数量
        outtextxy(170+16,90+i*20+10*j+6,ch[3*i]);
        outtextxy(282+16,90+i*20+10*j+6,ch[3*i+1]);
        outtextxy(394+16,90+i*20+10*j+6,ch[3*i+2]);
        //输出每条道车的数量
        outtextxy(508-12,90+i*20+10*j+6,ch1[i]);
    }
    for(i=0,j=0;i<4;i++)
    {
        outtextxy(508+24,110+j*70+6,ch2[i]);
        j++;
    }
}


/************************************************************
*函数名：void count_spnum_s                                 *
*功能：统计每种车速的车                                     *
*参数说明：n为车辆数组首地址，ch为二维数组首地址，存储车辆数据*
*************************************************************/
void count_spnum_s(int n[],char (* ch)[3])
{
    int i=0;
    for(i=0;i<36;i++)
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
*函数名：void count_012num_s                                  *
*功能：统计每个车道的车数                                     *
*参数说明：n为车辆数组首地址，ch1为二维数组首地址，存储车辆数据 *
*************************************************************/
void count_012num_s(int n[],char (* ch1)[3])
{
    int i=0;
    for(i=0;i<12;i++)
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
*函数名：void count_rdnum_s                                  *
*功能：统计4个路口的车数                                     *
*参数说明：n为车辆数组首地址，ch2为二维数组首地址，存储车辆数据 *
*************************************************************/
void count_rdnum_s(int n[],char (* ch2)[3])
{
    int i=0;
    int f[4]={0,0,0,0};
    for(i=0;i<4;i++)
    f[i]=n[9*i]+n[9*i+1]+n[9*i+2]+n[9*i+3]+n[9*i+4]+n[9*i+5]
          +n[9*i+6]+n[9*i+7]+n[9*i+8];

    for(i=0;i<4;i++)
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
*函数名：int fenxi_s                                                  *
*功能：统计3个路口的车数                                               *
*参数说明：car为车辆数组结构首地址，car1为当前，ntm,itm时间，n为车辆总数 *
***********************************************************************/
int fenxi_s(struct CAR *car,struct CAR *car1,struct TM *ntm,struct TM *itm,int n)
{
    int i=0,key=0;
    int num[36];  //用于记录
    char ch[36][3],ch1[12][3],ch2[4][3]; //用于输出
    for(i=0;i<36;i++)   //赋初值
        num[i]=0;
    for(i=0;i<n;i++)
    {
        switch(car[i].justment)
        {
            case 10:
                    if(car[i].std_speed==1*RATE)  num[0]++;  
                    if(car[i].std_speed==2*RATE)  num[1]++;  
                    if(car[i].std_speed==3*RATE)  num[2]++;  
                    break;
            case 11:
                    if(car[i].std_speed==1*RATE)  num[3]++; 
                    if(car[i].std_speed==2*RATE)  num[4]++; 
                    if(car[i].std_speed==3*RATE)  num[5]++;  
                    break;
            case 12:
                    if(car[i].std_speed==1*RATE)  num[6]++; 
                    if(car[i].std_speed==2*RATE)  num[7]++; 
                    if(car[i].std_speed==3*RATE)  num[8]++; 
                    break;
            case 20:
                    if(car[i].std_speed==1*RATE)  num[9]++; 
                    if(car[i].std_speed==2*RATE)  num[10]++; 
                    if(car[i].std_speed==3*RATE)  num[11]++; 
                    break;
            case 21:
                    if(car[i].std_speed==1*RATE)  num[12]++; 
                    if(car[i].std_speed==2*RATE)  num[13]++; 
                    if(car[i].std_speed==3*RATE)  num[14]++; 
                    break;
            case 22:
                    if(car[i].std_speed==1*RATE)  num[15]++; 
                    if(car[i].std_speed==2*RATE)  num[16]++; 
                    if(car[i].std_speed==3*RATE)  num[17]++;  
                    break;
            case 30:
                    if(car[i].std_speed==1*RATE)  num[18]++; 
                    if(car[i].std_speed==2*RATE)  num[19]++; 
                    if(car[i].std_speed==3*RATE)  num[20]++; 
                    break;
            case 31:
                    if(car[i].std_speed==1*RATE)  num[21]++;  
                    if(car[i].std_speed==2*RATE)  num[22]++;  
                    if(car[i].std_speed==3*RATE)  num[23]++; 
                    break;
            case 32:
                    if(car[i].std_speed==1*RATE)  num[24]++; 
                    if(car[i].std_speed==2*RATE)  num[25]++; 
                    if(car[i].std_speed==3*RATE)  num[26]++; 
                    break;
            case 40:
                    if(car[i].std_speed==1*RATE)  num[27]++; 
                    if(car[i].std_speed==2*RATE)  num[28]++; 
                    if(car[i].std_speed==3*RATE)  num[29]++; 
                    break;
            case 41:
                    if(car[i].std_speed==1*RATE)  num[30]++; 
                    if(car[i].std_speed==2*RATE)  num[31]++; 
                    if(car[i].std_speed==3*RATE)  num[32]++; 
                    break;
            case 42:
                    if(car[i].std_speed==1*RATE)  num[33]++; 
                    if(car[i].std_speed==2*RATE)  num[34]++; 
                    if(car[i].std_speed==3*RATE)  num[35]++; 
                    break;
        }
    }

    count_spnum_s(num,ch);  //记录每种速度的车
    count_012num_s(num,ch1);//记录每条车道的车
    count_rdnum_s(num,ch2); //记录每条路的车
    fenxi_bk_s(ch,ch1,ch2);  //输出
    fenxi_spn_s(car1,n);
    fenxi_tiao_s(ntm,itm);
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
*函数名：int check_off_s                                              *
*功能：检测所有车是否都驶出桌面                                        *
*参数说明：car为车辆结构数组首地址，n为车辆总数                         *
***********************************************************************/
int check_off_s(struct CAR *car,int n)
{
    int i=0;
    for(i=0;i<n;i++)     //flag==1说明该车驶离了桌面
    {
        switch(car[i].justment)
        {
            case 20:
            case 31:
            case 42:if(car[i].x-D-8>BX)
                        car[i].flag=1;
                    break;
            case 12:
            case 30:
            case 41:if(car[i].y-D-8>BY)
                        car[i].flag=1;
                    break;
            case 11:
            case 22:
            case 40:if(car[i].x+D+8<0)    //不加2会留个车尾
                        car[i].flag=1;
                    break;
            case 10:
            case 21:
            case 32:if(car[i].y+D+8<0)
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

/**********************************************************************
*函数名：void check_sp                                                 *
*功能：检测车是否超速                                                  *
*参数说明：car为车辆结构数组首地址，n为车辆总数                         *
***********************************************************************/
void check_sp(struct CAR *p,int n)
{
    int i=0,f=0;
    for(i=0;i<n;i++)
    {
        if(p[i].flag==0&&p[i].speed>2*RATE&&p[i].spflag==0)
        {
             p[i].spflag=1; 
             setcolor(RED);
             circle(p[i].x,p[i].y,15);
             circle(p[i].x,p[i].y,16);
             f=1;
        }	
    }
    if(f>0)
        getch();
}