#include "draw.h"

void bar_new(int left, int top, int right, int bottom,unsigned int color,unsigned int pattern) //»­¾ØĞÎ£¬ÓÃcolorÌî³ä
{
    setfillstyle(pattern,color);
    bar(left,top,right,bottom);
}

void line_new(int left, int top, int right, int bottom, unsigned int linestyle,int thickness)
{
    setcolor(BLACK);
    setlinestyle(linestyle,0,thickness);
    line(left,top,right,bottom);
}

