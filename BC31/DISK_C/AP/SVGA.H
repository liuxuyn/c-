#ifndef _SVGA_h_
#define _SVGA_h_

/*********读操作********/
void  putpixel(int  x,int  y,short color);
void Yline(int x,int y,int lenth,int color);
void Xline(int x,int y,int lenth,int color);
void line( double x1, double y1,double x2, double y2,short color );
char ReadBMP16(int x,int y,char *FileName);
char ReadBtn(int x,int y,char *FileName,unsigned int color) ;
void  ReadPartBMP(struct Area area ,int x, int y,char *filename,GamePara *para,short int);

/****************模式设置*******************/
void ReturnMode();
unsigned char SetSVGAMode(unsigned int );
unsigned int SelectPage(unsigned char );
void SetScreenWidth(unsigned );
void SetShowBegin(int x,int y);


/*屏幕操作*/
void BodyBackGroundCpy(int left,int top,int right,int bottom,short *buffer);
void BodyBackGroundReshow(int left,int top,int right,int bottom,short *buffer) ;

void Dark();
#endif
