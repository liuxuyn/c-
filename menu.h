#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "common.h"
#include "draw.h"
typedef struct menu
{
    int local[4];
    char *item;
    unsigned int No;
}Menu;
void setmenu(Menu *mainmenu, Menu *submenu[4], Menu *thirdmenu[5]);//设定各级菜单的集成函数
void setmainmenu(Menu *mainmenu);
void drawmainmenu(Menu *mainmenu);  //画出主菜单。
void nowmainmenu(Menu *mainmenu,int No,int status);//在程序大循环中，循环从主菜单第一项开始到第四项检查是否发生点击。点击某项后，该项标记为活跃，进入次级菜单。
void setsubmenu(Menu *submenu[4],Menu *mainmenu);
int drawsubmenu(Menu *submenu[4],Menu mainmenu);//进入次级菜单后，循环检测是否点击了次级菜单的某一项。返回值规则：第a个主菜单的第b个子菜单对应返回值为10*a+b.
//返回11打开，12保存，24缩放时需要打开输入框；返回21亮度，22旋转，23镜像，31扩散，32锐化，33柔化，35滤镜需要打开三级菜单；41，42，43是帮助选项；其他的选项无需弹出对话框。
//保存，打开操作成功失败时给出相应提示框。返回-1说明本次打开子菜单没有执行功能。

void exitmenu(imagesave *storage);//主要用于次级菜单退出。恢复被覆盖的区域。
void nowsubmenu(Menu *submenu,int No,int now,int status);//status: 1,表示点击选项，实质是鼠标放在框上不点击；0表示其他鼠标情况
void setthirdmenu(Menu *thirdmenu[5]);
int drawthirdmenu(Menu *thirdmenu[5],int No)//输入参数No表示类型。1是旋转方向选项，2是亮度选项，3是镜像选项，4是滤镜选项，5是程度选项。返回值：1-5是五个程度；6，7是一级，二级变亮；
//8是原亮度；9，10是一级，二级变暗；11，12是顺时针，逆时针；13，14是上下，左右翻转；21-25是五个滤镜。
void nowthirdmenu(Menu *thirdmenu[5],int No,int now,int status)
#endif // MENU_H_INCLUDED
