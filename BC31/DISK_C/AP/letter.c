
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
#include"intfa.h"
#include"intfa2.h"


#define ENTER  0x1c0d
#define UP 0x4800
#define DOWN 0x5000

#define PI 3.1415
#define SCREENX 800
#define SCREENY 600
#define N 10 //定义游戏中物体的个数
#define V 20 //定义调试时发射速度
#define PI 3.1415 //第一圆周率
#define G 4 //定义重力加速度
#define PIGX 139
#define PIGY 370
/*********显示游戏字符********/
void ShowScore(int s,GamePara *para);
int GetData(data *s,int n);
int SaveData(data *s,int n);
void ShowOne(data dat,GamePara *para);
void ShowHighScore(int,GamePara *para);
int GetLevStar(int level);
int GetLevNum();
void ResetHighScore();


/*************************************
	功能说明：显示最高分
	函数说明：
	返回值说明：无返回值
****************************/
void ShowHighScore(int page,GamePara *para)
{
	int i;
		
	//data s1[9]={{"NoData",0,1},{"NoData",0,1},{"NoData",0,2},{"NoData",0,3},{"NoData",0,4},{"NoData",0,5},{"NoData",0,6},{"NoData",0,7},{"NoData",0,8}};
	data s2[9];
	
  	///SaveData(s1,9);
	GetData(s2,9);
	for(i=page*3;i<page*3+3;i++)
	ShowOne(s2[i],para);
}
/*************************************
	功能说明：获得当前关数的星星数
	函数说明：
	返回值说明：星星
****************************/
int GetLevStar(int level)
{
		data s2[9];
		int star;
		GetData(s2,9);
		if(s2[level].score>=3200)
		star=3;
		else if(s2[level].score>=2100)
		star=2;
		else if(s2[level].score>=10)
		star=1;
		else
		return 0;
		return star;
}
/*************************************
	功能说明：显示一条记录
	函数说明：
	返回值说明：无返回值
****************************/
void ShowOne(data dat,GamePara *para)
{
	int  x=1250,i=0,a[4]={0};
	static int y=200;
	char str[12];
	x-=50;
	sprintf(str,"body/pig%d1.bmp",dat.type);
	ReadBtn(x,y,str,0xd1d);
	x+=50;
	while(dat.name[i]!='\0')
	{
		sprintf(str,"num2/%c.bmp",dat.name[i]);
		ReadBtn(x,y,str,0x35f);
		x+=20;
		i++;
	}

	y+=40;
	x=1400;
	a[0]=dat.score%10,a[1]=dat.score/10%10,a[2]=dat.score/100%10,a[3]=dat.score/1000;
	for(i=3;i>=0;i--)
	{
		sprintf(str,"num2/%d.bmp",a[i]);
		ReadBtn(x,y,str,0x35f);
		x+=20;
	}
	y+=50;
	if(y>=470)
    y=200;
}
/*************************************
	功能说明：获得当前关数
	函数说明：
	返回值说明：关数
****************************/
int GetLevNum()
{
		data s2[9];
		int i=0;
		GetData(s2,9);
		while(s2[i].score!=0)
		{
			++i;
		}
		return i;
}/*************************************
	功能说明：文件读写
	函数说明：
	返回值说明：无返回值
****************************/

int GetData(data *s,int n)
{
	FILE *fp;
	int i;
	if((fp=fopen("test.txt","rb+"))==NULL)
	{
		printf("can not open file\n");
		getch();
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%s %d %d",s[i].name,&s[i].score,&s[i].type);
	}
	fclose(fp);
}
int SaveData(data *s,int n)
{
	FILE *fp;
	int i;
	if((fp=fopen("test.txt","wb+"))==NULL)
	{
		printf("can not open file\n");
		getch();
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%s %d %d\n",s[i].name,s[i].score,s[i].type);
	}
	fclose(fp);
}
/*************************************
	功能说明：重置最高分
	函数说明：
	返回值说明：无返回值
****************************/
void ResetHighScore()
{
	data s1[9]={{"NoData",0,1},{"NoData",0,1},{"NoData",0,2},{"NoData",0,3},{"NoData",0,4},{"NoData",0,5},{"NoData",0,6},{"NoData",0,7},{"NoData",0,8}};
	SaveData(s1,9);
}

/*************************************
	功能说明：用图片显示s
	函数说明：传入s
	返回值说明：无返回值
****************************/
void ShowScore(int d,GamePara *para)
{
	int a0,a1,a2,a3;
	char *s1=0;
	a3=d%10,a2=d/10%10,a1=d/100%10,a0=d/1000%10;
	ReadBtn(600,2,"num2/score.bmp",0x35f);
	sprintf(s1,"num2/%d.bmp",a3);
	ReadBMP16(780,2,"num2/Blank.bmp");
	ReadBtn(780,2,s1,0x35f);
	sprintf(s1,"num2/%d.bmp",a2);
	ReadBMP16(760,2,"num2/Blank.bmp");
	ReadBtn(760,2,s1,0x35f);
	sprintf(s1,"num2/%d.bmp",a1);
	ReadBMP16(740,2,"num2/Blank.bmp");
	ReadBtn(740,2,s1,0x35f);
	sprintf(s1,"num2/%d.bmp",a0);
	ReadBMP16(720,2,"num2/Blank.bmp");
	ReadBtn(720,2,s1,0x35f);
}