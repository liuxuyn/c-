#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<graphics.h>
#include<dos.h>
/*鼠标信息宏定义*/
#define WAITING 0xff00
#define LEFTPRESS 0xff01
#define LEFTCLICK 0xff10
#define LEFTDRAG 0xff19
#define RIGHTPRESS 0xff02
#define RIGHTCLICK 0xff20
#define RIGHTDRAG 0xff2a
#define MIDDLEPRESS 0xff04
#define MIDDLECLICK 0xff40
#define MIDDLEDRAG 0xff4c
#define MOUSEMOVE 0xff08

int hide[16][16], bury[16][16],mousedraw[16][16],pixelsave[16][16];/*分别定义隐码、掩码、点值*/
int mousebutton,mouseexist,mouseX,mouseY;
void mousepicture() /*画心形，可设置其它的图形*/
{
   int i,j,k;
   long hidenum[16]={
   0xe3c7,0xc183,0x8001,0x0000,
   0x0000,0x0000,0x0000,0x8001,
   0x8001,0xc003,0xe007,0xf00f,
   0xf81f,0xfc3f,0xfe7f,0xffff,
} ; /*隐码点值，是对点素进行设置*/
long burynum[16]={ 
0x1c38,0x3e7c,0x7ffe,0xffff,
0xffff,0xffff,0xffff,0x7ffe,
0x3ffe,0x3ffc,0x1ff8,0x0ff0,
0x07e0,0x03c0,0x0180,0x0000,
};/*掩码点值*/
for(i=0;i<16;i++)
{ 
   while(hidenum[i]!=0) 
   { 
     for(j=15;j>=0;j--) 
     { 
        hide[i][j]=hidenum[i]%2; 
        hidenum[i]/=2; 
     } /*把隐码转化为0-1*/ 
   } 
   while(burynum[i]!=0) 
   { 
     for(k=15;k>=0;k--) 
     { 
        bury[i][j]=burynum[i]%2; 
        burynum[i]/=2; 
     } 
   } 
   for(k=0;k<16;k++) 
   { 
     if(hide[i][k]==0&&bury[i][k]==0)
       mousedraw[i][k]=1; 
     else if(hide[i][k]==0&&bury[i][k]==1)
       mousedraw[i][k]=2; 
     else if(hide[i][k]==1&&bury[i][k]==0)
       mousedraw[i][k]=3; 
     else
       mousedraw[i][k]=4; /*期间实行逻辑与和异或*/ 
    } 
} 
}

void mouseon(int x,int y) /*显示鼠标*/
{
int i,j;
for(i=0;i<16;i++)
{
for(j=0;j<16;j++)
{
pixelsave[i][j]=getpixel(x+j,y+i);/*取得指定像素的颜色*/
if(mousedraw[i][j]==1)
putpixel(x+j,y+i,6);
if(mousedraw[i][j]==2) /*1、2采用点的逻辑运算判断进行着色*/
putpixel(x+j,y+i,6);
}
}
}

void mouseoff() /*消失鼠标 */
{ 
int i,j,x,y,color;
x=mouseX;
y=mouseY;
for(i=0;i<16;i++)
{
for(j=0;j<16;j++)
{
if((mousedraw[i][j]==3)||(mousedraw[i][j]==4)) /*3、4采用点的逻辑运算判断可否继续运行*/
continue;
putpixel(x+j,y+i,BLACK); /*使其鼠标移动前的位置变为黑色*/
putpixel(x+j,y+i,pixelsave[i][j]);/*使其恢复指定像素的颜色*/
}
}
}

/*鼠标是否加载
MouseExist:1=加载
0=未加载
MouseButton:鼠标按键数目 */
void mouseload()
{
_AX=0x00;
geninterrupt(0x33);
mouseexist=_AX;
mousebutton=_BX;
}

/*鼠标状态值初始化*/
void mousereset()
{
_AX=0x00;
geninterrupt(0x33);/*0x33是DOS中断,是在DOS下通过调用中断来对鼠标进行操作.*/
}

/*改变鼠标光标形状
SHAPE sp:为以上定义的形状
void MouseShape(SHAPE sp)
{
_BX=sp.hotx;
_CX=sp.hoty;
_ES=FP_SEG(&sp.shape);
_DX=FP_OFF(&sp.shape);
_AX=0x09;
geninterrupt(0x33);
}*/

/*设置鼠标左右边界
lx:左边界
gx:右边界 */
void mousesetX(int lx,int rx)
{
_CX=lx;
_DX=rx;
_AX=0x07;
geninterrupt(0x33);
}

/*设置鼠标上下边界
uy:上边界
dy:下边界 */
void mousesetY(int uy,int dy)
{
_CX=uy;
_DX=dy;
_AX=0x08;
geninterrupt(0x33);
}

/*设置鼠标当前位置
x:横向坐标
y:纵向坐标 */
void mousesetXY(int x,int y)
{
_CX=x;
_DX=y;
_AX=0x04;
geninterrupt(0x33);
}

/*设置鼠标速度(缺省值:vx=8,vy=1)
值越大速度越慢 */
void mousespeed(int vx,int vy)
{
_CX=vx;
_DX=vy;
_AX=0x0f;
geninterrupt(0x33);
}

/*获取鼠标按下键的信息*/
/*是否按下左键
返回值: 1=按下 0=释放*/
int leftpress()
{
_AX=0x03;
geninterrupt(0x33);
return(_BX&1);
}

/*是否按下中键
返回值同上 */
int middlepress()
{
_AX=0x03;
geninterrupt(0x33);
return(_BX&4);
}

/*是否按下右键
返回值同上 */
int rightpress()
{
_AX=0x03;
geninterrupt(0x33);
return(_BX&2);
}

/*获取鼠标当前位置*/
void mousegetXY()
{
_AX=0x03;
geninterrupt(0x33);
mouseX=_CX;
mouseY=_DX;
}
int mousemove()/*鼠标移动;*/
{
int i,j,x,y,color,move,press=0;
x=mouseX;
y=mouseY;
move=0; /*没移动标志*/
if(mouseX!=x||mouseY!=y)
{
move=1;/*判断是否有移动*/
mouseon(mouseX,mouseY);
}
return 1;
}