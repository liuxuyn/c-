/************************************************
	该文件为一些图形显示、鼠标操作的函数
	首次编辑时间：2013/9/11
	制作人：玉佰强
********************************************************/
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<alloc.h>
#include<math.h>
#include"head.h"
#include"mouse.h"
#include"SVGA.h"


/********************************
	功能说明：本函数在(x,y)点画指定颜色的点
	参数说明：
		int x        目标位置横坐标
		int y        目标位置纵坐标
		int color    指定的颜色
	返回值说明:wu 
********************************/
void  putpixel(int  x,int  y,short color)
{
	long     pos;
	short far *VideoBuffer=(short far *)0xA0000000L;
    register int   NewPage = 0;
    pos = y *1600l+ x;
    NewPage = pos >> 15; //计算显示页
    pos &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
	SelectPage(NewPage);
    VideoBuffer[pos] = color;
}

/********************************
	功能说明：本函数在(x,y)点获取指定颜色的点
	参数说明：
		int x        目标位置横坐标
		int y        目标位置纵坐标
		int color    指定的颜色
	返回值说明:wu 
********************************/
short int  getpixel(int  x,int  y)
{
	long     pos;
	short color;
	short far *VideoBuffer=(short far *)0xA0000000L;
    register int   NewPage = 0;
    pos = y *1600l+ x;
    NewPage = pos >> 15; //计算显示页
    pos &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
	SelectPage(NewPage);
    color=VideoBuffer[pos];
	return color;
}


/********************************
	功能说明：从(x,y)开始从左向右画指定长度水平线
	参数说明：int x        所需画线的左端点横坐标
		int y        所需画线的左端点纵坐标
		int lenth    画线的长度(像素)
		int color    画线的颜色
	返回值说明：无
********************************/
void Xline(int x,int y,int lenth,int color)
{
	int     i;
	long    pos;
	int     NewPage= 0,OldPage=0;
	short far *VedioBuffer=(short far *)0xA0000000L;
	pos= y*1600l + x;
	OldPage= pos>> 15; //计算显示页
	SelectPage(OldPage);
    for ( i = 0; i < lenth; i++)
    {
        pos= y*1600l + x+i;
		NewPage= pos>> 15; //计算显示页
		pos&= 0x0000ffffl;//计算在一个页面上的偏移位置
        if (NewPage!=OldPage) //更换页面
        {
            SelectPage(NewPage);
            OldPage=NewPage;
        }
		VedioBuffer[pos] = color^getpixel(x+i,y);
    }
}


/********************************
	功能说明：从(x,y)开始从上到下垂直线
	参数说明：int x        所需画线的左端点横坐标
			int y        所需画线的左端点纵坐标
			int lenth    画线的长度(像素)
			int color    画线的颜色
	返回值说明：无
********************************/
void Yline(int x,int y,int lenth,int color)
{
	int     i;
	long    pos;
	int     NewPage= 0,OldPage=0;
	short far *VedioBuffer=(short far *)0xA0000000L;
	pos= y*1600l + x;
	OldPage= pos>> 15; //计算显示页
	SelectPage(OldPage);
    for ( i = 0; i < lenth; i++)
    {
        pos= ( y + i ) *1600l + x;
		NewPage= pos>> 15; //计算显示页
		pos&= 0x0000ffffl;//计算在一个页面上的偏移位置
        if (NewPage!=OldPage) //更换页面
        {
            SelectPage(NewPage);
            OldPage=NewPage;
        }
		VedioBuffer[pos] = color^getpixel(x,y+i);
    }
}
/********************************
	功能：从(x1,y1)到(x2,y2)画直线
	参数：
		double x1    目标直线的一个端点的横坐标
		double y1    目标直线的一个端点的纵坐标
		double x2    目标直线的另一个端点的横坐标
		double y2    目标直线的另一个端点的总坐标
		int color    color指定要显示直线的颜色
	返回值说明：
********************************/
void line( double x1, double y1,double x2, double y2,short color )
{
	int     pointX;
	int     pointY;
	int  k;
	 short far *VideoBuffer=(short far *)0xA0000000L;
	double  r,tcos,tsin,DX,DY;
	long pos;
	int      NewPage = 0, OldPage=0;
	pos=(y2*1600l+x2);
	NewPage=OldPage=pos>>15;
	SelectPage(NewPage);
    DX = x1 - x2;
    DY = y1 - y2;
    r = sqrt(DX * DX + DY * DY);
    tcos = DX / r;
	tsin = DY / r;
    for ( k = 0; k <= r; k ++)
    {
        pointX = (int)(x2 + tcos * k);
        pointY = (int)(y2 + tsin * k);
		pos =(long)( pointY * 1600l+ pointX);
		NewPage =pos >>15;
        if (NewPage != OldPage)
        {
            SelectPage(NewPage);
            OldPage= NewPage;
        }
			VideoBuffer[pos] = color^getpixel(pointX,pointY);

    }
}
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
        printf("SVAGA.c_Malloc error! in function ReadBMP!");
        getch();
        return 0;
	}
	/*Read file*/
    /*Put BITS to VRAM*/
	fseek(fp,DataOffset,SEEK_SET);
	k=(Width*2%4)?(4-Width*2%4):0;
	OldPage=((Height-1+y)*1600l+x)>>15;
	NewPage=OldPage;
    SelectPage(OldPage);   
	for(i=Height-1;i>=0;i--)
    {
		fread(buffer,Width*2+k,1,fp);  //读取一行像素点的信息
        for(j=0;j<Width;j++)     //把读取的一行像素点显示出来
        {
            pos=((i+y)*1600l+j+x);
            NewPage=pos>>15;
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
	OldPage=((Height-1+y)*1600l+x)>>15;
	NewPage=OldPage;
    SelectPage(OldPage);   
	for(i=Height-1;i>=0;i--)
    {
		fread(buffer,Width*2+k,1,fp);  //读取一行像素点的信息
        for(j=0;j<Width;j++)     //把读取的一行像素点显示出来
        {
			pos=((i+y)*1600l+j+x);
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

/*********************************************************
	功能说明：动画的背景抠图
	参数说明：前四个参数分别表示左上角和右下角的坐标，buffer表示图片存储地址，para是游戏常用变量
	返回值说明：无返回值
********************************************************/
void BodyBackGroundCpy(int left,int top,int right,int bottom,short *buffer)
{
    int i,j;
    unsigned long pos,Width,Height;
    char OldPage,NewPage;
    short far *VideoBuffer=(short far *)0xA0000000L;
    Width=right-left;
    Height=bottom-top;
    OldPage=(long)(top*1600l+left)/32768;
    NewPage=OldPage;
    SelectPage(NewPage);
    for(i=0;i<Height;i++)
    {
        for(j=0;j<Width;j++)
        {
			pos=(long)((i+top)*1600l+j+left);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
                SelectPage(NewPage);
                OldPage=NewPage;
            }
            buffer[i*Width+j]=VideoBuffer[pos%32768];
        }
    }
    return;
}

/*******************************************************************
	功能说明|；背景重新显示
	参数说明：前四个参数分别表示左上角和右下角的坐标，buffer表示图片存储地址，para是游戏  常用变量
	返回值说明：无返回值
**********************************************************************/
void BodyBackGroundReshow(int left,int top,int right,int bottom,short *buffer)
{
    int i,j;
    unsigned long pos,Width,Height;
    char OldPage,NewPage;
    short far *VideoBuffer=(short far *)0xA0000000L;
    Width=right-left;
    Height=bottom-top;
	OldPage=(top*1600l+left)/32768;
    NewPage=OldPage;
    SelectPage(NewPage);
    for(i=0;i<Height;i++)
    {
        for(j=0;j<Width;j++)
        {
			pos=((i+top)*1600l+j+left);
            NewPage=pos/32768;
			if(OldPage!=NewPage)
            {
				SelectPage(NewPage);
                OldPage=NewPage;
            }
            VideoBuffer[pos%32768]=buffer[i*Width+j];
	}
    }
    return;
}



/********************************
	功能说明：本函数在指定位置画指定文件的指定部分
	参数说明：
		Area area:        相对于图片的区域
		int  x      图片显示在屏幕上位置的左边界坐标
		int  y      图片显示在屏幕上位置的上边界坐标
		char *filename    指定的用于配置调色板的图片
	返回值：无
********************************/
void  ReadPartBMP(struct Area area ,int x, int y,char *filename,GamePara *para,short int color)
{

    register int      i,j,k;
    long     Width;
	long     Height;
    long     partWidth;
    long     partHeight;
	short far *VideoBuffer=(short far *)0xA0000000L;
	short *buffer;
    FILE *fp; 
    
	unsigned long  pos; 
    int  PageOld,PageNew;

    /*打开文件*/
    if ((fp = fopen(filename,"rb")) == NULL)
    {
        printf("Fail to open file in Function ReadPartBMP ");
        fclose(fp);
        return;
    }

    /*获取BMP的宽高信息*/
    fseek(fp,18,SEEK_SET);
    fread(&Width,4,1,fp);
    fread(&Height,4,1,fp);
	if(area.left<0||area.left>Width||area.right>Width||area.top<0||area.top>Height||area.bottom>Height)
	{
		ReturnMode();
		printf("area error in function ReadPartBMP");
	}
	k=(Width%2)?1:0; //修正宽度
	
    partWidth=area.right-area.left;
    partHeight=area.bottom-area.top;
	
	buffer=(short *)malloc((unsigned)abs(partWidth)* 2);
	if(buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function ReadPartBMP");
		getch();
		exit(1);
	}

	PageNew=PageOld= ((long)y*1600l+x)>>15;
	SelectPage(PageNew);
	
    fseek(fp,70 +((long)(Width+k)*(Height-area.bottom)+area.left )* 2, SEEK_SET);
    /*直接写显存*/
    for ( j = partHeight - 1; j >= 0; j--)
    { 
        fread(buffer,partWidth*2,1,fp);
		for ( i = 0; i < partWidth; i++) 
		{ 
			pos= (unsigned long)(y+j)*1600l+i+x; //计算要显示点的显存位置
			PageNew= pos>>15; //计算显示页
			if (PageNew != PageOld) //更换页面
			{
				SelectPage(PageNew);
				PageOld = PageNew;
			}
			if(buffer[i]!=color)
				VideoBuffer[pos&0x0000ffff] = buffer[i]; //写到显存位置
                
       }
       fseek(fp,(Width+k-partWidth)*2l,SEEK_CUR);
    }
    /*关闭文件*/
	fclose(fp);
	free(buffer);
}

/*********************************************************
	鍔熻兘璇存槑锛氬睆骞曟搷浣滐紝鍙樻殫
	鍙傛暟璇存槑锛氭棤鍙傛暟
	杩斿洖鍊艰鏄庯細鏃犺繑鍥炲�?
**************************************************************/
void Dark()                             
{
    int i;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
    char np=0;
	SelectPage(np);
    for(i=0;i<37;i++)
    {
        for(pos=0;pos<32768;pos=pos+2)
        {
            video_buffer[pos]=0;
        }
        np++;
		SelectPage(np);
	}
	return;
}
