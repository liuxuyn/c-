#include<stdio.h>
#include<alloc.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"
#include"physical.h"
#include"game.h"
#include"intfa2.h"
#include"common.h"
#include"SVGA.h"
#include"mouse.h"
#include"fm.h"

/**************************************************************************
	功能说明：自由模式设置初始化
	参数说明：
	返回值说明：
**************************************************************************/
char FreeModeSel(GamePara *para,struct body *a)
{
	Button button_yes,button_undo,button_menu;
	Area area,areaN[10];
	Coord bobo;
	int BodyNum=0;
	char i;
	char flag=0,flag_undo=0;
	para->buffer=(short *)malloc(60*65*2);
	if(para->mouse_buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function FreeModeSel");
		getch();
		exit(1);
	}
	//***************************************************
	MaterialsAppear(para); //出现选择
	DrewFrame();
	//**************************************************
	button_menu.left=14;
	button_menu.top=533;
	button_menu.right=69;
	button_menu.bottom=583;
	strcpy(button_menu.a,"btn\\menu1.bmp");
	strcpy(button_menu.b,"btn\\menu2.bmp");
	ReadBtn(14,533,"btn\\menu1.bmp",0);//初始化
	//****************************************************
	button_undo.left=76;
	button_undo.top=533;
	button_undo.right=140;
	button_undo.bottom=592;
	strcpy(button_undo.a,"btn\\undo1.bmp");
	strcpy(button_undo.b,"btn\\undo2.bmp");
	ReadBtn(76,533,"btn\\undo1.bmp",0);//初始化
	//*******************************************************
	button_yes.left=141;
	button_yes.top=533;
	button_yes.right=205;
	button_yes.bottom=592;
	strcpy(button_yes.a,"btn\\ok1.bmp");
	strcpy(button_yes.b,"btn\\ok2.bmp");
	ReadBtn(141,533,"btn\\ok1.bmp",0);//初始化
	//*********************************************************
	for(i=0;i<N;i++)
	{
		a[i].move=0,a[i].flag=0;
	}
	a[0].x=PIGX,a[0].y=PIGY,   //zhu
	a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
	a[0].flag=1;
	while(1)
	{
		flag=FreeModeSet(para,&area,&BodyNum);
		if(flag)
		{
			areaN[BodyNum].left=area.left;
			areaN[BodyNum].top=area.top;
			areaN[BodyNum].right=area.right;
			areaN[BodyNum].bottom=area.bottom;
			a[BodyNum+1].x=area.left+25,a[BodyNum+1].y=area.top+25,
			a[BodyNum+1].r=25,a[BodyNum+1].vx=0,a[BodyNum+1].vy=0,a[BodyNum+1].type=flag;
			a[BodyNum+1].flag=1;
			BodyNum++;
			if(BodyNum>1)
				for(flag=1;flag<BodyNum;flag++)   //检查是否区域重叠
				{
					if(Isshock(&a[BodyNum],&a[flag]))
					{
						flag_undo=1;
						break;
					}
					flag_undo=0;

				}
			bobo.x=area.left;
			bobo.y=area.top;
			if(!IsinRange(bobo,350,25,740,450))
			{
				flag_undo=1;
			}
		}
		//***************menu********************
		if(ButtonB(button_menu,para))
		{

			para->interface=LEVSEL1;
			MaterialsDisappear(para);
			para->diretion=0;
			free(para->buffer);
			BodyLife(a,BodyNum);
			return 1;
		}
		//**************undo**********************
		if(ButtonB(button_undo,para)|flag_undo)
		{
			flag_undo=0;
			if(BodyNum)
			{
				a[BodyNum].flag=0;
				BodyNum--;
				BodyBackGroundCpy(1050,50*BodyNum,1100,50*BodyNum+50,para->buffer);
				BodyBackGroundReshow(areaN[BodyNum].left,areaN[BodyNum].top,areaN[BodyNum].right,areaN[BodyNum].bottom,para->buffer);
			}
		}
		//**************yes*****************************
		if(ButtonB(button_yes,para)||BodyNum>=9)
		{
			MaterialsDisappear(para);
			free(para->buffer);
			BodyLife(a,BodyNum);
			DrewFrame();
			return 3;
		}
	}
}
/**************************************************************************
	功能说明：自由模式初始化时判断是否有物体拖出
	参数说明：
	返回值说明：
**************************************************************************/

int FreeModeSet(GamePara *para,Area *area,char * BodyNum)
{
	Area area1[6];
	int i,f=0,BodyType;
	char *pic[6]={"body\\bird111.bmp","body\\bird211.bmp","body\\stone3.bmp","body\\steel4.bmp","body\\ice.bmp","body\\wood.bmp"};
	area1[0].left=18;
	area1[0].top=18+294;
	area1[0].right=73;
	area1[0].bottom=75+294;
	
	area1[1].left=78;
	area1[1].top=17+294;
	area1[1].right=139;
	area1[1].bottom=74+294;
	
	area1[2].left=144;
	area1[2].top=15+294;
	area1[2].right=205;
	area1[2].bottom=75+294;
	
	area1[3].left=18;
	area1[3].top=79+294;
	area1[3].right=72;
	area1[3].bottom=137+294;
	
	area1[4].left=78;
	area1[4].top=79+294;
	area1[4].right=139;
	area1[4].bottom=137+294;
	
	area1[5].left=145;
	area1[5].top=81+294;
	area1[5].right=202;
	area1[5].bottom=136+294;
	
	for(i=0;i<6;i++)
	{
		f=MouseDrag2(&area1[i],para,pic[i]);
		if(f==1)
		{
			BodyBackGroundReshow(1050,50*(*BodyNum),1100,50*(*BodyNum)+50,para->buffer);
			area->left=area1[i].left;
			area->top=area1[i].top;
			area->right=area1[i].right;
			area->bottom=area1[i].bottom;
			switch(i)
			{
				case 0:
					BodyType=BIRD2;
					break;
				case 1:
					BodyType=BIRD1;
					break;
				case 2:
					BodyType=STONE;
					break;
				case 3:
					BodyType=STEEL;
					break;
				case 4:
					BodyType=ICE;
					break;
				case 5:
					BodyType=WOOD;
					break;
				default:
					BodyType=0;
				
			}
			return BodyType;
		}
	}
	return 0;
}
void FreeModeInit()
{
	
	ReadBtn(0,0,"body/1.bmp",0);
	SetShowBegin(0,0);
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
/**************************************************
	功能说明：自由模式下的物品箱弹出
	参数说明：
	返回值说明：无
*****************************************************/
void MaterialsAppear(GamePara *para)
{
	Area area1,area2;
	int i;
	area2.left=0;
	area2.top=0;
	area2.right=433;

	area1.right=219;
	area1.top=0;
	area1.bottom=217;
	for(i=1;i<=219;i+=1)
   	{
   		area2.bottom=i-130;
		area1.left=219-i;
		ReadPartBMP(area1,0,294,"body\\left.bmp",para,0x003f);
  		if(i>=130)
			ReadPartBMP(area2,0,600-i+130,"body\\bottom.bmp",para,0x003f);
 	}
	area2.bottom=89;
	area1.left=0;
	ReadPartBMP(area1,0,294,"body\\left.bmp",para,0x003f);
	ReadPartBMP(area2,0,511,"body\\bottom.bmp",para,0x003f);
}



/**************************************************
	功能说明：自由模式下的物品箱消失
	参数说明：
	返回值说明：无
	左图完全出来之后 左上角（0,600-217-89） 右下角（600-89）
	下图完全出来后 左上角（0,600-89） 右下角（436,600-89）
*****************************************************/
void MaterialsDisappear(GamePara *para)
{
	Area area,area1,area2,area3;
	int i;
	area.left=0;
	area.top=0;
	area.right=434;
	
	area1.right=219;
	area1.top=0;
	area1.bottom=217;
	area2.left=0;
	area2.top=511;
	area2.right=436;
	
	area3.right=219;
	area3.top=294;
	area3.bottom=511;
	for(i=1;i<218;i+=1)
	{
		area3.left=219-i;
		area2.bottom=381+i;
		area1.left=i;
		area.bottom=219-i;
		ReadPartBMP(area3,area3.left,294,"body\\1.bmp",para,0x003f);
		ReadPartBMP(area1,0,294,"body\\left.bmp",para,0x003f);
		if(i>=130)
		{
			ReadPartBMP(area2,0,511,"body/1.bmp",para,0x003f);
			ReadPartBMP(area,0,381+i,"body\\bottom.bmp",para,0x003f);
		}
	}	
	area3.left=0;
	area2.bottom=600;
	ReadPartBMP(area3,area3.left,294,"body/1.bmp",para,0x003f);
	ReadPartBMP(area2,0,511,"body/1.bmp",para,0x003f);
}

void DrewFrame()
{
	Xline(350,25,440,0xffff);
	Xline(350,500,440,0xffff);
	Yline(350,25,475,0xffff);
	Yline(790,25,475,0xffff);
}