#ifndef _anima_h_
#define _anima_h_
#define DELAYTIME 200		//�ӳ�ʱ��
void MoveScreen(int way,int next);//����˵���� way=0�������󻬣�way=1�������һ�
								//next=1������ת���һ��Ļ��next=2������ת��ڶ���Ļ 
								
void animation();
void animation_new(char* filename, float delaytime,unsigned int Base );
void  movie(char*filename,int time);
void MaterialsAppear(GamePara *para);
void MaterialsDisappear(GamePara *para);
#endif