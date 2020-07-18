#ifndef _intfa_h_
#define _intfa_h_

char GameInit(GamePara *para);

char Interface2Check(GamePara *para);
char Interface2Init(GamePara *para);

char InterfaceAboutInit(GamePara *para);  //关于界面初始化
char InterfaceAbout(GamePara *para);

char InterfaceHighInit(GamePara *para);
char InterfaceHigh(GamePara *para);

char InterfaceModSel(GamePara *para);
char InterfaceModSelInit(GamePara *para);

char InterfaceLevSelInit(GamePara *para);
char InterfaceLevSel(GamePara *para);

char PlayCheck(char *,GamePara *);
char Sound1Check(char *SoundAbout,GamePara *para);
#endif