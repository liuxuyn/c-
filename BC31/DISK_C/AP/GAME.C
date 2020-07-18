#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<time.h>
#include<bios.h>
#include<stdlib.h>
#include"head.h"
#include"SVGA.H"
#include"mouse.h"
#include"letter.h"
#include"common.h"
#include"debug.h"
#include"shape.h"
#include"physical.h"
#include"intfa.h"
#include"intfa2.h"
#include"Game.h"



/*************************************8
	功能说明：根据初始化的N个物体开始游�?
	函数说明：a游戏物体数组，para游戏系统常用变量
	返回值说明：无返回�?
****************************/
void begin(struct body*a,GamePara *para)
{
	Coord mouse;
	char b=0,flag=0;
	char str[20],debug[20];
	int i,j,life=3;
	int Press;
	int time=0;
	int count=0,bird=0,score=0;
   //	float angle=0;
   //	int beginx=a[0].x,beginy=a[0].y;
	int left=a[0].x-a[0].r,top=a[0].y-a[0].r,right=a[0].x+a[0].r,bottom=a[0].y+a[0].r;
	Area area;
	area.left=left,area.top=top,area.right=right,area.bottom=bottom;
	//读取area中的背景
	SetMouseRange(0,0,800,600);
	SetMousePosition(0,0);
	SetShowBegin(0,0);
	para->buffer=(short *)malloc(60*60*2);
	if(para->buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function begin");
		getch();
		getch();
		exit(1);
	}
	for(;life>0;life--)
	{
	       //BodyBackGroundCpy(a[0].x-a[0].r,a[0].y-a[0].r,a[0].x+a[0].r,a[0].y+a[0].r,para->buffer);
		b=0;
		area.left=left,area.top=top,area.right=right,area.bottom=bottom;
		HideShape(&a[0]);
		a[0].x=PIGX,
		a[0].y=PIGY,
		a[0].r=25,
		a[0].vx=0,
		a[0].vy=0,
		a[0].type=1;
		for(i=0;i<N;i++)
		{
			if(a[i].flag==1)
			ShowShape(&a[i],para);
		}
		ReadMouse(&mouse.x,&mouse.y,&b);

		DeBug("this is one try\n");
		while(1)
		{
			flag=SidePartCheck(para);
			if(flag==1)
			{
				free(para->buffer);
				return ;
			}
			sprintf(str,"body/pig%d1.bmp",para->pig);
			ReadMouse(&mouse.x,&mouse.y,&b);
			if(MouseDrag(&area,para,str)==1)
			{
				a[0].x=area.left+25;
				a[0].y=area.top+25;
				DeBug("this is break\n");
				break;
			}
			MouseCpy(&mouse,para->mouse_buffer);
			MouseShow(&mouse);
			delay(10);
			MouseReshow(&mouse,para->mouse_buffer);
			ReadMouse(&mouse.x,&mouse.y,&b);
		}
		a[0].move=1;
		a[0].vx=(-(area.left+25)+PIGX)/5;
		a[0].vy=(-(area.top+25)+PIGY)/5;
		sprintf(debug,"vx:%f vy:%f\n",a[0].vx,a[0].vy);
		DeBug(debug);
		time=0 ;
		while(time!=150&&a[0].move==1)
		{
			DeBug("I am shock\n");
			time++;
			count=0 ;
			bird=0;
			for(i=0;i<N;i++)
			{
				if(a[i].flag==0)
				continue;
				else
				count++;
				if(a[i].type==2||a[i].type==3)
				bird++;
				if(a[i].move==1)
				{
				move(&a[i],para);
				}
				CollideEdge(&a[i],para);
				for(j=i;j<N;j++)
				{
					if(i!=j&&a[j].flag==1)
					{
						if(Isshock(&a[i],&a[j]))
						{
							if(IsDestroy(&a[i],&a[j]))
							{
								destroy(&a[j]);
								switch(a[j].type)
								{
									case 2:
									case 3:
									score+=1000;
									break;
									case 4:
									case 5:
									case 6:
									score+=100;
									break;
								}
								ShowScore(score,para);
							}
							shock(&a[i],&a[j]);
						}
					}
				}

			}
			if(bird==0)
			{
				break;
			}
			delay(10);
		}
		if(bird==0)
		{
			Dark();
			if((para->mode1pass==para->interface-9)&&para->mode1pass<7)
				para->mode1pass++;
			win(score+life*500,para);
			free(para->buffer);
			return ;
		}
	}
	if(bird!=0)
	{
		Dark();
		FuncFailed(para);
		free(para->buffer);
		return ;
	}
}/*************************************
	功能说明：游戏初始化
	函数说明：无
	返回值说明：无返回�?
****************************/
void gameinti(int level,struct body *a)
{
	int i;
	switch(level)
	{
	case 1:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=714,a[1].y=304,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=2;
		a[2].x=594,a[2].y=304,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=5;
		a[3].x=488,a[3].y=304,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=5;
		a[4].x=713,a[4].y=402,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=5;
		a[5].x=592,a[5].y=402,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=5;
		a[6].x=486,a[6].y=402,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=5;
		a[7].x=486,a[7].y=481,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=5;
		a[8].x=594,a[8].y=481,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=5;
		a[9].x=716,a[9].y=481,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=5;
	break;
	case 2:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=731,a[1].y=229,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=6;
		a[2].x=731,a[2].y=312,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=6;
		a[3].x=731,a[3].y=397,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=6;
		a[4].x=609,a[4].y=313,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=6;
		a[5].x=609,a[5].y=400,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=6;
		a[6].x=609,a[6].y=485,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=6;
		a[7].x=487,a[7].y=483,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=6;
		a[8].x=487,a[8].y=400,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=2;
		a[9].x=731,a[9].y=485,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=6;
	break ;
	case 3:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=375,a[1].y=308,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=5;
		a[2].x=465,a[2].y=308,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=6;
		a[3].x=375,a[3].y=400,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=5;
		a[4].x=465,a[4].y=405,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=6;
		a[5].x=375,a[5].y=485,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=5;
		a[6].x=465,a[6].y=475,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=6;
		a[7].x=565,a[7].y=460,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=3;
		a[8].x=655,a[8].y=475,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=3;
		a[9].x=745,a[9].y=475,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=3;
		break;
	case 4:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=328,a[1].y=293,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=6;
		a[2].x=503,a[2].y=293,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=6;
		a[3].x=596,a[3].y=293,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=6;
		a[4].x=680,a[4].y=293,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=6;
		a[5].x=383,a[5].y=377,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=7;
		a[6].x=383,a[6].y=465,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=7;
		a[7].x=646,a[7].y=377,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=7;
		a[8].x=646,a[8].y=465,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=7;
		a[9].x=518,a[9].y=465,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=3;
		break;
	case 5:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=501,a[1].y=55,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=4;
		a[2].x=501,a[2].y=138,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=4;
		a[3].x=501,a[3].y=216,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=4;
		a[4].x=501,a[4].y=302,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=4;
		a[5].x=501,a[5].y=381,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=4;
		a[6].x=501,a[6].y=464,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=4;
		a[7].x=670,a[7].y=381,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=2;
		a[8].x=603,a[8].y=464,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=2;
		a[9].x=697,a[9].y=464,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=3;
		break;
	case 6:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=575,a[1].y=180,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=7;
		a[2].x=575,a[2].y=280,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=6;
		a[3].x=575,a[3].y=380,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=6;
		a[4].x=575,a[4].y=480,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=6;
		a[5].x=664,a[5].y=180,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=7;
		a[6].x=664,a[6].y=380,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=3;
		a[7].x=664,a[7].y=480,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=3;
		a[8].x=745,a[8].y=380,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=2;
		a[9].x=745,a[9].y=480,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=2;
		break;
	case 7:
		a[0].x=PIGX,a[0].y=PIGY,
		a[0].r=25,a[0].vx=0,a[0].vy=0,a[0].type=1;
		a[1].x=566,a[1].y=295,
		a[1].r=25,a[1].vx=0,a[1].vy=0,a[1].type=7;
		a[2].x=566,a[2].y=384,
		a[2].r=25,a[2].vx=0,a[2].vy=0,a[2].type=7;
		a[3].x=566,a[3].y=466,
		a[3].r=25,a[3].vx=0,a[3].vy=0,a[3].type=7;
		a[4].x=654,a[4].y=295,
		a[4].r=25,a[4].vx=0,a[4].vy=0,a[4].type=7;
		a[5].x=654,a[5].y=384,
		a[5].r=25,a[5].vx=0,a[5].vy=0,a[5].type=3;
		a[6].x=654,a[6].y=466,
		a[6].r=25,a[6].vx=0,a[6].vy=0,a[6].type=2;
		a[7].x=746,a[7].y=295,
		a[7].r=25,a[7].vx=0,a[7].vy=0,a[7].type=7;
		a[8].x=746,a[8].y=384,
		a[8].r=25,a[8].vx=0,a[8].vy=0,a[8].type=7;
		a[9].x=746,a[9].y=466,
		a[9].r=25,a[9].vx=0,a[9].vy=0,a[9].type=7;
		break;
	}
	BodyLife(a,N);
	for(i=0;i<N;i++)
	{
		a[i].move=0,a[i].flag=1;
	}
}
/*************************************
	功能说明：游戏胜�?
	函数说明：无
	返回值说明：无返回�?
****************************/
void win(int score,GamePara *para)
{
		int star;
		if(score>=3200)
		star=3;
		else if(score>=2100)
		star=2;
		else 
		star=1;
		ReadBtn(210,0,"body/win.bmp",0x5fe);
		switch(star)
		{
			case 3:
			SetShowBegin(0,8);
			ReadBtn(176,144,"body/star1.bmp",0);
			SetShowBegin(0,0);
			delay(200);
			SetShowBegin(0,8);
			ReadBtn(321,115,"body/star2.bmp",0);
			SetShowBegin(0,0);
			delay(200);
			SetShowBegin(0,8);
			ReadBtn(482,143,"body/star3.bmp",0);
			SetShowBegin(0,0);
			break;
			case 2:
			SetShowBegin(0,8);
			ReadBtn(176,144,"body/star1.bmp",0);
			SetShowBegin(0,0);
			delay(200);
			SetShowBegin(0,8);
			ReadBtn(321,115,"body/star2.bmp",0);
			SetShowBegin(0,0);
			break;
			case 1:
			SetShowBegin(0,8);
			ReadBtn(176,144,"body/star1.bmp",0);
			delay(200);
			SetShowBegin(0,0);
			break;
		}
		if(para->interface!=9)
			IsHighScore(para->interface-10,score,para);
		FuncWin(para);
}

/*************************************
	功能说明：获得玩家的姓名
	函数说明：参数有需要改变的字符串的地址
	返回值说明：无返回�?
****************************/
void InputName(char *name)
{
	char c;
	int i=0;
	char str[12];
	int x=400;
	int y=78;
	while(1)
	{
	   //	if(bioskey(0))
		c=getch();
		//如果输入的是26个字�?
		if(i<=8)
		{
		 
			if((c>='A'&&c<='Z')||(c>'a'&&c<='z'))
			{
			//则对应转换为相应字符�?
				sprintf(str,"num2/%c.bmp",c);
				ReadBtn(x,y,str,0x35f);
				x+=20;
				name[i]=c;
				i++;
			}
		}
		if(c==8&&i>0)
		{
			x-=20;
			i--;
			ReadBtn(x,y,"num2/Blank.bmp",0x35f);	
		}
		if(c==13&&i!=0)
		{
			break;
		}
		
		//如果输入退格键则删除上一个字�?
	}
	name[i]='\0';
}
/*************************************
	功能说明：判断是否是最高分
	函数说明：参数有第几关，分数�?
	返回值说明：无返回�?
****************************/
void IsHighScore(int level, int score,GamePara *para)
{
	char name[20];
	data dat[9];
	GetData(dat,9);
	if(dat[level].score<score)
	{
		ReadBtn(480,320,"body/best.bmp",0x35f);
		dat[level].score=score;
		ReadBtn(260,15,"body/inputbox.bmp",34);
		InputName(name);
		strcpy(dat[level].name,name);
		dat[level].type=para->pig;
	}
	SaveData(dat,9);
}

void BodyLife(struct body *a,int BodyNum)
{
	char i;
	for(i=0;i<BodyNum;i++)
	{
		switch(a[i].type)
		{
			case PIG:
			a[i].HP=8;
			break;
			case BIRD1:
			a[i].HP=3;
			break;
			case BIRD2:
			a[i].HP=3;
			break;
			case ICE:
			a[i].HP=2;
			break;
			case STEEL:
			a[i].HP=4;
			break;
			case WOOD:
			a[i].HP=3;
			break;
			case STONE:
			a[i].HP=3;
			break;
		}
	}
}


