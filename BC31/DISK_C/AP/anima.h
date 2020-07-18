#ifndef _anima_h_
#define _anima_h_
#define DELAYTIME 200		//延迟时间
void MoveScreen(int way,int next);//参数说明： way=0代表向左滑，way=1代表向右滑
								//next=1；代表转向第一屏幕，next=2，代表转向第二屏幕 
								
void animation();
void animation_new(char* filename, float delaytime,unsigned int Base );
void  movie(char*filename,int time);
void MaterialsAppear(GamePara *para);
void MaterialsDisappear(GamePara *para);
#endif