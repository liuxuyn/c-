#include<stdio.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include"mouse.h"
void main()
{
	int status;
	Coord mouse;
	FlyingPara FLY;	
	SetSVGAMode(0x111);
	SetScreenWidth(1280l);
	SetMouseRange(0,0,640,480);
	SetMousePosition(320,240);
	MouseSetSpeed(2,4);
	ReadBMP16(0,0,"C:\\CAV\\bmp\\1.bmp"); 
	while(!kbhit())
	{
			ReadMouse(&mouse.x,&mouse.y,&status);
			MouseCpy(&mouse,&FLY.mouse_buffer);
			MouseShow(&mouse);
			MouseReshow(&mouse,&FLY.mouse_buffer);
	}
	getch();




}