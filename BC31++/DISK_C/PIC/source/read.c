#include "head.h"
#pragma pack(1) //结构体的边界对齐为1个字节，节省内存
#define maxnSize (long long)1024*37 //可以存储的最大图片大小 


/*******************************
 读取BMP文件头信息头函数
 传入图片头，图片地址 
 将传入地址的图片信息读入图片头中 
 读入成功返回1
 读入失败返回0 
*******************************/
int readBmp(BMPHeader* head,char *address)
{
    int i=0;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD pColorTable[256];
    FILE* fp;
	fp = fopen(address, "rb");//address
    if(fp == NULL)
    {
        printf("Fail to open image!\n");
        return 0;
    }
    fread(&fileHeader, 1, sizeof(BITMAPFILEHEADER), fp);
    fread(&infoHeader, 1, sizeof(BITMAPINFOHEADER), fp);
    if (fileHeader.bfType != 0X4D42)
    {   /* BM */
        fprintf(stderr, "Not a BMP file !\n");
        return 0;
    }
    if (infoHeader.biBitCount > 8)
    {   /*  不能显示真彩色图像 */
        fprintf(stderr, "Can not display ture color image !\n");
        return 0;
    }
    if (infoHeader.biCompression != 0)
    { /*  不能处理压缩图像 */
        fprintf(stderr, "Not non-compressed image !\n");
        return 0;
    }
    fread(pColorTable,sizeof(RGBQUAD),256,fp);
    head->fileHead=fileHeader;
    head->infoHead=infoHeader;
    for(i=0; i<256; i++)
    {
        head->pColorTable[i].rgbBlue=pColorTable[i].rgbBlue;
        head->pColorTable[i].rgbGreen=pColorTable[i].rgbGreen;
        head->pColorTable[i].rgbRed=pColorTable[i].rgbRed;
        head->pColorTable[i].rgbReserved=pColorTable[i].rgbReserved;
    }
    fclose(fp);
    //printf("biBitCount:%d\n",infoHeader.biBitCount);
	//printf("biWidth:%d\n",infoHeader.biWidth);
	//printf("rgbBlue:%d\n",pColorTable[100].rgbBlue);
	return 1;
}

/*******************************
 读取BMP像素块函数
 传入图片头，图片地址 
 将传入地址的图片像素块读入内存中 
 读入成功返回1
 读入失败返回0 
*******************************/
int readPix(BYTE* temp,int size,char *address)
{
    FILE *fp;
    int off;
    fp=fopen(address,"rb");
    if (fp==0)
    {
        return 0;
    }

    // 计算偏移距离 
    off=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
    fseek(fp,off,SEEK_SET);
    fread(temp,size,1,fp);
    fclose(fp);
    return 1; 
}

/*******************************
 打开判断函数
 传入图片头
 若可以缩放返回1
 若不能缩放返回0 
*******************************/
int openJudge(BMPHeader *head)
{
    int width,height,biBitCount,lineByte; 
    long long bfSize;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;
    fileHead=head->fileHead;
    infoHead=head->infoHead;
    width=infoHead.biWidth;
    height=infoHead.biHeight;
    biBitCount=infoHead.biBitCount;
    lineByte=(width*biBitCount/8+3)/4*4;
     
    bfSize=(long long)height*lineByte+fileHead.bfOffBits; // 计算缩放后大小 
    bfSize=(bfSize+3)/4*4;
    
    if(bfSize>maxnSize)
        return 0;
    else 
        return 1; 
}
