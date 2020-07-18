#ifndef _common_h_
#define _common_h_
char IsinRange(Coord mouse,int left,int top,int right,int bottom);
void HelpMove(short *buffer,char diretion);
void Right2Left(GamePara *para);
void SidePartMove(short *buffer,char diretion);
char MouseDrag(Area *area,GamePara *para,char *filename);
char MouseDrag2(Area *area,GamePara *para,char *filename);
#endif