#include<string.h>
#include<dos.h>
#include<IO.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"head.h"
#include"SVGA.h"
#include"check.h"

/********************************************
	功能说明：数组指针存放各种图片路径，用于游戏刚开始时检查各个图片是否齐全
	参数说明：数组指针存放各种图片路径
	返回值说明：
*************************************************/
void BuildPicture(char (*p)[15])
{
	strcpy(p[0],"btn\\about.bmp");
	strcpy(p[1],"btn\\about1.bmp");
	strcpy(p[2],"btn\\about2.bmp");
	strcpy(p[3],"btn\\about3.bmp");
	strcpy(p[4],"btn\\back1.bmp");
	strcpy(p[5],"btn\\back2.bmp");
	strcpy(p[6],"btn\\box1.bmp");
	strcpy(p[7],"btn\\box2.bmp");
	strcpy(p[8],"btn\\no2.bmp");
	strcpy(p[9],"btn\\con1.bmp");
	strcpy(p[10],"btn\\con2.bmp");
	strcpy(p[11],"btn\\exit1.bmp");
	strcpy(p[12],"btn\\exit2.bmp");
	strcpy(p[13],"btn\\help1.bmp");
	strcpy(p[14],"btn\\help2.bmp");
	strcpy(p[15],"btn\\high.bmp");
	strcpy(p[16],"btn\\jie1.bmp");
	strcpy(p[17],"btn\\jie2.bmp");
	strcpy(p[18],"btn\\levon1.bmp");
	strcpy(p[19],"btn\\levon2.bmp");
	strcpy(p[20],"btn\\levsel.bmp");
	strcpy(p[21],"btn\\next.bmp");
	strcpy(p[22],"btn\\play1.bmp");
	strcpy(p[23],"btn\\play2.bmp");
	strcpy(p[24],"btn\\retry1.bmp");
	strcpy(p[25],"btn\\retry2.bmp");
	strcpy(p[26],"btn\\s.bmp");
	strcpy(p[27],"btn\\s1.bmp");
	strcpy(p[28],"btn\\high1.bmp");
	strcpy(p[29],"btn\\high2.bmp");
	strcpy(p[30],"btn\\set1.bmp");
	strcpy(p[31],"btn\\set2.bmp");
	strcpy(p[32],"btn\\sidme1.bmp");
	strcpy(p[33],"btn\\sidme2.bmp");
	strcpy(p[34],"btn\\sidpar.bmp");
	strcpy(p[35],"btn\\sound1.bmp");
	strcpy(p[36],"btn\\sound2.bmp");
	strcpy(p[37],"btn\\sound3.bmp");
	strcpy(p[37],"btn\\sound4.bmp");
	strcpy(p[39],"btn\\star1.bmp");
	strcpy(p[40],"btn\\star2.bmp");
	strcpy(p[41],"btn\\star3.bmp");
	strcpy(p[42],"btn\\win.bmp");
	strcpy(p[43],"btn\\yes2.bmp");
}

/********************************************
	功能说明：游戏刚开始时检查各个图片是否齐全
	参数说明：
	返回值说明：
*************************************************/
void CheckPicture()
{
	char p[44][15];
	char i;
	FILE * fp;
	BuildPicture(p);
	for(i=0;i<44;i++)//
	{//
		fp=fopen(p[i],"rb");//
		if(!FileExists(p[i]))
		{
			ReturnMode();
			printf("\nPicture_%s can not access when is check\n",p[i] );
			delay(1000);
			getch();
			//exit(1);
		}
	}
	if(i>=44)
		printf("picture in folder_btn is integrated\n");
	fclose(fp);
    return;

}

int FileExists(char *filename) 
{ 
  return (access(filename,0) == 0);
}
