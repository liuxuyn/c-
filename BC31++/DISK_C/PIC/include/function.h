#ifndef _FUNCTION_H_
#define _FUNCTION_H_ 
#pragma pack(1) 


int readBMP(BMPHeader* head,char *address);//读取BMP文件头
int readpic(BYTE* p,int size,char *address); //读取BMP像素块
int openJudge(BMPHeader *head); //判断图片大小

#endif