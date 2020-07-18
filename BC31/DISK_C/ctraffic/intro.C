/***************************************************
*           *本文件为程序开始简介                  *
*           *作者：李鑫                            *
*           *最终修改时间：2011.11.4                *
*****************************************************/

#include <graphics.h>
#include <dos.h>
#include <bios.h>
#include <conio.h>
#include "all.h"
#include "drawtool.h"
#include "intro.h"

/***********************************************
*函数名：void intro_circle                     *
*功能：一个逐渐放大的圆的动画                   *
*参数：void                                    *
************************************************/
void intro_circle(void)
{
    int i,j;
    setfillstyle(1,DARKGRAY);
    setcolor(WHITE);
    for(i=0;i<400;i++)
    {
        fillellipse(ENDX/2,ENDY/2,i,i);
    }
}

/***********************************************
*函数名：void instruction                      *
*功能：简介                                    *
*参数：void                                    *
************************************************/
void introduct(void)
{
    typedef struct words          //介绍界面结构体 作用范围仅在此界面
    {
        int x;
        int y;
        char *stc;	      //stc：要显示的信息
        unsigned char color;
        unsigned char charsize;
    }WORDS;
    int i=0,j=80;
 

    WORDS sentence[4]={
                        {240,160,"智能交通图形仿真系统",RED,16},
                        {288,200,"团队介绍",RED,16},
                        {296,240,"李 鑫 U201013673",BLUE,16},
                        {296,280,"国悦婷 U201013694",BLUE,16},
                      };
    WORDS *p=sentence;
    init_VGA();
    setbkcolor(BLACK);
    intro_circle();
    for(i=0;i<4;i++)
    {
        word_write(p[i].x,p[i].y,p[i].stc,p[i].color,p[i].charsize);
        delay(100);
    }

    while(j)
    {
        delay(50);
        if(bioskey(1))
        {
            getch();
            return;
        }
        j--;
    }
}



