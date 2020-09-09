#include"head.h"
#pragma pack(1)
#define midx 400 //横轴中点 
#define midy 300 //纵轴中点 

/*******************************
 图片显示函数
 传入图片头，像素块
 在图框中心显示图片 
*******************************/
int show(BMPHeader* head,char *pBmpBuf)
{
	int i,j;
	char oldPage=0,newPage=0;
	int height,width,lineByte,biBitCount;
	BITMAPINFOHEADER infoHead;
	unsigned long pos;
	int x,y;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biBitCount=infoHead.biBitCount; 
	lineByte=(width*biBitCount/8+3)/4*4;
	
	x=midx-(width>>1);
	y=midy-(height>>1);

	// 显存的逻辑宽度为1600 
	oldPage=((height-1+y)*1600l+x)>>15; 
    newPage=oldPage;
    Select_Page(oldPage);
    
    for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
		{
			pos=(i+y)*(long)800+(j+x); //偏移量
			newPage=pos/65536; // 计算页数 
			if(newPage!=oldPage)  // SVGA显示换页
			{
				Select_Page(newPage);
				oldPage=newPage;
			}
			// 写入显存 
			// 容量为65535故要取模 
			pokeb(0xa000,pos%65536,*(pBmpBuf+(height-i-1)*lineByte+j));
		}
	}
	return 0;
}