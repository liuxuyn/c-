#ifndef _intfa2_h_
#define _intfa2_h_
char IsinRange(Coord mouse,int left,int top,int right,int bottom);

char ButtonA(Button btn,GamePara *para,unsigned short color);				                
char ButtonB(Button btn,GamePara *para);
char SidePart(GamePara *para);
void FuncWin(GamePara *para);
void FuncFailed(GamePara *para);
void ExitBox(GamePara *para);
void HelpBox(GamePara *para);
char SidePartCheck(GamePara *para);
#endif