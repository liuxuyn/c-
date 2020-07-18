#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include"sound.h"
#include"head.h"
#include"SVGA.h"
#include"mouse.h"
#include"intfa.h"
#include"anima.h"
#include"common.h"
#include"intfa2.h"


/**************************************************************************
	功能说明：”侧边栏“界面检测
	参数说明：para 游戏常用变量
	返回值说明：返回1时要退出游戏界面 return
**************************************************************************/
char SidePartCheck(GamePara *para)
{
	Coord mouse;
	char a;
	char fanhui;
	ReadMouse(&mouse.x,&mouse.y,&a);
	MouseCpy(&mouse,para->mouse_buffer);
	MouseShow(&mouse);
	if(IsinRange(mouse,3,3,64,64)&&a==1)
	{
		MouseReshow(&mouse,para->mouse_buffer);
		if(para->buffer==NULL)
		{
			ReturnMode();
			printf("malloc error in function SidePartMove");
		}		
		SidePartMove(para->buffer,1);
		fanhui=SidePart(para);
		if(fanhui==1)
		{
			return 1;
		}
		else if(fanhui==0)
		{
			SidePartMove(para->buffer,0);
		}
	}
	else
	{
		MouseReshow(&mouse,para->mouse_buffer); 
	}
	
}

/**************************************************************************
	功能说明：”侧边栏“界面初始化设置及”侧边栏“背景扣取
	参数说明：para 游戏常用变量
	返回值说明：
**************************************************************************/
char SidePart(GamePara *para)
{
	Coord mouse;
	char a;
	char*string;
	Button button_continue,button_retry,button_menu,button_help;
	ReadBMP16(0,0,"btn\\sidpar.bmp");
	//***************显示当前关数 如： 1——2 ******************
	if(para->interface!=FREEMODE)
	{
		ReadBtn(150,10,"num2\\1.bmp",0x35f);
		ReadBtn(170,10,"num2\\point.bmp",0x35f);
		sprintf(string,"num2\\%d.bmp",para->interface-9);
		ReadBtn(190,10,string,0x35f);
	}
	else
	{
		ReadBtn(150,10,"num2\\f.bmp",0x35f);
		ReadBtn(170,10,"num2\\point.bmp",0x35f);
		ReadBtn(190,10,"num2\\m.bmp",0x35f);
	}
	

	//**************判断声音状态****************************
	if(para->sound==0)
		ReadBtn(15,438,"btn\\sound4.bmp",0);
	//*********************按键数据*************************
	button_continue.left=5;
	button_continue.top=4;
	button_continue.right=104;
	button_continue.bottom=101;
	strcpy(button_continue.a,"btn\\con1.bmp");
	stpcpy(button_continue.b,"btn\\con2.bmp");

	button_retry.left=58;
	button_retry.top=118;
	button_retry.right=180;
	button_retry.bottom=237;
	strcpy(button_retry.a,"btn\\retry1.bmp");
	stpcpy(button_retry.b,"btn\\retry2.bmp");
	
	button_menu.left=59;
	button_menu.top=261;
	button_menu.right=180;
	button_menu.bottom=380;
	strcpy(button_menu.a,"btn\\sidme1.bmp");
	stpcpy(button_menu.b,"btn\\sidme2.bmp");	
	
	button_help.left=127;
	button_help.top=438;
	button_help.right=226;
	button_help.bottom=535;
	strcpy(button_help.a,"btn\\help1.bmp");
	stpcpy(button_help.b,"btn\\help2.bmp");
	while(1)
	{
		//************************continue*****************************************
		if(ButtonB(button_continue,para))
		{
			return 0;
		}
		//************************retry********************************************
		if(ButtonB(button_retry,para))
		{
			return 1;
		}
		//************************return level selet*******************************
		if(ButtonB(button_menu,para))
		{
			para->interface=LEVSEL1;
			para->diretion=0;
			return 1;
		}
		//************************sound *******************************************
		ReadMouse(&mouse.x,&mouse.y,&a);
		if(a==1&&IsinRange(mouse,15,438,114,535))//当前处于sound键的坐标范围
		{

			if(para->sound)
			{
				ReadBtn(15,438,"btn\\sound4.bmp",0);
				para->sound=0;
			}
			else
			{
				ReadBtn(15,438,"btn\\sound3.bmp",0);
				para->sound=1;
			}
			delay(30);
		}
		//*************************help *******************************************
		if(ButtonB(button_help,para))
		{
			SidePartMove(para->buffer,0);
			HelpBox(para);
			return 2;
		}
	}
}


/******************************************************************************
	功能说明：A类按键检测（经过图标位置换图片，点击触发事件）
	参数说明： 结构体button，按键的信息；
	返回值说明： 返回1表示已经触发事件，0表示没有触发
*******************************************************************************/
char ButtonA(Button btn,GamePara *para,unsigned short color)
{
	char a=0;
	Coord mouse;
	ReadMouse(&mouse.x,&mouse.y,&a);
	MouseCpy(&mouse,para->mouse_buffer);
	MouseShow(&mouse);
	if(IsinRange(mouse,btn.left,btn.top,btn.right,btn.bottom))//当前处于键的坐标范围
	{
		delay(10);
		MouseReshow(&mouse,para->mouse_buffer);           //为了不残留鼠标痕迹
		ReadBtn(btn.left,btn.top,btn.b,color);
		if(a==1)
			return 1;
	}
	else if(!IsinRange(mouse,btn.left,btn.top,btn.right,btn.bottom))
	{
		delay(10);
		MouseReshow(&mouse,para->mouse_buffer);
		ReadBtn(btn.left,btn.top,btn.a,color);
	}
	else
	{
		MouseReshow(&mouse,para->mouse_buffer);
	}
	return 0;
}

/******************************************************************************
	功能说明：B类按键检测（按下键换图片，放开触发事件）
	参数说明： 结构体button，按键的信息；
	返回值说明： 返回1表示已经触发事件，0表示没有触发
*******************************************************************************/
char ButtonB(Button btn,GamePara *para)
{
	char a=0;
	Coord mouse,mouse_old;
	ReadMouse(&mouse.x,&mouse.y,&a);
	MouseCpy(&mouse,para->mouse_buffer);
	MouseShow(&mouse);
	if(a==1&&IsinRange(mouse,btn.left,btn.top,btn.right,btn.bottom))//当前处于键的坐标范围
	{
		mouse_old.x=mouse.x;
		mouse_old.y=mouse.y; //增设一变量使鼠标不留痕迹
		//playmus("music\\but_b.wav",0);
		while(a==1)//处于按下左键状态
		{
			ReadBtn(btn.left,btn.top,btn.b,0);
			delay(100);
			ReadMouse(&mouse.x,&mouse.y,&a);
			if(a==0) //放开左键
			{
				MouseReshow(&mouse_old,para->mouse_buffer);
				ReadBtn(btn.left,btn.top,btn.a,0);
				return 1;
			}
		}
	}
	MouseReshow(&mouse,para->mouse_buffer);	
	return 0;
}
/**************************************************
	功能说明：过关的界面
	参数说明：
	返回值说明：无
*****************************************************/
void FuncWin(GamePara *para)
{
	struct Button button_menu,button_retry,button_next;
	SetShowBegin(0,0);
	SetMouseRange(0,0,800,600);
	SetMousePosition(10,10);
	button_menu.left=226;
	button_menu.top=405;
	button_menu.right=350;
	button_menu.bottom=524;
	strcpy(button_menu.a,"btn\\sidme1.bmp");
	stpcpy(button_menu.b,"btn\\sidme2.bmp");

	button_retry.left=354;
	button_retry.top=405;
	button_retry.right=477;
	button_retry.bottom=524;
	strcpy(button_retry.a,"btn\\retry1.bmp");
	stpcpy(button_retry.b,"btn\\retry2.bmp");
	
	button_next.left=482;
	button_next.top=405;
	button_next.right=598;
	button_next.bottom=524;
	strcpy(button_next.a,"btn\\nexta1.bmp");
	stpcpy(button_next.b,"btn\\nexta2.bmp");
	
	while(1)
	{
	//*****************************菜单 return to menu*********************
		if(ButtonB(button_menu,para))
		{
			para->interface=LEVSEL1;
			para->diretion=0;
			return ;
		}
	//******************************重来 retry**********************************
		if(ButtonB(button_retry,para))
		{
			para->diretion=1;
			return ;
		}
	//******************************下一关 next level***************************
		if(ButtonB(button_next,para))
		{
			para->diretion=1;
			if(para->interface<16)
				para->interface+=1;
			return ;
		}
	}
}
/**************************************************
	功能说明：闯关失败的界面
	参数说明：
	返回值说明：无
*****************************************************/
void FuncFailed(GamePara *para)
{
	struct Button button_menu,button_retry;
	SetShowBegin(0,0);
	SetMouseRange(0,0,800,600);
	SetMousePosition(10,10);
	ReadBMP16(210,0,"body/failed.bmp"); 
	//*********************按键信息 ***********************
	button_menu.left=245;
	button_menu.top=405;
	button_menu.right=361;
	button_menu.bottom=525;
	strcpy(button_menu.a,"btn\\sidme1.bmp");
	stpcpy(button_menu.b,"btn\\sidme2.bmp");

	button_retry.left=472;
	button_retry.top=405;
	button_retry.right=589;
	button_retry.bottom=524;
	strcpy(button_retry.a,"btn\\retry1.bmp");
	stpcpy(button_retry.b,"btn\\retry2.bmp");

	while(1)
	{
		//*****************************返回到关卡选择菜单 return to menu*********************
		if(ButtonB(button_menu,para))
		{
			para->interface=LEVSEL1;
			para->diretion=0;
			return ;
		}
	//******************************重来 retry**********************************
		if(ButtonB(button_retry,para))
		{
			para->diretion=0;
			return ;
		}
	}
}
/**************************************************
	功能说明：按退出键是弹出的对话框
	参数说明：GamePara *para 
	返回值说明：无
*****************************************************/
void ExitBox(GamePara *para)
{
	Button button_yes,button_no;
	//*********************yes按键信息 ***********************
	button_yes.left=480;
	button_yes.top=335;
	button_yes.right=581;
	button_yes.bottom=431;
	strcpy(button_yes.a,"btn\\yes2.bmp");
	stpcpy(button_yes.b,"btn\\yes2.bmp");
	//*********************no按键信息 ***********************
	button_no.left=251;
	button_no.top=335;
	button_no.right=352;
	button_no.bottom=431;
	strcpy(button_no.a,"btn\\no2.bmp");
	stpcpy(button_no.b,"btn\\no2.bmp");

	while(1)
	{
		//********************exitbox yes***************************
		if(ButtonB(button_yes,para))
		{
			free(para->mouse_buffer);
			MouseReset();
			ReturnMode();
			exit(1);
		}
		//***********************exitbox cancle******************************
		if(ButtonB(button_no,para))
		{
			ReadBtn(225,225,"btn\\box1.bmp",0);
			return ;
		}
	}
}

/**************************************************
	功能说明：按help键是弹出的对话框
	参数说明：GamePara *para 
	返回值说明：无
*****************************************************/
void HelpBox(GamePara *para)
{
	Button button_next,button_no;
	unsigned int i=1;
	char s[15];
	HelpMove(para->buffer,1);
	ReadBtn(225,225,"btn\\tips1.bmp",0xd3);
	//*********************next按键信息 ***********************
	button_next.left=335+225;
	button_next.top=166+225;
	button_next.right=365+225;
	button_next.bottom=196+225;
	strcpy(button_next.a,"btn\\n1.bmp");
	stpcpy(button_next.b,"btn\\n2.bmp");
	//*********************x按键信息 ***********************
	button_no.left=345+225;
	button_no.top=225;
	button_no.right=387+225;
	button_no.bottom=38+225;
	strcpy(button_no.a,"btn\\close.bmp");
	stpcpy(button_no.b,"btn\\close.bmp");

	while(1)
	{
		//********************helpbox next***************************
		if(i<6)
		{
			if(ButtonB(button_next,para))
			{
				i++;
				sprintf(s,"btn\\tips%d.bmp",i);
				ReadBtn(225,225,s,0xd3);

			}	
		}
		else
		{
			 ReadBtn(335+225,166+225,"btn\\n3.bmp",0xd3);
		}
		//***********************helpbox cancle******************************
		if(ButtonB(button_no,para))
		{
			HelpMove(para->buffer,0);
			return ;
		}
	}
}




