#include<graphics.h>
#include<fcntl.h>
#include<io.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>


void chinese(char *s,int x,int y,int wd,int Px,int Py,char color) ;


void chinese(char *s,int x,int y,int wd,int Px,int Py,char color)
{
	FILE *fp;
	char buffer[32];
	register m,n,i,j,k;
	unsigned char qh,wh;
	unsigned long offset;
	if((fp=fopen("c:\\cav\\hzk\\hzk16","rb"))==NULL)
	{
		printf("can't open hzk16,please add it");
		getch();
		closegraph();
		exit(0);
	}
	while(*s)
	{
		qh=*s-0xa0;
		wh=*(s+1)-0xa0;
		offset=(94*(qh-1)+(wh-1))*32L;
		fseek(fp,offset,SEEK_SET);
		fread(buffer,32,1,fp);
		for(i=0;i<16;i++)
		for(n=0;n<Px;n++)
		for(j=0;j<2;j++)
		for(k=0;k<8;k++)
		for(m=0;m<Py;m++)
		if((buffer[i*2+j]>>(7-k)&0x1)!=NULL)
			putpixel(x+8*j*Py+k*Py+m,y+i*Px+n,color);
		s+=2;
		x=x+24+wd;
	}
	fclose(fp);
}
