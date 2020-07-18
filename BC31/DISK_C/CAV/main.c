#include<stdio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include"mouse.h"
#include"head.h"
#include"menu.h"

void main()
{
	int flag=1;
	FlyingPara Fly;
	Fly.mouse_buffer=(short *)malloc(24*18);
	welcome();
	users1();
	aveinit();
	while(1)
	{
		switch(flag)
		{
			case 1:
				
				flag=menucheck(&Fly);
					break;
			case 2:
					//flag=flying();
					break;
			case 3: 
					return;
		}
	}
	
}