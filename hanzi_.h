#ifndef _hanzi_h_
#define _hanzi_h_
void hanzi_s(int x,int y,char *s,int color); /*16宋体汉字输出*/
int ChineseStrlen(char *); /*计算汉字个数*/  
void yingwen(char *s,int x,int y,int dx,int dy,short color); /*输出英文和数字*/ 
void hanzi48(int x0,int y0,char *s,int color);
void hz48(int a,int b,int c,int d,char *s1,int color); //输出48大小汉字 
void hanzi24kaiti(int x0,int y0,char *s,int color);
void hz24kaiti(int a,int b,int c,int d,char *s1,int color);//输出24楷体汉字 
void hanzi(int x0,int y0,char *s,int color); //单个汉字输出 
#endif
