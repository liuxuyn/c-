#ifndef _mouse_h_
#define _mouse_h_


typedef struct Coord
{
    int x,y;
}Coord;
typedef struct FlyingPara
{
	char sound;   //=1则系统有声音，=0则无声
    short *buffer;
	short *mouse_buffer;  
}FlyingPara;/*常用参量变量*/

void initmouse(Coord *MS);
void MouseReset();
void SetMousePosition(int x,int y);
void SetMouseSen(int x,int y);
void SetMouseVelo(int v);
void SetMouseRange(int left,int top,int right,int bottom);
void ReadMouse( int *mouse_x,int *mouse_y,char *mouse_butt );
//void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt);
void MouseCpy(Coord *CoordXY,short *);
void MouseReshow(Coord *,short *);
void MouseShow(Coord *CoordXY);

int menu(FlyingPara *FLY);
int flying(FlyingPara *Fly);
int setting(FlyingPara *Fly);
int abouting(FlyingPara *Fly);
int person(FlyingPara *Fly);

#endif