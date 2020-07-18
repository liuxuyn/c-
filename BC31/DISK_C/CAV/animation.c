#include"head.h"
#include"SVGA.h"




void MoveScreen(int way,int next)
{
	int i;
	if(next==2) //to Scrren 2
	{
		if(way==1)
		{
			for(i=1;i<=640;i++)
			{
				SetShowBegin(i,0);
				delay(1);
			}
		}
		else if(way==0)
		{
			for(i=1280;i>=640;i--)
			{
				SetShowBegin(i,0);
				delay(1);
			}
		}
		else
		{
			ReturnMode();
			printf("function MoveScreen(int way,int next) parameter error ");
		}
	}
	else if(next==1)  //to screen 1
	{
		if(way==0)
		{
			for(i=1;i<=640;i++)
			{
				SetShowBegin(640-i,0);
				delay(1);
			}
		}
		else if(way==1)
		{
			for(i=640;i<=1280;i++)
			{
				SetShowBegin(i,0);
				delay(1);
			}
			SetShowBegin(0,0);
		}
		else
		{
			ReturnMode();
			printf("function MoveScreen(int way,int next) parameter error ");
		}
	}
	else
	{
		ReturnMode();
		printf("function MoveScreen(int way,int next) parameter error ");
	}
}