#ifndef _hanzi_h_
#define _hanzi_h_
void hanzi_s(int x,int y,char *s,int color); /*16���庺�����*/
int ChineseStrlen(char *); /*���㺺�ָ���*/  
void yingwen(char *s,int x,int y,int dx,int dy,short color); /*���Ӣ�ĺ�����*/ 
void hanzi48(int x0,int y0,char *s,int color);
void hz48(int a,int b,int c,int d,char *s1,int color); //���48��С���� 
void hanzi24kaiti(int x0,int y0,char *s,int color);
void hz24kaiti(int a,int b,int c,int d,char *s1,int color);//���24���庺�� 
void hanzi(int x0,int y0,char *s,int color); //����������� 
#endif
