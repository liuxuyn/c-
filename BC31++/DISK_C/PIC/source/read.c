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
int readbmp(BMPHeader* head,char *address)
{
    int i=0;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD pColorTable[256];
    FILE* fp;
	fp = fopen("C:/PIC/picture/c.bmp", "rb");//address
    if(fp == NULL)
    {
        printf("Fail to open image!\n");
        return 0;
    }
    fread(&fileHeader, 1, sizeof(BITMAPFILEHEADER), fp);
    fread(&infoHeader, 1, sizeof(BITMAPINFOHEADER), fp);
    fread(pColorTable,sizeof(RGBQUAD),256,fp);
    fileHeader=head->fileHead;
    infoHeader=head->infoHead;
    for(i=0; i<256; i++)
    {
        head->pColorTable[i].rgbBlue=pColorTable[i].rgbBlue;
        head->pColorTable[i].rgbGreen=pColorTable[i].rgbGreen;
        head->pColorTable[i].rgbRed=pColorTable[i].rgbRed;
        head->pColorTable[i].rgbReserved=pColorTable[i].rgbReserved;
    }
    fclose(fp);
    //printf("biBitCount:%d",infoHeader.biBitCount);
    return 1;
}

/*******************************
 读取BMP像素块函数
 传入图片头，图片地址 
 将传入地址的图片像素块读入内存中 
 读入成功返回1
 读入失败返回0 
*******************************/
int readpic(BYTE* p,int size,char *address)
{
    FILE *fp;
    int i;
    unsigned char *pBmpBuf;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;
    RGBQUAD *pColorTable;
    int height,width,lineByte,biCount,jump;
    fp=fopen(address,"rb");
    if (fp==0)
    {
        return 0;
    }
    
    // 计算偏移距离 
    jump=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
    fseek(fp,jump,SEEK_SET);
    fread(p,size,1,fp);
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
    int width,height,biCount,lineByte; 
    long long bfSize;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;
    fileHead=head->fileHead;
    infoHead=head->infoHead;
    width=infoHead.biWidth;
    height=infoHead.biHeight;
    biCount=infoHead.biBitCount;
    lineByte=(width*biCount/8+3)/4*4;
     
    bfSize=(long long)height*lineByte+fileHead.bfOffBits; // 计算缩放后大小 
    bfSize=(bfSize+3)/4*4;
    
    if(bfSize>maxnSize)
        return 0;
    else 
        return 1; 
}
