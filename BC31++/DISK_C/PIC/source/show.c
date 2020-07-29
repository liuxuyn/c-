#include"head.h"
#pragma pack(1)
#define midx 400 //横轴中点 
#define midy 300 //纵轴中点 

int show(BMPHeader* head,char *pBmpBuf)
{
	int i,j;
	char oldPage=0,newPage=0;
	int height,width,lineByte,biCount;
	BITMAPINFOHEADER infoHead;
	unsigned long pos;
	int x,y;
	short *buffer;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4;
	
	x=midx-(width>>1);
	y=midy-(height>>1);
	
}