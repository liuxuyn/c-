#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<alloc.h>
#include<math.h>
#include"SVGA.h"


/******************************************************************
	功能说明：设置SVGA的模式
	参数说明：Mode序号
	返回值说明：int10中断中的_AH
*************************************************************************/
unsigned char SetSVGAMode(unsigned int vmode) 
{
	union REGS in,out;
    in.x.ax=0x4f02;
    in.x.bx=vmode;
    int86(0x10,&in,&out);
    if(out.h.ah==0x01)
    {
		ReturnMode();
        printf("Set SVGA error!"); /*中断*/
        getch();
        exit(1);
    }
    return(out.h.ah);
}
/************************************************
	功能说明：SVGA显存换页面
	参数说明：index，页面号
	返回值说明：0
*******************************************************/
unsigned int SelectPage(unsigned char index)   
{
	union REGS in,out;
    in.x.ax=0x4f05;
	in.x.bx=0;
    in.x.dx=index;
    int86(0x10,&in,&out); //中断
    return 0;
}
/*******************************************
	功能说明：退出SVGA模式，返回原模式
	参数说明：无参数
	返回值说明：无返回值
**********************************************/
void ReturnMode()        
{
    union REGS in;
    in.h.ah=0;
    in.h.al=(char)0x03;
    int86(0x10,&in,&in);  /*中断*/
    return;
}
/*******************************************************
	功能说明：从硬盘读取BMP直接到显存
	参数说明：x，y：图片左上角坐标，FileName：文件路径
	返回值说明：无返回值
***********************************************************/
char ReadBMP16(int x,int y,char *FileName)
{
    int i,j,k=0;
    FILE *fp;
	char OldPage=0,NewPage=0;
	unsigned int DataOffset;
    long Width,Height;
    unsigned long pos;
    short *buffer;
	short far *VedioBuffer=(short far *)0xA0000000L;
    if((fp=fopen(FileName,"rb"))==NULL)
    {
		ReturnMode();
	printf("Cannot read the picture\n\t\t%s",FileName);
        getch();
        return 0;
    }
	/*Read file size*/
	fseek(fp,10,SEEK_SET);// 其中SEEK_SET,SEEK_CUR和SEEK_END和依次为0,1和2. 简言之: fseek(fp,100L,0);把fp指针移动到离文件开头100字节处; 
	fread(&DataOffset,sizeof(long),1,fp);
    fseek(fp,18,SEEK_SET);
    fread(&Width,sizeof(long),1,fp);
	fread(&Height,sizeof(long),1,fp);
    /*RAM start*/
    buffer=(short *)malloc(Width*sizeof(short));
    if(buffer==NULL)
    {
		ReturnMode();
        printf("SVAGA.c_Malloc error! in function ReadBMP!");
        getch();
        return 0;
	}
	/*Read file*/
    /*Put BITS to VRAM*/
	fseek(fp,DataOffset,SEEK_SET);
	k=(Width*2%4)?(4-Width*2%4):0;
	OldPage=((Height-1+y)*1280l+x)>>15;
	NewPage=OldPage;
    SelectPage(OldPage);   
	for(i=Height-1;i>=0;i--)
    {
		fread(buffer,Width*2+k,1,fp);  //读取一行像素点的信息
        for(j=0;j<Width;j++)     //把读取的一行像素点显示出来
        {
            pos=((i+y)*1280l+j+x);
            NewPage=pos>>15;
			pos &= 0x0000ffffl;

            if(NewPage!=OldPage)/*Change Pages!!!*/
            {
				SelectPage(NewPage);
                OldPage=NewPage;
            }
            VedioBuffer[pos&0x00007fff]=buffer[j];
        }
    }
    /*Close file*/
    fclose(fp);
    free(buffer);
    return 1;
}

/*******************************************************
	功能说明：从硬盘读取BMP直接到显存
	参数说明：x，y：图片左上角坐标，FileName：文件路径, color是不读取出来的色彩
	返回值说明：无返回值
***********************************************************/
char ReadBtn(int x,int y,char *FileName,unsigned int color)
{
    int i,j,k=0;
  
	char OldPage=0,NewPage=0;
	unsigned int DataOffset;
    long Width,Height;
    unsigned long pos;
    short *buffer;
    short far *VedioBuffer=(short far *)0xA0000000L;  FILE *fp;
    if((fp=fopen(FileName,"rb"))==NULL)
    {
		ReturnMode();
        printf("Cannot read the picture in function ReadBtn\n\t\t%s",FileName);
        getch();
        return 0;
    }
	/*Read file size*/
	fseek(fp,10,SEEK_SET);
	fread(&DataOffset,sizeof(long),1,fp);
    fseek(fp,18,SEEK_SET);
    fread(&Width,sizeof(long),1,fp);
	fread(&Height,sizeof(long),1,fp);
    /*RAM start*/
    buffer=(short *)malloc(Width*sizeof(short));
    if(buffer==NULL)
    {
        ReturnMode();
		printf("Malloc error!");
        getch();
        return 0;
	}
	/*Read file*/
    /*Put BITS to VRAM*/
	fseek(fp,DataOffset,SEEK_SET);
	k=(Width*2%4)?(4-Width*2%4):0;
	OldPage=((Height-1+y)*1280l+x)>>15;
	NewPage=OldPage;
    SelectPage(OldPage);   
	for(i=Height-1;i>=0;i--)
    {
		fread(buffer,Width*2+k,1,fp);  //读取一行像素点的信息
        for(j=0;j<Width;j++)     //把读取的一行像素点显示出来
        {
			pos=((i+y)*1280l+j+x);
            NewPage=pos>>15;
            if(NewPage!=OldPage)/*Change Pages!!!*/
            {
				SelectPage(NewPage);
                OldPage=NewPage;
            }
			if(buffer[j]!=color)
			VedioBuffer[pos&0x00007fff]=buffer[j];

        }
    }
    /*Close file*/
    fclose(fp);
    free(buffer);
    return 1;
}

/*********************************************************************
	功能说明：逻辑显存横向像素数量设定
	参数说明：
	返回值说明：
******************************************************************************/
void SetScreenWidth(unsigned pixels)   
{
    static union REGS r;
    r.h.bl=0;
    r.x.ax=0x4f06;
    r.x.cx=pixels;
	int86(0x10,&r,&r);/*中断*/
    return;
}

/*********************************************************************
	功能说明：逻辑显存显示像素起始位置
	参数说明：
	返回值说明：
******************************************************************************/
void SetShowBegin(int x,int y)          
{
    static union REGS r;
    r.x.cx=x;
    r.x.dx=y;
    r.x.ax=0x4f07;
    int86(0x10,&r,&r);/*中断*/
    return;
}

/*测试函数
void main()
{
	SetSVGAMode(0x111);
	SetScreenWidth(1280l);
	ReadBMP16(0,0,"C:\\cccc\\bmp\\1.bmp");
	getch();
}*/
