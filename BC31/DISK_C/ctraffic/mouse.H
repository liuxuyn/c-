#ifndef __mouse_h__
	#define __mouse_h__

/*鼠标信息宏定义*/
#define   WAITING   0xff00
#define   LEFTPRESS   0xff01
#define   LEFTCLICK   0xff10
#define   LEFTDRAG   0xff19
#define   RIGHTPRESS   0xff02
#define   RIGHTCLICK   0xff20
#define   RIGHTDRAG   0xff2a
#define   MIDDLEPRESS   0xff04
#define   MIDDLECLICK   0xff40
#define   MIDDLEDRAG   0xff4c
#define   MOUSEMOVE   0xff08
	
void init_mouse(void);
void hide_mouse(void);
void show_mouse(void);
int  read_mouse(void);

/*检测鼠标是否在按钮上的函数*/
int mouse_onbt(struct BUTTON *bt);

/*检测鼠标是否在窗口上的函数*/
int mouse_onwin(int sx,int sy,int ex,int ey);

/*检测鼠标是否在输入框上*/
int mouse_onbox(struct INPUT_BOX *box);

#endif