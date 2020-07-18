
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#define pi 3.1415926
//void users1();
void init();
void ButtonUp(int x1,int y1,int x2,int y2,int W);
void huakuang(int x,int y,int x1,int y1,int color);
void ButtonIntial(int x1,int y1,int x2,int y2,int W);
void ButtonDown(int x1,int y1,int x2,int y2,int W);
void mountain(float x0,float y0,float h);

//ç”¨æˆ·ç•Œé¢çš„ç»˜åˆ¶
void main()
{	
  char *a[]={"»¶Ó­Ê¹ÓÃÎŞÈË»ú·ÉĞĞÄ£ÄâÏµÍ³","ÓÃ»§Ãû","ÃÜÂë","ÇëÊäÈëÓÃ»§Ãû","ÇëÊäÈëÃÜÂë","µÇÂ½","×¢²á","ÍË³ö","Çë×¢Òâ´óĞ¡Ğ´"} ;
  init();
  huakuang(320,240,400,200,LIGHTGRAY);
  settextstyle(0,0,1);
  settextjustify(1,1);
  chinese(a[0],320,170,16,1,1,BLACK);
  outtextxy(180,200,a[1]);
  chinese(a[1],340,200,16,1,1,BLACK);
  chinese(a[2],180,230,16,1,1,BLACK);
  huakuang(340,230,150,17,BLACK);
  setcolor(WHITE);
  rectangle(119,139,521,341);
  rectangle(264,191,416,209);
  rectangle(264,221,416,239);
  ButtonIntial(255,273,325,297,3);//ç™»é™† åæ ‡èŒƒå›´
  ButtonIntial(145,273,215,297,3);//æ³¨å†Œ åæ ‡èŒƒå›´
  ButtonIntial(365,273,435,297,3);//é€€å‡º åæ ‡èŒƒå›´
  setcolor(WHITE);
  chinese(a[3],340,200,16,1,1,WHITE);
  chinese(a[4],340,230,16,1,1,WHITE);
  chinese(a[5],180,285,16,1,1,BLACK);
  chinese(a[6],290,285,16,1,1,BLACK);
  chinese(a[7],400,285,16,1,1,BLACK);
  chinese(a[8],320,315,16,1,1,BLACK);
  //mountain(80,100,40);
  
	/*while(!kbhit())
	{
		mouse(&X,&Y,&Mkey,&mx,&my);
	}

  getch();
  closegraph();*/
  getch();

}
void huakuang(int x,int y,int x1,int y1,int color)
//è¾“å…¥ç”»æ¡†çš„ä¸­å¿ƒä»¥åŠé•¿å’Œå®½
{
	setfillstyle(SOLID_FILL,color);
	bar(x-x1/2,y-y1/2,x+x1/2,y+y1/2);

}
/* x1 y1,x2,y2ä¸ºè¾¹ç•Œåæ ‡*/
/* wä¸ºè¾¹ç•Œåšåº¦ï¼Œhzä¸ºæŒ‰é’®å­—ä½“*/
/****ç”»æŒ‰é’®****/
void ButtonIntial(int x1,int y1,int x2,int y2,int W)
{
	int i;

	setfillstyle(1,LIGHTGRAY);
	bar(x1,y1,x2,y2);
	setfillstyle(1,LIGHTGRAY);
	bar(x1+W,y1+W,x2-W,y2-W);

	setcolor(WHITE);
	for(i=0;i<=W;i++)
		line(x1,i+y1,x2-i,i+y1);
	for(i=0;i<=W;i++)
		line(x1+i,y1+W,x1+i,y2-i);

	setcolor(BLACK);
	for(i=0;i<=W;i++)
		line(x2,i+y2-W,x1+W-i,i+y2-W);
	for(i=0;i<=W;i++)
		line(x2-W+i,y2-W,x2-W+i,y1+W-i);
	/****æŒ‰é’®å¼¹èµ·è¾¹æ¡†å˜åŒ–****/
 }
void ButtonUp(int x1,int y1,int x2,int y2,int W)
{
	int i;
    
	setcolor(WHITE);
	for(i=0;i<=W;i++)
		line(x1,i+y1,x2-i-1,i+y1);
	for(i=0;i<=W;i++)
		line(x1+i,y1+W,x1+i,y2-i-1);

	setcolor(BLACK);
	for(i=0;i<=W;i++)
		line(x2,i+y2-W,x1+W-i,i+y2-W);
	for(i=0;i<=W;i++)
		line(x2-W+i,y2-W,x2-W+i,y1+W-i);

}


/****æŒ‰é’®æŒ‰ä¸‹è¾¹æ¡†å˜åŒ–****/
void ButtonDown(int x1,int y1,int x2,int y2,int W)
{
	int i;
	
	setcolor(BLACK);
	for(i=0;i<=W;i++)
		line(x1,i+y1,x2-i-1,i+y1);
	for(i=0;i<=W;i++)
		line(x1+i,y1+W,x1+i,y2-i-1);

	setcolor(WHITE);
	for(i=0;i<=W;i++)
		line(x2,i+y2-W,x1+W-i,i+y2-W);
	for(i=0;i<=W;i++)
		line(i+x2-W,y2-W,x2-W+i,y1+W-i);
}


void init()
{
	int graphdriver=DETECT;
	int graphmode;
	initgraph(&graphdriver,&graphmode,"c:\\borlandc\\BGI");
}
