#ifndef _SVGA_h_
#define _SVGA_h_

/*********读操作********/
char ReadBMP16(int x,int y,char *FileName);

/****************模式设置*******************/
void ReturnMode();
unsigned char SetSVGAMode(unsigned int );
unsigned int SelectPage(unsigned char );
void SetScreenWidth(unsigned );
void SetShowBegin(int x,int y);

#endif