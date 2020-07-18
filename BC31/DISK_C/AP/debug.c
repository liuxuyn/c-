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
#include"debug.h"



/*************************************
	功能说明：debug
	函数说明：
	返回值说明：无返回值
****************************/

void DeBug(char *s)
{
	FILE *fp;
	int i;
	if((fp=fopen("debug.txt","at+"))==NULL)
	{
		printf("can not open file\n");
		getch();
		exit(0);
	}
		fprintf(fp,"%s\n",s);
	fclose(fp);
	
}

void DeBugInti()
{
	FILE *fp;
	int i;
	if((fp=fopen("debug.txt","wt"))==NULL)
	{
		printf("can not open file\n");
		getch();
		exit(0);
	}
	fprintf(fp,"%s\n","\0");
	fclose(fp);
}