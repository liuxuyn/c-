#include"stdio.h"
#include"fcntl.h"
#include"bios.h"
#include"dos.h"
#include"stdlib.h"
#include"process.h" /*文件头结构*/ typedef struct tagBIT_MAP_FILE_HEADER
{
int bfType;
long bfSize; //文件大小，以字节为单位
int bfReservedl1; //保留，必须设置为零
int bfReservedl2; //保留，必须设置为零
long bfOffBits; //从文件头开始到实际的图像数据之间的字节偏移量
}BIT_MAP_FIlE_HEADER; /*信息头结构*/ typedef struct tagBIT_MAP_INFO_HEADER
{
long biSize; //信息头大小
long biWidth; //图像宽度
long biHeight; //图像高度
int biPlanes; //必须为1
int biBitCount; //每像素位数，必须是1,4,8或24 
long biCompression; //压缩方法
long biSizeImage; //实际图像大小，必须是4的倍数
long biXPelsPerMeter; //水平方向每米像素数
long biYPelsPerMeter; //垂直方向每米像素数
long biClrUsed; //所用颜色数
long biClrImportant; //重要的颜色数
}BIT_MAP_INFO_HEADER; /*调色板*/ typedef struct tagRGBQUAD
{
char rgbBlue; //蓝色分量
char rgbGreen; //绿色分量
char rgbRed; //红色分量
char rgbReserved;
}RGBQUAD; int COLS=640,ROWS=480; /*换页函数*/ void selectpage(register char page)
{
union REGS r;
r.x.ax=0x4f05;
r.x.bx=0;
r.x.dx=page; //选择页面
int86(0x10,&r,&r);
} /*设置SVGA屏幕格式*/ unsigned char set_SVGA_mode(int vmode)
{
union REGS r;
r.x.ax=0x4f02;
r.x.bx=vmode;
int86(0x10,&r,&r);
return (r.h.ah);
} /*获取当前SVGA屏幕格式*/ unsigned int get_SVGA_mode()
{
union REGS r;
r.x.ax=0x4f03;
int86(0x10,&r,&r);
return (r.x.bx);
} /*设置调色板*/ void set_SVGA_palette(unsigned char r[],unsigned char g[],unsigned char b[])
{
int k;
for(k=0;k<256;k++)
{
outportb(0x03C8,k);
outportb(0x03C9,r[k]>>2);
outportb(0x03C9,g[k]>>2);
outportb(0x03C9,b[k]>>2);
}
} void main()
{
BIT_MAP_FIlE_HEADER FileHeader;
BIT_MAP_INFO_HEADER bmiHeader;
RGBQUAD bmiColors[256];
unsigned char buffer[1024],r[256],g[256],b[256];
unsigned int width,height,linebytes;
long offset,position;
char page_new=0,page_old=0;
int i,j,k,n,savemode;
FILE *fp; if((fp=fopen("e:\\c\\tu\\1.bmp","rb"))==NULL) //判断打开文件是否正确
{
printf("Can't open file!");
return;
}

if(fread((char *)&FileHeader,sizeof(FileHeader),1,fp)!=1)
{
printf("Can't read file header!\n"); //读文件头
return;
} if(FileHeader.bfType!=0X4D42)
{
fprintf(stderr,"Not a BMP file!\n");
return;
}

if(fread((char *)&bmiHeader,sizeof(bmiHeader),1,fp)!=1)
{
fprintf(stderr,"Can't read bmiHeader!\n"); //读信息头
return;
} if(bmiHeader.biBitCount > 8) //不能显示真彩色图像
{
fprintf(stderr,"Can't display ture color image!\n");
return;
} if(bmiHeader.biCompression!=0) //不能处理压缩图像
{
fprintf(stderr,"Not non-compressed image!\n");
return;
} width=(unsigned int)bmiHeader.biWidth;
height=(unsigned int)bmiHeader.biHeight;
linebytes=((width * (long)bmiHeader.biBitCount+31)/32)*4; //每行字节数是4的整数倍 if(fread((char *)&bmiColors[0],4,256,fp)!=256) //读调色板数据
{
fprintf(stderr,"Can't get palette!\n");
return;
}
savemode=get_SVGA_mode(); //先保存原来的屏幕格式
set_SVGA_mode(0x101); //硬件无关性初始化屏幕为256色640*480模式
COLS=640;
ROWS=480;
for(i=0;i<256;i++)
{
r[i]=bmiColors[i].rgbRed;
g[i]=bmiColors[i].rgbGreen;
b[i]=bmiColors[i].rgbBlue;
}
set_SVGA_palette(r,g,b); //设置调色板数据
offset=FileHeader.bfOffBits;
fseek(fp,offset,SEEK_SET); //跳到位图数据的起始位置
for(j=height-1;j>=0;j--)
{
fread(buffer,linebytes,1,fp);
for(i=0,n=0;i<width;i++,n++)
{
position=j*(long)COLS+i; //计算要显示点的显存位置
page_new=position/655361; //计算显示页
if(page_new!=page_old) //当显示也不同时更换页面，提高一定的输出速度
{
selectpage(page_new);
page_old=page_new;
}
pokeb(0xa000,position%655361,buffer[n]); //写到显存位置
}
}
fclose(fp);
bioskey(0);
set_SVGA_mode(savemode); //恢复屏幕
}