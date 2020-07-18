#include<stdio.h>
#include<alloc.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include"head.h"
#include"game.h"
#include"mouse.h"
#include"SVGA.h"
/**************************************************************************
	功能说明：判断是否在某一范围
	参数说明：mouse是鼠标位置，left/top/right/bottom为左上右下的坐标
	返回值说明：在范围之内返回值，否则返回0
**************************************************************************/
char IsinRange(Coord mouse,int left,int top,int right,int bottom)
{
	return (mouse.x>left&&mouse.x<right&&mouse.y>top&&mouse.y<bottom);
}

/******************************************************************************
	功能说明：此函数用于当横坐标像素扫描长度为1600时，
			用于将左边（0，0，250，600）的区域复制到右边（800，0，1050，600）中
	参数说明：diretion=1表示从左移到右，=0表示从右移到左
	返回值说明：
**********************************************************************************/
void HelpMove(short *buffer,char diretion)
{
	char i,j;
	diretion&=1;
	buffer=(short *)malloc(5000);
	if(buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function SidePartMove");
		getch();
		exit(1);
	}
	for(i=12;i>=4;i--)
	{
		for(j=4;j<9;j++)
		{			
			BodyBackGroundCpy(800*(1-diretion)+i*50,j*50,800*(1-diretion)+50+i*50,50+j*50,buffer);
			BodyBackGroundReshow(800*diretion+i*50,j*50,800*diretion+50+i*50,50+j*50,buffer);
		}
	}
	free(buffer);
}


/******************************************************************************
	功能说明：此函数用于当横坐标像素扫描长度为1600时，
			用于将左边（0，0，800，600）的区域复制到右边（800，0，1600，600）中
	参数说明：
	返回值说明：
**********************************************************************************/
void Right2Left(GamePara *para)
{
	char i,j;
	para->buffer=(short *)malloc(50*70*sizeof(short));
	if(para->buffer==NULL)
	{
		ReturnMode();
		printf("malloc error");
	}
	for(i=0;i<16;i++)
	{
		for(j=0;j<12;j++)
		{			
			BodyBackGroundCpy(800+i*50,j*50,850+i*50,50+j*50,para->buffer);
			BodyBackGroundReshow(i*50,j*50,50+i*50,50+j*50,para->buffer);
		}
	}
	free(para->buffer);
}

/******************************************************************************
	功能说明：此函数用于当横坐标像素扫描长度为1600时，
			用于将左边（0，0，250，600）的区域复制到右边（800，0，1050，600）中
	参数说明：diretion=1表示从左移到右，=0表示从右移到左
	返回值说明：
**********************************************************************************/
void SidePartMove(short *buffer,char diretion)
{
	char i,j;
	diretion&=1;
	buffer=(short *)malloc(5000);
	if(buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function SidePartMove");
		getch();
		exit(1);
	}
	for(i=4;i>=0;i--)
	{
		for(j=0;j<12;j++)
		{			
			BodyBackGroundCpy(800*(1-diretion)+i*50,j*50,800*(1-diretion)+50+i*50,50+j*50,buffer);
			BodyBackGroundReshow(800*diretion+i*50,j*50,800*diretion+50+i*50,50+j*50,buffer);
		}
	}
	free(buffer);
}

/****************************************
	功能说明：鼠标拖动，主要用于拖动猪发射的
	参数说明：
		Area *area：需要拖动物体的位置范围
		GamePara * para ：游戏常用变量
		int *distance 返回拖动距离
		char *filename 拖动的物体的文件位置
	返回值说明：
*******************************************/
char MouseDrag(Area *area,GamePara *para,char *filename)
{
		Coord mouse;
		char mousea=0;
		int dx,dy;
		ReadMouse(&mouse.x,&mouse.y,&mousea);
		if(mousea==1&&IsinRange(mouse,area->left,area->top,area->right,area->bottom))
		{
			SetMouseRange(area->left-100,area->top-60,area->right+50,area->bottom+80);
			SetMousePosition(mouse.x,mouse.y);
			dx=mouse.x-area->left;//记录被拖动物体与鼠标的位置差
			dy=mouse.y-area->top;
			ReadBMP16(PIGX-25,PIGY-25,"body\\2.bmp");
			//BodyBackGroundReshow(area->left,area->top,area->right,area->bottom,para->buffer);            
			while(mousea==1)
			{
				ReadMouse(&mouse.x,&mouse.y,&mousea);
				BodyBackGroundCpy(mouse.x-dx,mouse.y-dy,mouse.x-dx+area->right-area->left,mouse.y-dy+area->bottom-area->top,para->buffer);
			//	line(mouse.x-dx+25,mouse.y-dy+25,PIGX-25,PIGY-25,0xffff);
				ReadBtn(mouse.x-dx,mouse.y-dy,filename,0);
				delay(100);
				BodyBackGroundReshow(mouse.x-dx,mouse.y-dy,mouse.x-dx+area->right-area->left,mouse.y-dy+area->bottom-area->top,para->buffer);
				
			}
			area->left=mouse.x-dx; //更新物理位置
			area->top=mouse.y-dy;
			area->right=area->left+50;
			area->bottom=area->top+50;
			BodyBackGroundCpy(area->left,area->top,area->right,area->bottom,para->buffer);
			//ReadBtn(area->left,area->top,filename,0);
			SetMouseRange(0,0,800,600);			
			return 1;
		}
		else
		{
			MouseCpy(&mouse,para->mouse_buffer);
			MouseShow(&mouse);
			delay(10);
			MouseReshow(&mouse,para->mouse_buffer);
		}
		return 0;
}
/****************************************
	功能说明：鼠标拖动，自由模式的自定义
	参数说明：
		Area *area：需要拖动物体的位置范围
		GamePara * para ：游戏常用变量
		int *distance 返回拖动距离
		char *filename 拖动的物体的文件位置
	返回值说明：
*******************************************/
char MouseDrag2(Area *area,GamePara *para,char *filename)
{
		Coord mouse;
		char mousea=0;
		int dx,dy;
		ReadMouse(&mouse.x,&mouse.y,&mousea);
		if(mousea==1&&IsinRange(mouse,area->left,area->top,area->right,area->bottom))
		{
			dx=mouse.x-area->left;//记录被拖动物体与鼠标的位置差
			dy=mouse.y-area->top;
			while(mousea==1)
			{
				ReadMouse(&mouse.x,&mouse.y,&mousea);
				BodyBackGroundCpy(mouse.x-dx,mouse.y-dy,mouse.x-dx+area->right-area->left,mouse.y-dy+area->bottom-area->top,para->buffer);
				ReadBtn(mouse.x-dx,mouse.y-dy,filename,0x0d1d);
				delay(50);
				BodyBackGroundReshow(mouse.x-dx,mouse.y-dy,mouse.x-dx+area->right-area->left,mouse.y-dy+area->bottom-area->top,para->buffer);
			}
			area->left=mouse.x-dx; //更新物理位置
			area->top=mouse.y-dy;
			area->right=area->left+50;
			area->bottom=area->top+50;
			BodyBackGroundCpy(area->left,area->top,area->right,area->bottom,para->buffer);
			ReadBtn(area->left,area->top,filename,0x0d1d);	
			return 1; 			
		}
		else
		{
			MouseCpy(&mouse,para->mouse_buffer);
			MouseShow(&mouse);
			delay(10);
			MouseReshow(&mouse,para->mouse_buffer);
		}
		return 0;
}