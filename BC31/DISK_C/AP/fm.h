#ifndef _fm_h_
#define _fm_h_
char FreeModeSel(GamePara *para,struct body *a);
int FreeModeSet(GamePara *para,Area *area,char * BodyNum);
void FreeModeInit();
void MaterialsAppear(GamePara *para);
void MaterialsDisappear(GamePara *para);
void BodyLife(struct body *a,int BodyNum);
void DrewFrame();
#endif