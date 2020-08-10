#include "helper.h"

void help(int No)//No:41 关于 42调整介绍 43修饰介绍
{
    int wordh=textheight("w"),wordw=textwidth("w");
    imagesave storage;
    storage.local[0]=1;
    storage.local[1]=11;
    storage.local[2]=638;
    storage.local[3]=478;

     if((storage.ibuffer=(unsigned char*)malloc(imagesize(1,11,639,479)))==NULL)
    {
        return 0;
    }
    else
    {
    getimage(1,11,638,478,storage.ibuffer);
    }

    bar_new(1,11,638,478,DARKGRAY,0);

    char *s1="软件开发信息";
    char *s2="开发人员单位"
    char *s3="华中科技大学人工智能与自动化学院";
    char *s4="开发者 刘旭阳 胡睿";
    char *s5="该程序是c语言课程设计项目"
    char *s6="水平有限 欢迎反馈";
    char *s7="希望此程序为您的美好生活锦上添花";
    char *s8="键盘按下回车回到主界面";

    char *x1="调整部分功能介绍";
    char *x2="镜像 包括水平翻转和竖直翻转";
    char *x3="缩放 需要您先后输入横轴和纵轴缩放比例 请输入一个正小数且不要超过一点五";
    char *x4="裁剪 需要您先后点击图片上两点作为新图片的一条对角线的两端点";

    char *y1="修饰部分功能介绍"
    char *y2="扩散 柔化 锐化都有五个等级，等级越高效果越明显";
    char *y3="滤镜 包括数个不同功能 欢迎体验";

    switch(No)
    {
        case 41:
            {
                hz48(200,30,630,470,s1,217);
                hz24kaiti(20,100,620,460,s2,217);
                hz24kaiti(20,150,620,460,s3,217);
                hz24kaiti(20,200,620,460,s4,217);
                hz24kaiti(20,250,620,460,s5,217);
                hz24kaiti(20,300,620,460,s6,217);
                hz24kaiti(20,350,620,460,s7,217);
                hz48(200,400,630,470,s8,217);
            }
            break;

        case 42:
            {
                hz48(200,30,630,470,x1,217);
                hz24kaiti(20,100,620,460,x2,217);
                hz24kaiti(20,150,620,460,x3,217);
                hz24kaiti(20,300,620,460,x4,217);
                hz48(200,400,630,470,s8,217);
            }
            break;

        case 43:
            {
                hz48(200,30,630,470,y1,217);
                hz24kaiti(20,100,620,460,y2,217);
                hz24kaiti(20,150,620,460,y3,217);
                hz24kaiti(20,250,620,460,y4,217);
                hz48(200,400,630,470,s8,217);
            }
    }


	while(1)
    {
        mos_pos(&MouseX,&MouseY,&press);
        if(bioskey(1)||mouse_press(1,11,638,478)==1)
        {
            exitmenu(&storage);
            return ;
        }
    }
}
