#ifndef _FUNCTION_H_
#define _FUNCTION_H_ 
#pragma pack(1) 


int readBmp(BMPHeader* head,char *address);//读取BMP文件头
int readPix(BYTE* temp,int size,char *address); //读取BMP像素块
int openJudge(BMPHeader *head); //判断图片大小
int show(BMPHeader* head,char *pBmpBuf); //图片显示函数
int saveBMP(BMPHeader* head,unsigned char *pBmpBuf,char *address); //图片保存函数
int getIndex(RGBQUAD *pColorTable,BYTE r,BYTE g,BYTE b); //索引值查找函数,返回最近的颜色索引
void brightness(BMPHeader *head,unsigned char *pBmpBuf,int level,double *present); //亮度调节函数
void rotation(BMPHeader *head,char *pBmpBuf,int direction); //旋转函数
void mirror(BMPHeader *head,char *pBmpBuf,int direction); //镜像函数

#endif