#ifndef _mouse_h_
#define _mouse_h_
int mouse_press(int x1, int y1, int x2, int y2); //�ж��Ƿ��ڿ��ڵ��  ���ڵ������1   ���ڲ��������2   �����Ҽ��������3   �������������4  ��������0 
void mouse(int,int);   //����꺯�� 
void mouseinit(void);  //����ʼ�� 
void mou_pos(int*,int*,int*);  //�������λ��
void mou_pos_state(int *nx,int *ny,int*nbuttons);//����λ�û�ͼ   ���ظ�λ��
void mread(int *,int *,int*);  //������λ�� 
void mread_state(int *nx,int *ny,int*nbuttons);//���������  ���ظ�λ��
void save_bk_mou(int x,int y); //����걳�� 
void clrmous(int x,int y);     //������ 
void drawmous(int x,int y);    //����Ļ�ϻ������ 
int GetMouseStatus(int *button);   //��ȡ��갴����״̬ 

extern int MouseX;
extern int MouseY;
extern int press;
extern union REGS regs;
#endif
