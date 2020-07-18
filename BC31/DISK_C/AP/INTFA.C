#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include<alloc.h>
#include<stdio.h>
#include"head.h"
#include"mouse.h"
#include"SVGA.h"
#include"intfa2.h"
#include"letter.h"
#include"anima.h"
#include"common.h"
#include"check.h"
#include"intfa.h"
/**************************************************************************
	功能说明：游戏初始化设置
	参数说明：
	返回值说明：
**************************************************************************/
char GameInit(GamePara *para)
{
	int pass;
	SetSVGAMode(0x114);
	SetScreenWidth(1600l);
	para->logwid=1600l;
	MouseReset();
	para->interface=INTERFACE1;
	para->gamemode=1;
	para->diretion=1;
	para->sound=0;
	para->pig=1;
	pass=GetLevNum();
	if(pass<7)
		para->mode1pass=pass+1;
	else
		para->mode1pass=pass;
	para->gamemode=1;
	para->pig=1;
	para->mouse_buffer=(short *)malloc(32*16);
	if(para->mouse_buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function GameInit");
		getch();
		exit(1);
	}
	SetMouseRange(0,0,800,600);
	MouseSetSpeed(2,4);
	return 1;

}
/**************************************************************************
	功能说明：界面2初始化设置
	参数说明：
	返回值说明：
**************************************************************************/
char Interface2Init(GamePara *para)   //界面2初始化
{
	ReadBMP16(0,0,"btn\\jie2.bmp") ;
	ReadBtn(178,518,"btn\\set1.bmp",0);
	ReadBMP16(284,247,"btn\\play1.bmp");
	ReadBtn(12,518,"btn\\exit1.bmp",0);
	ReadBtn(95,518,"btn\\high1.bmp",0);
	ReadBtn(720,518,"btn\\movie1.bmp",0);
	MoveScreen(para->diretion,1);          //在左边
	SetMousePosition(200,300);
	SetMouseRange(0,0,800,600);
	return 1;
}

/***********************************************************************
	功能说明：第二个界面的逻辑判断及跳转
	参数说明：para，系统常用变量
	返回值说明：返回值暂时没有特殊含义，，，，为后期修改提供便利
**********************************************************************/
char Interface2Check(GamePara *para)
{
	 Button button_exit,button_about,button_high,button_movie;
	 char SoundAbout=0,flagset=0,flagplay=0;
	 char a;
	 Coord mouse;
	 	//*******************按键信息****************************
		button_exit.left=12;
		button_exit.top=518;
		button_exit.right=87;
		button_exit.bottom=593;
		strcpy(button_exit.a,"btn\\exit1.bmp");
		stpcpy(button_exit.b,"btn\\exit2.bmp");
		
		button_high.left=95;
		button_high.top=518;
		button_high.right=170;
		button_high.bottom=593;
		strcpy(button_high.a,"btn\\high1.bmp");
		stpcpy(button_high.b,"btn\\high2.bmp");
		
		button_about.left=187;
		button_about.top=390;
		button_about.right=244;
		button_about.bottom=446;
		strcpy(button_about.a,"btn\\about1.bmp");
		stpcpy(button_about.b,"btn\\about2.bmp");
		
		button_movie.left=720;
		button_movie.top=518;
		button_movie.right=796;
		button_movie.bottom=593;
		strcpy(button_movie.a,"btn\\movie1.bmp");
		stpcpy(button_movie.b,"btn\\movie2.bmp");
	 while(1)
	 {
	//************************************设置set**************************************
	
		ReadMouse(&mouse.x,&mouse.y,&a);
		MouseCpy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		if(flagset==0&&IsinRange(mouse,178,518,253,593))
		{			
			ReadBtn(178,518,"btn\\set2.bmp",0);
			ReadBtn(187,390,"btn\\s.bmp",0);	
			flagset=1;			
			if(!para->sound)
			{
				ReadBtn(187,450,"btn\\sound2.bmp",0);
			}
			SoundAbout=1;
		}
		else if(flagset==1&&!IsinRange(mouse,178,518,253,593))
		{
			ReadBtn(178,518,"btn\\set1.bmp",0);
			flagset=0;
		}
		MouseReshow(&mouse,para->mouse_buffer);
		
		//***********************************play键*****************************************************
		if(PlayCheck(&flagplay,para))
			return 1;

		//************************************重放动画********************************************************
		if(ButtonA(button_movie,para,0))
		{
			do
			{
				ReadMouse(&mouse.x,&mouse.y,&a);
			}while(a!=0);
			delay(10);
			ReadBtn(720,518,"btn\\movie3.bmp",0);
			para->interface=INTERFACE1;
			return 1;
		}
			//************************************退出键exit*************************************************
		if(ButtonA(button_exit,para,0))
		{
			ReadBtn(225,225,"btn\\box2.bmp",0xd3);
			ExitBox(para);
		}
		//*************************************最高分键high********************************************************
		if(ButtonA(button_high,para,0))
		{
			para->diretion=1;
			para->interface=HIGH;
			return 1;
		}
	//**************************************音效键sound******************************************************
		Sound1Check(&SoundAbout,para);
		//****************************************关于键about******************************************************
		if(SoundAbout==1)//当前处于关于键的坐标范围
		{				
			if(ButtonB(button_about,para))
			{
				para->interface=ABOUT;
				para->diretion=1;
				return 1;
			}
		}

	 }
}




/**************************************************************************
	功能说明：”关于“界面初始化设置
	参数说明：
	返回值说明：
**************************************************************************/
char InterfaceAboutInit(GamePara *para)  //关于界面初始化
{
	ReadBMP16(800,0,"btn\\about.bmp");
	MoveScreen(para->diretion,2);
	SetMousePosition(800,0);
	SetMouseRange(800,0,1600,600);
	return 1;
}


/**************************************************************************
	功能说明：”关于“界面运行ing
	参数说明： para 游戏常用变量
	返回值说明：
**************************************************************************/
char InterfaceAbout(GamePara *para)
{
	register int i=1;
     //	char flag=1;
	Coord mouse;
	Area area;
	char a;
	Button button;
	
	button.left=829;
	button.top=25;
	button.right=912;
	button.bottom=109;
	strcpy(button.a,"btn\\back1.bmp");
	stpcpy(button.b,"btn\\back2.bmp");
	while(1)
	{
	  	if(ButtonB(button,para))
		{
			para->interface=INTERFACE2;
			para->diretion=0;
			return 1;
		}
		//**********************************************************
		ReadMouse(&mouse.x,&mouse.y,&a);
		MouseCpy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		if(i<352&&!IsinRange(mouse,1176,128,1468,481))
		{
			area.left=0;
			area.top=0;
			area.right=292;
			area.bottom=i;
			ReadPartBMP(area,1176,480-i,"btn\\abmov.bmp",para,0);
			i++;
		}
		else if(!IsinRange(mouse,1176,128,1468,481))
		{
			area.left=0;
			area.top=i-352;
			area.right=292;
			area.bottom=i;
			ReadPartBMP(area,1176,128,"btn\\abmov.bmp",para,0);
			i++;
		}
		else 
		{
			delay(10);
		}
		i%=950;
		MouseReshow(&mouse,para->mouse_buffer);
	}
}

/**************************************************************************
	功能说明：”最高分“界面初始化设置
	参数说明：
	返回值说明：
**************************************************************************/
char InterfaceHighInit(GamePara *para) //最高分界面初始化
{
	ReadBMP16(800,0,"btn\\high.bmp");
	ReadBMP16(1116,104,"btn\\page1.bmp");
	ShowHighScore(0,para);
	ReadBtn(1370,510,"btn\\pre3.bmp",0);
	ReadBtn(1420,510,"btn\\next1.bmp",0);
	ReadBtn(1118,510,"btn\\reset1.bmp",0);
	MoveScreen(para->diretion,2);
 	SetMousePosition(1000,100);
	SetMouseRange(800,0,1600,600);
	return 1;
}


/**************************************************************************
	功能说明：”最gao分“界面运行ing
	参数说明：
	返回值说明：
**************************************************************************/
char InterfaceHigh(GamePara *para)
{
	Coord mouse;
	char s[15];
	char a;
	Button button_return,button_prev,button_next,button_reset;
	char ScorePage=0,flagprev=0,flagnext=0; //加标记变量减少读图片次数，加快判断速度
	button_return.left=827;
	button_return.top=23;
	button_return.right=912;
	button_return.bottom=109;
	strcpy(button_return.a,"btn\\back1.bmp");
	stpcpy(button_return.b,"btn\\back2.bmp");
	
	button_prev.left=1370;
	button_prev.top=510;
	button_prev.right=1411;
	button_prev.bottom=541;
	strcpy(button_prev.a,"btn\\pre1.bmp");
	stpcpy(button_prev.b,"btn\\pre2.bmp");
	
	button_next.left=1420;
	button_next.top=510;
	button_next.right=1461;
	button_next.bottom=541;
	strcpy(button_next.a,"btn\\next1.bmp");
	stpcpy(button_next.b,"btn\\next2.bmp");
	
	button_reset.left=1118;
	button_reset.top=510;
	button_reset.right=1147;
	button_reset.bottom=539;
	strcpy(button_reset.a,"btn\\reset1.bmp");
	stpcpy(button_reset.b,"btn\\reset2.bmp");
	//**********************************************************
	while(1)
	{
		//*************************************************************

	  	if(ButtonB(button_return,para))
		{
			para->interface=INTERFACE2;
			para->diretion=0;
			return 1;
		}
		if(ButtonB(button_reset,para))
		{
			ResetHighScore();
			ScorePage=0;
			sprintf(s,"btn\\page%d.bmp",ScorePage+1);
			ReadBMP16(1116,104,s);
			ShowHighScore(ScorePage,para);
			para->mode1pass=1;
			
		}
		//***********************************************************
		if(flagprev==0&&ScorePage==0)
		{
			ReadBtn(1370,510,"btn\\pre3.bmp",0);
			flagprev=1;
		}
		else if(ScorePage!=0)
		{
			ReadBtn(1370,510,"btn\\pre1.bmp",0);
			flagprev=0;
			if(ButtonB(button_prev,para))
			{
				
				ScorePage-=1;
				sprintf(s,"btn\\page%d.bmp",ScorePage+1);
				ReadBMP16(1116,104,s);
				ShowHighScore(ScorePage,para);
			}
		}
		//************************************************************
		if(flagnext==0&&ScorePage==2)
		{
			ReadBtn(1420,510,"btn\\next3.bmp",0);
			flagnext=1;
		}
		else if(ScorePage!=2)
		{
			ReadBtn(1420,510,"btn\\next1.bmp",0);
			flagnext=0;
			if(ButtonB(button_next,para))
			{

				ScorePage+=1;
				sprintf(s,"btn\\page%d.bmp",ScorePage+1);
				ReadBMP16(1116,104,s);
				ShowHighScore(ScorePage,para);
			}
		}
	}

}




/**************************************************************************
	功能说明：”选择模式“界面初始化设置
	参数说明：
	返回值说明：
**************************************************************************/
char InterfaceModSelInit(GamePara *para)
{
	ReadBMP16(800,0,"btn\\modsel.bmp");
	MoveScreen(para->diretion,2);
	SetMousePosition(1200,300);
	SetMouseRange(800,0,1600,600);
	return 1;
}

/**************************************************************************
	功能说明：”选择模式“界面运行ing
	参数说明： para 游戏常用变量
	返回值说明：
**************************************************************************/
char InterfaceModSel(GamePara *para)
{
	int i=0;
	Button button_return,button[10];
	for(i=0;i<3;i++)
	{
		button[i].left=1027+i*120;
		button[i].top=309;
		button[i].right=button[i].left+50;
		button[i].bottom=button[i].top+50;
	}
	button[3].left=962;
	button[3].top=409;
	button[3].right=button[i].left+50;
	button[3].bottom=button[i].top+50;
	for(i=4;i<7;i++)
	{
		button[i].left=1092+(i-4)*120;
		button[i].top=409;
		button[i].right=button[i].left+50;
		button[i].bottom=button[i].top+50;
	}
	for(i=7;i<10;i++)
	{
		button[i].left=1027+(i-7)*120;
		button[i].top=509;
		button[i].right=button[i].left+50;
		button[i].bottom=button[i].top+50;
	}
	strcpy(button[0].a,"body\\pig02.bmp");
	strcpy(button[0].b,"body\\pig01.bmp");
	strcpy(button[1].a,"body\\pig11.bmp");
	strcpy(button[1].b,"body\\pig12.bmp");
	strcpy(button[2].a,"body\\pig21.bmp");
	strcpy(button[2].b,"body\\pig22.bmp");
	strcpy(button[3].a,"body\\pig31.bmp");
	strcpy(button[3].b,"body\\pig32.bmp");
	strcpy(button[4].a,"body\\pig41.bmp");
	strcpy(button[4].b,"body\\pig42.bmp");
	strcpy(button[5].a,"body\\pig51.bmp");
	strcpy(button[5].b,"body\\pig52.bmp");
	strcpy(button[6].a,"body\\pig61.bmp");
	strcpy(button[6].b,"body\\pig62.bmp");
	strcpy(button[7].a,"body\\pig71.bmp");
	strcpy(button[7].b,"body\\pig72.bmp");
	strcpy(button[8].a,"body\\pig81.bmp");
	strcpy(button[8].b,"body\\pig82.bmp");
	strcpy(button[9].a,"body\\pig91.bmp");
	strcpy(button[9].b,"body\\pig92.bmp");

	button_return.left=827;
	button_return.top=23;
	button_return.right=909;
	button_return.bottom=109;
	strcpy(button_return.a,"btn\\back1.bmp");
	stpcpy(button_return.b,"btn\\back2.bmp");
	
	
	while(1)
	{
	 //***************************返回键*********************************
		if(ButtonB(button_return,para))
		{
			para->interface=INTERFACE2;
			para->diretion=0;
			return 1;
		}
		//*********检测各类猪****************
		for(i=0;i<10;i++)
		{
			if(ButtonA(button[i],para,123))
			{
				ReadBtn(button[i].left,button[i].top,"body\\pow.bmp",0xd1d);
				para->interface=LEVSEL1;
				para->pig=i;
				para->diretion=1;
				Right2Left(para);
				SetShowBegin(0,0);
				return 1;
			}
		}
		
		
	}
}
/**************************************************************************
	功能说明：”选择关卡“界面初始化设置
	参数说明：
	返回值说明：
**************************************************************************/
char InterfaceLevSelInit(GamePara *para)
{
	int i;
	char s[15] ,*string;
	char star[15];
	int StarNum=0;
	//BuildNum(a);
	ReadBMP16(800,0,"btn\\levsel.bmp");
	for(i=0;i<para->mode1pass;i++)
	{
		ReadBtn(954+(i%4)*146,59+(i/4)*180,"btn\\levon2.bmp",0);  //把已经通关的关卡解锁
		sprintf(string,"num\\%d.bmp",i+1);
		ReadBtn(985+(i%4)*146,72+(i/4)*180,string,0x35f);
		StarNum=GetLevStar(i);
		if(StarNum)
		{
			sprintf(star,"btn\\score%d.bmp",StarNum);
			ReadBtn(970+(i%4)*146,162+(i/4)*180,star,0);
		}
	}
	ReadBtn(800+591,398,"btn\\fm.bmp",0);
	MoveScreen(para->diretion,2);
	SetMousePosition(810,10);
	SetMouseRange(800,0,1600,600);
	return 1;
}

/**************************************************************************
	功能说明：”选择关卡“界面运行ing
	参数说明：
	返回值说明：
**************************************************************************/
char InterfaceLevSel(GamePara *para)
{
	int i;
	char a;
	Coord mouse;
	Button button_return,button_fm;
	button_return.left=827;
	button_return.top=23;
	button_return.right=912;
	button_return.bottom=109;
	strcpy(button_return.a,"btn\\back1.bmp");
	stpcpy(button_return.b,"btn\\back2.bmp");
	//*************************************
	button_fm.left=827;
	button_fm.top=23;
	button_fm.right=912;
	button_fm.bottom=109;
	strcpy(button_fm.a,"btn\\back1.bmp");
	stpcpy(button_fm.b,"btn\\back2.bmp");
	//****************************
	  //**********************************************************************************************************
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&a);
		MouseCpy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		for(i=0;i<para->mode1pass;i++)
		{
			if(a==1&&IsinRange(mouse,954+(i%4)*146,59+(i/4)*180,1035+(i%4)*146,185+(i/4)*180))
			{
				ReadBtn(936+(i%4)*146,41+(i/4)*180,"btn\\levon1.bmp",0);			
				para->interface=10+i;
				para->diretion=1;
				return 1;
			}
			
		}
		if(a==1&&IsinRange(mouse,800+591,398,800+694,499))
		{
			ReadBtn(800+591-18,398-18,"btn\\levon1.bmp",0);
			para->interface=FREEMODE;
			para->diretion=1;
			return 1;
		}
		MouseReshow(&mouse,para->mouse_buffer);
		//******************返回键 return key************************
		if(ButtonB(button_return,para))
		{
			para->interface=MODSEL;
			para->diretion=0;
			Right2Left(para);	
			SetShowBegin(0,0);
			return 1;
		}
	}

}


char PlayCheck(char *flagplay, GamePara *para)
{
	Coord mouse;
	char a;
	ReadMouse(&mouse.x,&mouse.y,&a);
	if(*flagplay==0&&IsinRange(mouse,296,256,522,407))//在开始键的坐标范围中
	{
		ReadBtn(284,247,"btn\\play2.bmp",0x3f);
		*flagplay=1;
	}
	if(a==1&&IsinRange(mouse,296,256,522,407))
	{
		para->interface=MODSEL;
		para->diretion=1;
		ReadBMP16(284,247,"btn\\play1.bmp");
		return 1;
	}
	if(*flagplay==1&&(!IsinRange(mouse,296,256,522,407)))//不在开始键的坐标范围中
	{
		ReadBMP16(284,247,"btn\\play1.bmp");
		*flagplay=0;
	}
	return 0;
}


char Sound1Check(char *SoundAbout,GamePara *para)
{

	Coord mouse;
	char a;
	ReadMouse(&mouse.x,&mouse.y,&a);
	if(a==1&&IsinRange(mouse,187,450,244,504)&&*SoundAbout==1)//当前处于音效键的坐标范围
	{
		if(para->sound)//当前音效开
		{
			ReadBtn(187,450,"btn\\sound2.bmp",0);
			delay(10);
			para->sound=0;
		}
		else//当前音效关
		{
			ReadBtn(187,450,"btn\\sound1.bmp",0);
			delay(10);
			para->sound=1;
		}
	}
	if(*SoundAbout==1&&(!IsinRange(mouse,187,390,253,593)))//离开音效关于键的范围，
	{
		ReadBtn(187,390,"btn\\s1.bmp",0xf800);
		*SoundAbout=0;

	}
}