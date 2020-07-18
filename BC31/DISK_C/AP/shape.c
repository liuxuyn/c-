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
#include"game.h"
#include"shape.h"



/*************************************
	功能说明：根据a的类型来显示不同物体
	函数说明�?a第一个物体的结构�?
	返回值说明：无返回�?
****************************/
void ShowShape(struct body*a,GamePara *para)
{
	char str[20];
	switch(a->type)
	{
	
	case PIG:
	if(a->state==1)
	{
		sprintf(str,"body/pig%d1.bmp",para->pig);
		ReadBtn(a->x-a->r,a->y-a->r,str,0x5fe);
		a->state=0;
	}
	else
	{
		sprintf(str,"body/pig%d2.bmp",para->pig);
		ReadBtn(a->x-a->r,a->y-a->r,str,0x5fe);
		a->state=1;
	}
	break;
	
	case BIRD2:
	if(a->vx>=0)
	{
		if(a->state==1)
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird111.bmp",0x5fe);
			a->state=0;
		}
		else
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird112.bmp",0x5fe);
			a->state=1;
		}
	}
	else
	{
		if(a->state==1)
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird121.bmp",0x5fe);
			a->state=0;
		}
		else
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird122.bmp",0x5fe);
			a->state=1;
		}
	}
	break;
	
	case BIRD1:
	if(a->vx>=0)
	{
		if(a->state==1)
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird211.bmp",0x5fe);
			a->state=0;
		}
		else
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird212.bmp",0x5fe);
					a->state=1;
		}
	}
	else
	{
		if(a->state==1)
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird221.bmp",0x5fe);
			a->state=0;
		}
		else
		{
			ReadBtn(a->x-a->r,a->y-a->r,"body/bird222.bmp",0x5fe);
			a->state=1;
		}
	}
	break;
	
	case ICE:
	if(a->HP==2)
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/ice2.bmp",0x5fe);
	}
	else
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/ice2.bmp",0x5fe);
	}
	break;
	
	case STEEL:
	if(a->HP==4)
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/steel4.bmp",0x5fe);
	}
	else if(a->HP==3)
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/steel3.bmp",0x5fe);
	}
	else if(a->HP==2)
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/steel2.bmp",0x5fe);
	}
	else
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/steel1.bmp",0x5fe);
	}
	break;

	case WOOD:
	if(a->HP==3)
	{
	ReadBtn(a->x-a->r,a->y-a->r,"body/wood3.bmp",0x5fe);
	}
	else if(a->HP==2)
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/wood2.bmp",0x5fe);
	}
	else
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/wood1.bmp",0x5fe);
	}
	break;
	case STONE:
	if(a->HP==3)
	{
	ReadBtn(a->x-a->r,a->y-a->r,"body/stone3.bmp",0x5fe);
	}
	else if(a->HP==2)
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/stone2.bmp",0x5fe);
	}
	else
	{
		ReadBtn(a->x-a->r,a->y-a->r,"body/stone1.bmp",0x5fe);
	}
	break;

	}
}


/*************************************
	功能说明：隐藏a物体
	函数说明：a为第一个物�?
	返回值说明：无返回�?
****************************/
void HideShape(struct body*a)
{
	ReadBtn(a->x-a->r,a->y-a->r,"body/2.bmp",0);
}

