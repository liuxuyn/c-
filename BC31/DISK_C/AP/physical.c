
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<time.h>
#include<bios.h>
#include<stdlib.h>
#include"head.h"
#include"SVGA.H"
#include"mouse.h"
#include"intfa.h"
#include"intfa2.h"
#include"PHYSICAL.h"


/*************************************
	功能说明：判断两个物体相撞时是物体对物体的伤�?
	函数说明：两个物体的地址
	返回值说明：0为假
****************************/
int IsDestroy(struct body *a,struct body *b)
{
	// char str[30];
	double v=a->vx*a->vx+a->vy*a->vy+b->vx*b->vx+b->vy*b->vy;
	// sprintf(str,"IsDestroy:%lf\n",v);
	// DeBug(str);
	if(v>360)
	{
		a->HP-=4;
	}
	else if(v>240)
	{
		a->HP-=3;
	}
	if(v>120)
	{
		a->HP-=2;
	}
	else if(v>60)
	{
		a->HP-=1;
	}
	if(a->HP<=0)
	{
	// / /	sprintf(str,"HP:%d\n",a->HP);
	// /	DeBug(str);
		return 1;
	}
	else
	{
	 //	sprintf(str,"HP:%d\n",a->HP);
	 //	DeBug(str);
		return 0;
	}
}




/*************************************
	功能说明：销毁某个物�?
	函数说明：传入地址
	返回值说明：无返回�?
****************************/
void destroy(struct body *a)
{
	int i;

	a->flag=0;
	HideShape(a);
	ReadBtn(a->x,a->y,"body/pow.bmp",0x35f);
	delay(20);	
	ReadBtn(a->x,a->y,"body/2.bmp",0x5fe);
	ReadBtn(a->x,a->y,"body/pow11.bmp",0x5fe);
	delay(20);
	ReadBtn(a->x,a->y,"body/2.bmp",0x5fe);
	ReadBtn(a->x,a->y,"body/pow12.bmp",0x5fe);
	delay(20);
	ReadBtn(a->x,a->y,"body/2.bmp",0x5fe);
	ReadBtn(a->x,a->y,"body/pow13.bmp",0x5fe);
}


/*************************************
	功能说明：反弹碰撞的物体
	函数说明�?a第一个物体的结构体，*b第二个物体的结构�?
	返回值说明：无返回�?
****************************/
void shock(struct body *a,struct body *b)
{
	float A,B,C,D,E,F,GG,H;
	//ReadBtn(a->x/2+b->x/2,a->y/2+b->y/2,"body/pow.bmp",0x5fe,&para);
		A = (a->x - b->x)*(a->x - b->x) ,
			B = (a->y - b->y)*(a->y - b->y) ,
			C = A+B,
			D = a->vx - b->vx,
			E = a->vy - b->vy,
			F = (a->x - b->x)*(a->y - b->y),
			GG = (A*D + E*F)/C,
			H = (B*E + D*F)/C;
	a->vx -= GG*0.9;
	a->vy -=H*0.9;
	b->vx+=GG*0.9;
	b->vy+=H*0.9;
	a->move=1;
	b->move=1;
	if(a->vx*a->vx+a->vy*a->vy<0.025)
	a->ac=0;
	if(b->vx*b->vx+b->vy*b->vy<0.025)
	b->ac=0;
 
}


/*************************************
	功能说明：计算是否碰�?
	函数说明�?
	返回值说明：0为假
****************************/
int Isshock(struct body *a,struct body *b)
{
	//char str[20];
	float d2=(a->x-b->x)*(a->x-b->x)+(a->y-b->y)*(a->y-b->y);
	
	return d2<=(a->r+b->r)*(a->r+b->r)*1.1;
}
/*************************************
	功能说明：移动某个物�?
	函数说明�?a第一个物体的结构�?
	返回值说明：无返回�?
****************************/
void move(struct body *a,GamePara *para)
{
	HideShape(a);
	a->vy+=G*0.1;
	a->x+=a->vx;
	a->y+=a->vy;
	a->vx*=0.999;
	a->vy*=0.999;
	if(a->vx*a->vx+a->vy*a->vy<0.005&&a->ac==0)
	a->move=0;
	if(a->y>=520-a->r)
	{
		a->vx*=0.5;
		if(a->vx<0.1&&a->vy<0.1)
		a->move=0;
	}
	ShowShape(a,para);
	//delay(4);
}
/*************************************
	功能说明：反弹碰撞的物体
	函数说明�?a第一个物体的结构�?
	返回值说明：无返回�?
****************************/
void CollideEdge(struct body* a,GamePara *para)
{
	if(a->y+a->r>520)
	{
		reset(a,a->x,520-a->r,para);
		a->vy=-a->vy*0.7;
	}
	if(a->x+a->r>SCREENX)
	{
		reset(a,SCREENX-a->r,a->y,para);
		a->vx=-a->vx*0.7;
	}
	if(a->x-a->r<0)
	{
		reset(a,a->r,a->y,para);
		a->vx=-a->vx*0.7;
	}
	if(a->y-a->r<0)
	{
		reset(a,a->x,a->r,para);
		a->vy=-a->vy*0.7;
	}

}
