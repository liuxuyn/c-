#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "common.h"
void bar_new(int left, int top, int right, int bottom,unsigned int color,unsigned int pattern);
void line_new(int left, int top, int right, int bottom, unsigned int linestyle,int thickness);
typedef struct imagebuffer
{
    int local[4];
    unsigned char* ibuffer;
}imagesave;
#endif // DRAW_H_INCLUDED
