/********************************************************
*             *本文件为读取bmp图片                      *
*             *作者：李鑫                               *
*             *最终修改时间：2011.11.4                  *
*********************************************************/

#include <dos.h>
#include <stdio.h>
#include <process.h>
#include <bios.h>
#include <conio.h>
#include <bios.h>
#include "readbmp.h"

void selectpage(register char page) /*换页函数*/
{
	union REGS r;
	r.x.ax=0x4f05;
	r.x.bx=0;
	r.x.dx=page; /*选择页面*/
	int86(0x10,&r,&r);
}

unsigned char set_SVGA_mode(int vmode) /*设置SVGA屏幕模式*/
{
	union REGS r;
	r.x.ax=0x4f02;
	r.x.bx=vmode;
	int86(0x10,&r,&r);
	return(r.h.ah);
}

unsigned int get_SVGA_mode() /*获取当前SVGA屏幕模式*/
{
	union REGS r;
	r.x.ax=0x4f03;
	int86(0x10,&r,&r);
	return(r.x.bx);
}

void readbmp(char *p)
{
	char buffer[640],page_new=0,page_old=0;
	int i,j,k,n,r,g,b,savemode;
	long position,width,length;
	FILE *fp;
	strcpy(buffer,p);

	if((fp=fopen(buffer,"rb"))==NULL)
	{
		printf("Can't open file: %s",buffer);
		return;
	}

	fseek(fp,28,SEEK_SET);
	fread(&i,2,1,fp);

	if(i!=8) /*检查是否为256色位图*/
	{
		puts("Not a 256 color bitmap!");
		fclose(fp);exit(0);
	}

	fseek(fp,18,SEEK_SET);
	fread(&width,4,1,fp);
	fread(&length,4,1,fp);

	savemode=get_SVGA_mode(); /*先保存原来的屏幕模式*/
	set_SVGA_mode(0x101); /*硬件无关性初始化屏幕为640*480 256色模式*/
	fseek(fp,54,SEEK_SET);

	for(i=0;i<256;i++) /*按照该图片的DAC色表设置色彩寄存器*/
	{
		b=fgetc(fp);g=fgetc(fp);r=fgetc(fp); /*获取R、G、B分量*/
		outportb(968u,i);
		outportb(969u,r>>2);
		outportb(969u,g>>2);
		outportb(969u,b>>2);
		fgetc(fp);
	}
	k=(width%4)?(4-width%4):0; /*宽度修正值*/

	for(j=length-1;j>=0;j--)
	{
		fread(buffer,width,1,fp);
		for(i=0,n=0;i<width;i++,n++)
		{
			position=j*640l+i; /*计算要显示点的显存位置*/
			page_new=position/65536L; /*计算显示页*/

			if(page_new!=page_old) /*当显示页不同时更换页面。*/
			{
				selectpage(page_new);
				page_old=page_new;
			}

			pokeb(0xa000,position%65536l,buffer[n]); /*写到显存位置*/
		}

		fseek(fp,k,SEEK_CUR); /*每行绘制完后修正宽度*/
	}
	fclose(fp);

	i=100;
	while(i)
	{
		if(bioskey(1))
		{
			getch();
			return;
		}
		delay(40);
		i--;
	}

	set_SVGA_mode(savemode); /*恢复屏幕*/
}

