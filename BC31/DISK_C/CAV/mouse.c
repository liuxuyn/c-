#include<stdio.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include"mouse.h"
#include"head.h"
#include"SVGA.h"
int MouseSave[16][16];    /*用于保存鼠标即将覆盖的区域*/
int MouseDot[16][16]=   //设计鼠标的形状,其中1:表示鼠标的区域,2:表示鼠标边界所包围的区域的边界,0:表示鼠标以外的区域  
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,
		0,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,
		0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,
		0,2,1,1,1,1,1,2,0,0,0,0,0,0,0,0,
		0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,
		0,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0,
		0,2,1,1,1,1,1,2,2,0,0,0,0,0,0,0,
		0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,
		0,2,1,2,2,1,1,2,0,0,0,0,0,0,0,0,
		0,2,2,0,2,1,1,2,0,0,0,0,0,0,0,0,
		0,0,0,0,0,2,1,1,2,0,0,0,0,0,0,0,
		0,0,0,0,0,2,1,1,2,0,0,0,0,0,0,0,
		0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0 
	};


//初始化鼠标

void MouseReset()     
{
    /*检查是否安装了鼠标驱程或者鼠标*/
	union REGS regs;
	int retcode;
    regs.x.ax=0;
    int86(51,&regs,&regs);
    retcode=regs.x.ax;
    if(retcode==0)
    {
		printf("mouse or mouse driver is absent,please install ");
		getch();
		exit(1);
    }
    return;
}
//设置鼠标位置
void SetMousePosition(int x,int y)
{
	union REGS regs;
    regs.x.ax=4;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(51,&regs,&regs);//设置鼠标当前坐标			 
	return ;
}


	//设置鼠标倍速阈值；
	//v为鼠标即将设定的倍速阈值

void SetMouseVelo(int v)
{
	union REGS regs;
    regs.x.ax=0x13;
    regs.x.dx=v;
	int86(51,&regs,&regs);
}


	//设置鼠标计数与像素比,值越大鼠标移动速度越慢 
	//int   vx,	鼠标横向的；int   vy	鼠标纵向的

void  MouseSetSpeed(int vx,int vy)
{
	union REGS regs;
	regs.x.ax=0x0f;
	regs.x.cx=vx;
    regs.x.dx=vy;
	int86(51,&regs,&regs);
} 

	//设置鼠标移动范围；
	//int left,int top,int right,int bottom分别为左上右下坐标


void SetMouseRange(int left,int top,int right,int bottom)
{
	 union REGS regs;
	 int retcode,xmin=left,ymin=top,xmax=right,ymax=bottom;
	 /*设定鼠标移动的边界*/
    regs.x.ax=7;
    regs.x.cx=xmin;
    regs.x.dx=xmax;
    int86(51,&regs,&regs);
    regs.x.ax=8;
    regs.x.cx=ymin;
    regs.x.dx=ymax;
    int86(51,&regs,&regs);
}


	//设置鼠标灵敏度；设置鼠标倍速阈值；
	//x为水平灵敏度，y为竖直灵敏度,v为鼠标即将设定的倍速阈值

void SetMouseSen(int x,int y)
{
	union REGS regs;
    regs.x.ax=0x1a;
	regs.x.bx=x;
	regs.x.cx=y;
   // regs.x.dx=v;
	int86(51,&regs,&regs);
}

/*
	读鼠标的位置和按钮状态函数
	mouse_x，mouse_y为鼠标坐标，mouse——butt为鼠标案件状态，1，2,4分别表示按下左中右键
*/
void  ReadMouse( int *mouse_x,int *mouse_y,char *mouse_butt )
{
    union REGS regs;
    int x_new,y_new;
    regs.x.ax=3;
    int86(51,&regs,&regs);
    x_new=regs.x.cx;
    y_new=regs.x.dx;
    *mouse_butt=regs.x.bx&0x07;

	/*-----记录下此时新的坐标---------*/
    *mouse_x=x_new;
    *mouse_y=y_new;
	
	return ;
}


/*	//获取鼠标状态,利用不活动不刷新消除闪烁
	
	/*	int * mouseX		鼠标纵坐标地址
		int * mouseY		鼠标横坐标地址
		int * mButton		鼠标按键状态地址
	

void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt)
{
	int 	Xx0 = *mouse_x;
	int 	Yy0 = *mouse_y;
	int 	but0 =*mouse_butt;
	union REGS regs;
	/*获取鼠标位置
	do
	{
		regs.x.ax=3;
		int86(0x33,&regs,&regs);
		*mouse_x =regs.x.cx;
		*mouse_y=regs.x.dx;
		*mouse_butt =regs.x.bx&1;
	}while ((*mouse_x == Xx0)&&(*mouse_y == Yy0)&&	(*mouse_butt== but0));	//鼠标的显示操作，鼠标区域背景扣取
}*/





void MouseCpy(Coord *CoordXY,short *mouse_buffer)    
{
    int i,j;
    unsigned long pos;
    char OldPage,NewPage;
    short far *VedioBuffer=(short far *)0xA0000000L;
	OldPage=((CoordXY->y)*1600l+(CoordXY->x))/32768;
    NewPage=OldPage;
	SelectPage(NewPage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600l+j+(CoordXY->x);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
                SelectPage(NewPage);
                OldPage=NewPage;
            }
			mouse_buffer[i*16+j]=VedioBuffer[pos%32768];
        }
    }
    return;
}

/*****************************************************************************
	功能说明：鼠标区域背景扣取后重新显示
	参数说明：结构体说明见SVGA.H，
	返回值说明：无返回值
*****************************************************************************/
void MouseReshow(Coord *CoordXY,short *mouse_buffer)
{
    int i,j;
    char OldPage,NewPage;
    unsigned long pos;
    short far *VedioBuffer=(short far *)0xA0000000L;
	OldPage=((CoordXY->y)*1600l+(CoordXY->x))/32768;
    NewPage=OldPage;
	SelectPage(OldPage);
	for(i=0;i<16;i++)
	{
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600l+j+(CoordXY->x);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
				SelectPage(NewPage);
                OldPage=NewPage;
            }
            VedioBuffer[pos%65536]=mouse_buffer[i*16+j];
        }
    }
    return;
}
/**************************************************************************************
	功能说明：鼠标显示
	参数说明：见SVGA。h
	返回值说明：无返回值
**************************************************************************/
void MouseShow(Coord *CoordXY)
{
    int i,j;
    unsigned long pos;
    char OldPage,NewPage;
    short far *VedioBuffer=(short far *)0xA0000000L;
	OldPage=((CoordXY->y)*1600l+(CoordXY->x))/32768;
    NewPage=OldPage;
	SelectPage(OldPage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600l+j+(CoordXY->x);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
                SelectPage(NewPage);
                OldPage=NewPage;
            }
             if(MouseDot[i][j]==1)    /* 画鼠标*/
				VedioBuffer[pos%32768]=0xffff;
			 else if(MouseDot[i][j]==2)
				VedioBuffer[pos%32768]=0;
        }
    }
    delay(15);
    return;
}




//直接调用该函数完成全部初始化
void initmouse(Coord *MS)
{
	MS->x=320,MS->y=240;
	MouseReset();
	SetMousePosition(MS->x,MS->y);
	SetMouseRange(0,0,640,480);
	MouseSetSpeed(2,4);
}
/*
void mouseview()
{	
	while(1)
	{	
		while(!kbhit())
		{
			
			ReadMouse(&mouse->x,&mouse->y,&status);
			MouseCpy(mouse,Fly->mouse_buffer);
			MouseShow(mouse);
			delay(10);
			MouseReshow(mouse,Fly->mouse_buffer);
			ReadMouse(&mouse->x,&mouse->y,&status);
		}

	}
}
//实现鼠标的显示、移动和时间监测(有问题)
*/