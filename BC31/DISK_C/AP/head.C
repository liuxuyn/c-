#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<alloc.h>
#include"head.h"
#include"SVGA.h"
#include"mouse.h"
#include"intfa.h"
#include"intfa2.h"
#include"anima.h"
#include"fm.h"
#include"game.h"
void main()
{ 

	struct body a[N]={0};
	GamePara para;
	GameInit(&para);
	//*********************************************************************
	//***********************************************************************
	while(1)
	{
		switch(para.interface)
		{
			case INTERFACE1:            //界面1
				{

					if(para.sound)
						movie("music\\movie.wav",0);
					else
						animation();
					para.interface=INTERFACE2;
					para.diretion=1;

					break;
				}
			case INTERFACE2:			//界面2
				{
					Interface2Init(&para);
					Interface2Check(&para);
					break;
				}
			case ABOUT: 				//关于界面
				{	
					InterfaceAboutInit(&para);
					InterfaceAbout(&para);
					break;
				}
			case HIGH:					//最高分界面
				{
					InterfaceHighInit(&para);
					InterfaceHigh(&para);
					break;
				}
			case MODSEL:
				{
					InterfaceModSelInit(&para);
					InterfaceModSel(&para);
					break;
				}
			case LEVSEL1: 				//模式1关卡选择
				{
					InterfaceLevSelInit(&para);
					InterfaceLevSel(&para);
					break;
				}
			case FREEMODE:  //自由模式
				{
					FreeModeInit();
					if(FreeModeSel(&para,&a)==3)
						begin(a,&para);
					break;
				}
			default :
				{
					
					if(para.interface>=10&&para.interface<=16)
					{
						ReadBMP16(0,0,"body/1.bmp");
						gameinti(para.interface-9,a);
						begin(a,&para);
					}
					else
					{
						ReturnMode();
						printf("there is not this interface");
						getch();
						exit(1);
					}
				}
		
		}

	}

}
