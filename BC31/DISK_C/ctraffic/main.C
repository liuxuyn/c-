#include "all.h"
#include "readbmp.h"
#include "intro.h"
#include "menu.h"

struct MOUSE
{
    int mx;
    int my;
    int mstate;
}MS;               //注  键盘输入也读到鼠标状态当中

void main()
{
    readbmp("wenjian\\welcome.bmp");
    introduct();
    menu();
}