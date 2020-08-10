#include "begin.h"

void drawphone(int left,int top)
{
    int right=left+480;
    int bottom=top+300;
    //画四个圆角
    partcircle(left+50,top+50,90,180,50,WHITE);
    partcircle(right-50,top+50,0,90,50,WHITE);
    partcircle(left+50,bottom-50,180,270,50,WHITE);
    partcircle(left+50,bottom-50,270,360,50,WHITE);
    //连接收集外框
    line_new(left,top+50,left,bottom-50,WHITE,0);
    line_new(right,top+50,right,bottom-50,WHITE,0);
    line_new(left+50,top,right-50,top,WHITE,0);
    line_new(left+50,bottom,right-50,bottom,WHITE,0);
    //画出屏幕分割线
    line_new(left+50,top,left+50,bottom,WHITE,0);
    line_new(right-100,top,right-100,bottom,WHITE,0);
    //画前置摄像头区域
    line_new(left,162,left+10,180,WHITE,0);
    line_new(left,232,left+10,220,WHITE,0);
    partcircle(left-20,top+150,60,120,40,WHITE);
    //画前置摄像头
    partcircle(left+10,top+150,0,360,5,WHITE);
    //  画快门 479，170，230，539，
    partcircle(right-50,top+150,0,360,30,WHITE);
    partcircle(right-50,top+150,0,360,25,WHITE);
    //  画摄像头转化按钮 484，75，534，100
    partcircle(right-50,top+50,0,360,25,WHITE);
    rectangle_new(right-65,top+30,right-35,top+50,WHITE,0);
    partcircle(right-55,top+40,0,360,8,WHITE);
    partcircle(right-55,top+40,0,360,6,WHITE);
    rectangle_new(right-41,top+32,right-37,top+35,WHITE,0);
    partcircle(right-50,top+50,180,270,20,WHITE);
    line_new(top+70,right-50,top+60,right-60,WHITE,0);
    line_new(top+70,right-50,top+80,right-60,WHITE,0);
    partcircle(right-50,top+50,290,360,20,WHITE);
    line_new(top+50,right-30,top+60,right-40,WHITE,0);
    line_new(top+50,right-30,top+60,right-30,WHITE,0);

    setfillstyle(1,WHITE);
    floodfill(right-50,top+150,WHITE);
    floodfill(left+10,top+150,WHITE);
}

void extendline(int sx,int sy,int ex,int ey,int color)
{
    int x,y;
    if(ex!=sx) float k=(ey-sy)/(ex-sx);
    if(ex==sx)
    {
        if(sy<ey)
        {
            for(y=sy;y<=ey;y++)
            {
                line_new(sx,sy,x,y,WHITE,0);
            }
        }
        else
        {
            for(y=sy;y>=ey;y--)
            {
                line_new(sx,sy,x,y,WHITE,0);
            }
        }
    }
    else
    {
        if(ex>sx)
        {
            for(x=sx;x<=ex;x++)
            {
                y=(x-sx)*k+sy;
                line_new(sx,sy,x,y,WHITE,0);
            }
        }
        else
        {
            for(x=sx;x>=ex;x--)
            {
                y=(x-sx)*k+sy;
                line_new(sx,sy,x,y,WHITE,0);
            }
        }
    }
}

int fbegin()
{
    char *s1="照片编辑系统";
    char *s2="按下快门";
    char *s3="记录美好瞬间";
    char *x1="打开程序";
    char *x2="雕琢花样流年"
    char *s4="点击快门进入程序";
    char *x3="开发者 刘旭阳 胡睿"
    int screen=1;
    int flag=0;
    int page=0;

    //绘制界面底色等
    bar_new(1,11,639,479,BLACK,0);
    bar_new(1,1,639,11,LIGHTGRAY,0);
    bar_new(619,0,639,10,RED,0);//退出图标
    line_new(624,0,634,10,WHITE,0);
    line_new(624,10,634,0,WHITE,0);
    //绘制手机图画
    drawphone(79,49);

    extendline(0,379,479,379,WHITE);
    extendline(479,459,159,459,WHITE);
    hanzi24kaiti(180,399,x3,WHITE);

    while(page==0)
    {
        mou_pos(&MouseX,&MouseY,&press);
        if(mouse_press(479,170,230,539) == 1||mouse_press(479,170,230,539) == 2)
        {
            setfillstyle(1,WHITE);
            floodfill(509,199,WHITE);
            floodfill(532,199,WHITE);
        }
        else
        {
            setfillstyle(1,BLACK);
            floodfill(532,199,WHITE);
            partcircle(509,199,0,360,25,WHITE);
            setfillstyle(1,WHITE);
            floodfill(509,199,WHITE);
        }
        if(mouse_press(479,170,230,539) == 1)
        {
            clrmous(MouseX,MouseY);
            delay(50);
            page=1;
        }
        if(mouse_press(619,0,639,10) == 1)
        {
            clrmous(MouseX,MouseY);
            delay(50);
            page=-1;
        }
        if(mouse_press(484,75,534,100) == 1)
        {
            screen=-1*screen;
            flag=0;
            delay(500);
        }
        if(screen==1&&flag==0)
        {
            bar_new(129,50,459,350,BLACK,0);
            delay(500);
            hanzi24kaiti(220,50,s1,WHITE);
            delay(500);
            hanzi24kaiti(200,150,s2,WHITE);
            delay(500);
            hanzi24kaiti(270,200,s3,WHITE);
            delay(500);
            hanzi24kaiti(270,200,s4,WHITE);
            delay(500);
            extendline(129,300,284,350,WHITE);
            extendline(459,300,284,350,WHITE);
            flag=1;
        }
        else if(screen==-1&&flag==0)
        {
            bar_new(129,50,459,350,WHITE,0);
            delay(50);
            hanzi24kaiti(220,50,s1,BLACK);
            delay(500);
            hanzi24kaiti(200,150,x2,BLACK);
            delay(500);
            hanzi24kaiti(270,250,x3,BLACK);
            delay(500);
            hanzi24kaiti(270,200,s4,BLACK);
            delay(500);
            extendline(129,300,284,350,BLACK);
            extendline(459,300,284,350,BLACK);
            flag=1;
        }
    }
    return page;
}
