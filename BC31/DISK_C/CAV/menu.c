#include "menu.h"
#include "mouse.h"
#include "SVGA.h"
#include <conio.h>
#include <graphics.h>
#include <dos.h>


void initg()
{
	int graphdriver=DETECT,graphmode;
	initgraph(&graphdriver,&graphmode,"C:\\BORLANDC\\BGI");	 
}

void welcome()
{
	SetSVGAMode(0x111);
	SetScreenWidth(1280l);
	ReadBMP16(0,0,"C:\\CAV\\bmp\\1.bmp"); 
	getch();
}
void aveinit()
{
	SetSVGAMode(0x111);
	SetScreenWidth(1280l);
	
}
void menuinit()
{
	SetSVGAMode(0x111);
	SetScreenWidth(1280l);
	ReadBMP16(0,0,"C:\\CAV\\bmp\\2.bmp");
	MouseSetSpeed(2,4);
	SetMousePosition(320,240);
	SetMouseRange(0,0,640,480);
}
int menucheck(FlyingPara *FLY)
{
	int temp,status=0;
	Coord mouse;
	menuinit();
	while(1)
	{
		temp = 0;
		
			ReadMouse(&mouse.x,&mouse.y,&status);
			MouseCpy(&mouse,&FLY->mouse_buffer);
			MouseShow(&mouse);
		if(mouse.x>=20&&mouse.x<=140&&mouse.y>=100&&mouse.y<=160&&status==1)
		{
			temp = FLYING;
			return temp;
		} 
		else if(mouse.x>=20&&mouse.x<=140&&mouse.y>=310&&mouse.y<=370&&status==1)
		{
			temp = SETTING;
		}
		else if(mouse.x>=450&&mouse.x<=570&&mouse.y>=100&&mouse.y<=160&&status==1)
		{
			temp = ABOUTING;
		}
		else if(mouse.x>=450&&mouse.x<=570&&mouse.y>=310&&mouse.y<=370&&status==1)
		{
			temp = PERSON;
		}
		else if(mouse.x>=520&&mouse.x<=640&&mouse.y>=420&&mouse.y<=480&&status==1)
		{
			temp = EXIT;
			return temp;
		}
		
		switch(temp)
		{
			case 4:
				setting(FLY);
				menuinit();
					break;
			case 5:
				abouting(FLY);
				menuinit();
					break;
			case 6:
				person(FLY);
				menuinit();
					break;
		}
			MouseReshow(&mouse,&FLY->mouse_buffer);
	
	}
}
int flying(FlyingPara *Fly)
{
	int status=0;
	Coord mouse;
	ReadBMP16(0,0,"C:\\CAV\\bmp\\0.bmp");  
	while(1)
	{	
		
			ReadMouse(&mouse.x,&mouse.y,&status);
			MouseCpy(&mouse,Fly->mouse_buffer);
			MouseShow(&mouse);
			
			if(mouse.x>=520&&mouse.x<=640&&mouse.y>=420&&mouse.y<=480&&status==1)
		{
			break;
		} 
			MouseReshow(&mouse,&Fly->mouse_buffer);
			
		
	}	
}
int setting(FlyingPara *Fly)
{
	int status=0;
	Coord mouse;
	ReadBMP16(0,0,"C:\\CAV\\bmp\\3.bmp"); 
		while(1)
	{	
		
			ReadMouse(&mouse.x,&mouse.y,&status);
			MouseCpy(&mouse,Fly->mouse_buffer);
			MouseShow(&mouse);
			
			if(mouse.x>=520&&mouse.x<=640&&mouse.y>=420&&mouse.y<=480&&status==1)
		{
			break;
		} 
			MouseReshow(&mouse,&Fly->mouse_buffer);
			
		
	}
}
int abouting(FlyingPara *Fly)
{
	int status=0;
	Coord mouse;
	ReadBMP16(0,0,"C:\\CAV\\bmp\\4.bmp"); 
	
		while(1)
	{	
		
			ReadMouse(&mouse.x,&mouse.y,&status);
			MouseCpy(&mouse,Fly->mouse_buffer);
			MouseShow(&mouse);
			
			if(mouse.x>=520&&mouse.x<=640&&mouse.y>=420&&mouse.y<=480&&status==1)
		{
			break;
		} 
			MouseReshow(&mouse,&Fly->mouse_buffer);
			
		
	}	
}
int person(FlyingPara *Fly)
{
	int status=0;
	Coord mouse;
	ReadBMP16(0,0,"C:\\CAV\\bmp\\4.bmp"); 
		while(1)
	{	
		
			ReadMouse(&mouse.x,&mouse.y,&status);
			MouseCpy(&mouse,&Fly->mouse_buffer);
			MouseShow(&mouse);
			
			if(mouse.x>=520&&mouse.x<=640&&mouse.y>=420&&mouse.y<=480&&status==1)
		{
			break;
		} 
			MouseReshow(&mouse,&Fly->mouse_buffer);
			
		
	}	
}
