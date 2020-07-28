#include <stdio.h>
#include <malloc.h>
#include "bmp.h"
#pragma pack(1) //结构体的边界对齐为1个字节，节省内存
#define midx 400 //横轴中点 
#define midy 300 //纵轴中点 

/*******************************
 读取BMP文件头信息头函数
 传入图片头，图片地址 
 将传入地址的图片信息读入图片头中 
 读入成功返回1
 读入失败返回0 
*******************************/
int main()
{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD pColorTable[256];
    FILE* fp;
	fp = fopen("C:/PIC/picture/c.bmp", "rb");
    if(fp == NULL)
    {
        printf("Fail to open image!\n");
        return 0;
    }
    fread(&fileHeader, 1, sizeof(BITMAPFILEHEADER), fp);
    fread(&infoHeader, 1, sizeof(BITMAPINFOHEADER), fp);
    fread(pColorTable,sizeof(RGBQUAD),256,fp);
    fclose(fp);
    //printf("biBitCount:%d",infoHeader.biBitCount);
    return 1;
}