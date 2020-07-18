#ifndef __drawtool_h__
	
    #define __drawtool_h__





/******VGA初始化******/

void init_VGA(void);



/*******EGA初始化*******/

void init_EGA(void);



/******************汉字及字符输出（已对齐）*********************/

void word_write(int x,int y,unsigned char *word,int color,unsigned char charsize);



/*******画界面通用背景及通用“温馨提示”********/

void draw_bk(void);



/*当鼠标移到按钮上时，画按钮边框的函数*/

void draw_btlight(struct BUTTON *bt,int state);



/*开一个某颜色的窗口*/

void win(int sx,int sy,int ex,int ey,int color);



/*擦去提示内容*/

void msgoff(void);



/*画洋红色线*/

void Mline(int x0,int y0,int x1,int y1);



/*画半径为2个像素的实心黑点*/

void pot(int x,int y);



/*界面名显示函数*/

void show_winname(char *winname,int n);



/*通用按钮名字及边框*/

void draw_bt(struct BUTTON *bt,int color,int charsize);  
 


/***********高亮按钮***********/

void hlight_bt(struct BUTTON *bt);



/*在十字车辆初始化界面画路面的函数*/

void draw_roadin_s(int x0,int y0,int len,int wid,int rwid);



/*画丁字车辆初始化界面时的路面函数*/

void draw_roadin_d(int x0,int y0,int len,int wid,int rwid);



/*画指北针*/

void draw_eswn(int x,int y);



/*画输入框的函数*/

void draw_box(struct INPUT_BOX *box,int color);



/**画十字仿真界面的路面函数***/

void draw_road_s(void);



/*画丁字路面的函数（交通仿真运行模块的工具函数）*/

void draw_road_d(void);		   

/*赋给左上角点

画仿真界面四周绿地
*/
void draw_gg_s(int *count,struct TM *tm,int *g);



/*画丁字仿真界面四周绿地
*/
void draw_gg_d(int *count,struct TM *tm,int *g);



/*画交通灯的函数*/

void draw_lamp_s(struct LAMP * pl);



/*画丁字交通灯的函数*/

void draw_lamp_d(struct LAMP * pl);



/**********画车的函数************/

void draw_car(struct CAR * p);



/***********画界面通用背景***********/

void draw_winbk(void);



/*****画仿真界面下播放/暂停按钮****/

void draw_play(int x,int y,int state);



/*********画仿真界面下重播按钮***********/

void draw_replay(int x,int y,int state);



/*********画仿真界面下分析按钮************/

void draw_fenxi(void);



#endif