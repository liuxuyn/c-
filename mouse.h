#ifndef _mouse_h_
#define _mouse_h_
int mouse_press(int x1, int y1, int x2, int y2); //判断是否在框内点击  框内点击返回1   框内不点击返回2   框内右键点击返回3   框外点击点击返回4  其他返回0 
void mouse(int,int);   //画鼠标函数 
void mouseinit(void);  //鼠标初始化 
void mou_pos(int*,int*,int*);  //更改鼠标位置
void mou_pos_state(int *nx,int *ny,int*nbuttons);//鼠标改位置画图   不必改位置
void mread(int *,int *,int*);  //读坐标位置 
void mread_state(int *nx,int *ny,int*nbuttons);//读鼠标坐标  不必改位置
void save_bk_mou(int x,int y); //存鼠标背景 
void clrmous(int x,int y);     //清除鼠标 
void drawmous(int x,int y);    //在屏幕上画出鼠标 
int GetMouseStatus(int *button);   //获取鼠标按键的状态 

extern int MouseX;
extern int MouseY;
extern int press;
extern union REGS regs;
#endif
