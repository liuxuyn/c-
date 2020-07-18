#include<graphics.h>                    
#include<conio.h>
void main()
{
	int graphdriver=DETECT;
	int graphmode,x;
	initgraph(&graphdriver,&graphmode,"c:\\borlandc\\bgi");
	cleardevice();
	setpalette(1,0);
	setbkcolor(RED);
	setcolor(1);
	arc(320,240,0,180,200);
	arc(220,240,0,180,100);
	arc(420,240,180,360,100);
	setfillstyle(1,1);
	floodfill(321,240,1);
	setcolor(WHITE);
	arc(320,240,180,360,200);
	arc(220,240,0,180,100);
	arc(420,240,180,360,100);
	circle(420,240,20);
	setfillstyle(1,WHITE);
	floodfill(420,240,WHITE);
	floodfill(319,240,WHITE);
	setcolor(1);
	circle(220,240,20);
	setfillstyle(1,1);
	floodfill(220,240,1);
	getch();
	closegraph();
}