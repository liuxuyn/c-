 /*----------例程 3-16----------*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<dos.h>
#include	<process.h>
#include	<bios.h>
#include    <graphics.h>
#include     <string.h>
#include     "bmp.h"
/*文件头结构*/
typedef struct tagBITMAPFILEHEADER
{
	int	bfType;	/*  通常是 'BM' 。现在来看似乎判断 OS/2 的标识已无什么意义*/
	long	 bfSize;		/*  文件大小，以字节为单位*/
	int	bfReserved1;	/*保留，必须设置为 0*/
	int	bfReserved2;	/*保留，必须设置为 0*/
	long	bfOffBits;	/*从文件头开始到实际的图象数据之间的字节的偏移量。这*/
/*个参数是非常有用的，因为位图信息头和调色板的长度会*/
/*根据不同情况而变化，可以用这个偏移值迅速的从文件中*/
/*读取到位数据。 */
} BITMAPFILEHEADER;

/*信息头结构*/
typedef struct tagBITMAPINFOHEADER
{
	long	biSize;	/* 信息头大小 */
	long	biWidth;	/* 图像宽度 */
	long	biHeight;	/* 图像高度 */
	int	biPlanes;	/*  必须为 1 */
	int	biBitCount;	/*  每像素位数，必须是 1, 4, 8 或 24 */
	long	biCompression;	/*  压缩方法 */
	long	biSizeImage;	/* 实际图像大小，必须是 4 的倍数 */
	long	biXPelsPerMeter;	/*  水平方向每米像素数 */
	long	biYPelsPerMeter;	/*  垂直方向每米像素数*/
	long	biClrUsed;	/*  所用颜色数*/
	long	biClrImportant;	/* 重要的颜色数 */
} BITMAPINFOHEADER;

/*调色板*/
typedef struct tagRGBQUAD
{
	char       rgbBlue;      /*蓝色分量*/
	char       rgbGreen;    /*绿色分量*/
	char       rgbRed;       /*红色分量*/
	char       rgbReserved;
} RGBQUAD;



int COLS=1024, ROWS=768;	/*  缺省为 256 色 640*480 模式 */

/*换页函数*/
void selectpage(register char page)
{
	union REGS r;
	r.x.ax=0x4f05;
	r.x.bx=0;
	r.x.dx=page; /*选择页面*/
	int86(0x10,&r,&r);
}


/*设置 SVGA 屏幕模式*/
/*101H----256 色 640×480 模式*/
/*103H----256 色 800×600 模式*/
/*105H----256 色 1024×768 模式*/
unsigned char set_SVGA_mode(int vmode)
{
	union REGS r;
	r.x.ax=0x4f02;
	r.x.bx=vmode;
	int86(0x10,&r,&r);
	return(r.h.ah);
}


/*获取当前 SVGA 屏幕模式*/
unsigned int get_SVGA_mode(void)
{
	union REGS r;
	r.x.ax=0x4f03;
	int86(0x10,&r,&r);
	return(r.x.bx);
}

/*设置调色板*/
void set_SVGA_palette(unsigned char r[],unsigned char g[], unsigned char b[])
{
	int	k;
	for (k = 0; k < 256; k++)
	{
		outportb(0x03C8,k);
		outportb(0x03C9,r[k]>>2);
		outportb(0x03C9,g[k]>>2);
		outportb(0x03C9,b[k]>>2);
	}
}


void readbmp(char *p)
{

	BITMAPFILEHEADER		FileHeader;
	BITMAPINFOHEADER		 bmiHeader;
	RGBQUAD	bmiColors[256];
	unsigned char  buffer[1024], r[256], g[256], b[256];
	unsigned int	width, height, linebytes;
	long	offset, position;
	char page_new=0,page_old=0;
	int i,j,k,n,savemode; FILE *fp;

	strcpy(buffer,p);

	if((fp=fopen(buffer,"rb"))==NULL) /*判断打开文件是否正确*/
	{
		printf("Can't open file: %s",buffer); return;
	}


	if (fread((char *)&FileHeader, sizeof(FileHeader), 1, fp) != 1)
	{
		printf("Can't read file header !\n"); /*  读文件头 */
		return;
	}
	if (FileHeader.bfType != 0X4D42)
	{	/* BM */
		fprintf(stderr, "Not a BMP file !\n");
		return;
	}








	if (fread((char *)&bmiHeader, sizeof(bmiHeader), 1, fp) != 1)
	{
		 fprintf(stderr, "Can't read bmiHeader !\n");   /*  读信息头 */
		return;
	}
	if (bmiHeader.biBitCount > 8)
	{	/*  不能显示真彩色图像 */
		fprintf(stderr, "Can not display ture color image !\n"); return;
	}
	if (bmiHeader.biCompression != 0)
	{ /*  不能处理压缩图像 */
		fprintf(stderr, "Not non-compressed image !\n");
		return;
	}


	width = (unsigned int)bmiHeader.biWidth;
	height = (unsigned int)bmiHeader.biHeight;
	linebytes = ((width*(long)bmiHeader.biBitCount+31)/32)*4; /*  每行字节数--4 的整数倍 */

	if (fread((char *)&bmiColors[0], 4, 256, fp) != 256)
	{ /*  读调色板数据 */
		fprintf(stderr, "Can't get palette !\n");
		return;
	}


	savemode=get_SVGA_mode(); /*先保存原来的屏幕模式*/
	set_SVGA_mode(0x105); /*硬件无关性初始化屏幕为 256 色 640*480 模式*/
	COLS=1024;ROWS=768;
	for (i = 0; i < 256; i++)
	{
		r[i] = bmiColors[i].rgbRed;
		g[i] = bmiColors[i].rgbGreen;
		b[i] = bmiColors[i].rgbBlue;
	}
	set_SVGA_palette(r, g, b);	/*  设置调色板 */


	offset = FileHeader.bfOffBits;
	fseek(fp, offset, SEEK_SET);	/* 跳到位图数据的起始位置 */
	for(j=height-1;j>=0;j--)
	{
		fread(buffer,linebytes,1,fp);
		for(i=0,n=0;i<width;i++,n++)
		{
			position=j*(long)COLS+i; /*计算要显示点的显存位置*/
			page_new=position/65536l; /*计算显示页*/
			if(page_new!=page_old) /*当显示页不同时更换页面，提高一定的输出速度*/
			{
				selectpage(page_new);
				page_old=page_new;
			}
		pokeb(0xa000,position%65536l,buffer[n]); /*写到显存位置*/
		}
	}
	fclose(fp);
	bioskey(0);
	set_SVGA_mode(savemode); /*恢复屏幕*/
}
int main(int argc, char const *argv[]) {
	read_bmp("C:\\123\\2.bmp");
	getch();
    return 0;
}

