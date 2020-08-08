#include "draw.h"

void bar_new(int left, int top, int right, int bottom,unsigned int color,unsigned int pattern) //»­¾ØÐÎ£¬ÓÃcolorÌî³ä
{
    setfillstyle(pattern,color);
    bar(left,top,right,bottom);
}

void line_new(int left, int top, int right, int bottom, unsigned int color,unsigned int linestyle)
{
    setcolor(color);
    setlinestyle(linestyle,0,1);
    line(left,top,right,bottom);
}

void rectangle_new(int left, int top, int right,int bottom, unsigned int color, unsigned int linestyle)
{
    setlinestyle(linestyle,0,1);
    setcolor(color);
    rectangle(left,top,right,bottom);
}
