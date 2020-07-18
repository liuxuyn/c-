#ifndef _mouse_h_
#define _mouse_h_
void MouseReset();
void SetMousePosition(int x,int y);
void SetMouseSen(int x,int y);
void SetMouseVelo(int v);
void SetMouseRange(const int left,const int top,const int right,const int bottom);
void ReadMouse( int *mouse_x,int *mouse_y,char *mouse_butt );
//void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt);
void MouseCpy(Coord *CoordXY,short *);
void MouseReshow(Coord *,short *);
void MouseShow(Coord *CoordXY);
#endif