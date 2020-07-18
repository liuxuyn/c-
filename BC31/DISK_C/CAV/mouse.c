#include<stdio.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include"mouse.h"
#include"head.h"
#include"SVGA.h"
int MouseSave[16][16];    /*���ڱ�����꼴�����ǵ�����*/
int MouseDot[16][16]=   //���������״,����1:��ʾ��������,2:��ʾ���߽�����Χ������ı߽�,0:��ʾ������������  
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,
		0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,
		0,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,
		0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,
		0,2,1,1,1,1,1,2,0,0,0,0,0,0,0,0,
		0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,
		0,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0,
		0,2,1,1,1,1,1,2,2,0,0,0,0,0,0,0,
		0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,
		0,2,1,2,2,1,1,2,0,0,0,0,0,0,0,0,
		0,2,2,0,2,1,1,2,0,0,0,0,0,0,0,0,
		0,0,0,0,0,2,1,1,2,0,0,0,0,0,0,0,
		0,0,0,0,0,2,1,1,2,0,0,0,0,0,0,0,
		0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0 
	};


//��ʼ�����

void MouseReset()     
{
    /*����Ƿ�װ��������̻������*/
	union REGS regs;
	int retcode;
    regs.x.ax=0;
    int86(51,&regs,&regs);
    retcode=regs.x.ax;
    if(retcode==0)
    {
		printf("mouse or mouse driver is absent,please install ");
		getch();
		exit(1);
    }
    return;
}
//�������λ��
void SetMousePosition(int x,int y)
{
	union REGS regs;
    regs.x.ax=4;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(51,&regs,&regs);//������굱ǰ����			 
	return ;
}


	//������걶����ֵ��
	//vΪ��꼴���趨�ı�����ֵ

void SetMouseVelo(int v)
{
	union REGS regs;
    regs.x.ax=0x13;
    regs.x.dx=v;
	int86(51,&regs,&regs);
}


	//���������������ر�,ֵԽ������ƶ��ٶ�Խ�� 
	//int   vx,	������ģ�int   vy	��������

void  MouseSetSpeed(int vx,int vy)
{
	union REGS regs;
	regs.x.ax=0x0f;
	regs.x.cx=vx;
    regs.x.dx=vy;
	int86(51,&regs,&regs);
} 

	//��������ƶ���Χ��
	//int left,int top,int right,int bottom�ֱ�Ϊ������������


void SetMouseRange(int left,int top,int right,int bottom)
{
	 union REGS regs;
	 int retcode,xmin=left,ymin=top,xmax=right,ymax=bottom;
	 /*�趨����ƶ��ı߽�*/
    regs.x.ax=7;
    regs.x.cx=xmin;
    regs.x.dx=xmax;
    int86(51,&regs,&regs);
    regs.x.ax=8;
    regs.x.cx=ymin;
    regs.x.dx=ymax;
    int86(51,&regs,&regs);
}


	//������������ȣ�������걶����ֵ��
	//xΪˮƽ�����ȣ�yΪ��ֱ������,vΪ��꼴���趨�ı�����ֵ

void SetMouseSen(int x,int y)
{
	union REGS regs;
    regs.x.ax=0x1a;
	regs.x.bx=x;
	regs.x.cx=y;
   // regs.x.dx=v;
	int86(51,&regs,&regs);
}

/*
	������λ�úͰ�ť״̬����
	mouse_x��mouse_yΪ������꣬mouse����buttΪ��갸��״̬��1��2,4�ֱ��ʾ���������Ҽ�
*/
void  ReadMouse( int *mouse_x,int *mouse_y,char *mouse_butt )
{
    union REGS regs;
    int x_new,y_new;
    regs.x.ax=3;
    int86(51,&regs,&regs);
    x_new=regs.x.cx;
    y_new=regs.x.dx;
    *mouse_butt=regs.x.bx&0x07;

	/*-----��¼�´�ʱ�µ�����---------*/
    *mouse_x=x_new;
    *mouse_y=y_new;
	
	return ;
}


/*	//��ȡ���״̬,���ò����ˢ��������˸
	
	/*	int * mouseX		����������ַ
		int * mouseY		���������ַ
		int * mButton		��갴��״̬��ַ
	

void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt)
{
	int 	Xx0 = *mouse_x;
	int 	Yy0 = *mouse_y;
	int 	but0 =*mouse_butt;
	union REGS regs;
	/*��ȡ���λ��
	do
	{
		regs.x.ax=3;
		int86(0x33,&regs,&regs);
		*mouse_x =regs.x.cx;
		*mouse_y=regs.x.dx;
		*mouse_butt =regs.x.bx&1;
	}while ((*mouse_x == Xx0)&&(*mouse_y == Yy0)&&	(*mouse_butt== but0));	//������ʾ������������򱳾���ȡ
}*/





void MouseCpy(Coord *CoordXY,short *mouse_buffer)    
{
    int i,j;
    unsigned long pos;
    char OldPage,NewPage;
    short far *VedioBuffer=(short far *)0xA0000000L;
	OldPage=((CoordXY->y)*1600l+(CoordXY->x))/32768;
    NewPage=OldPage;
	SelectPage(NewPage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600l+j+(CoordXY->x);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
                SelectPage(NewPage);
                OldPage=NewPage;
            }
			mouse_buffer[i*16+j]=VedioBuffer[pos%32768];
        }
    }
    return;
}

/*****************************************************************************
	����˵����������򱳾���ȡ��������ʾ
	����˵�����ṹ��˵����SVGA.H��
	����ֵ˵�����޷���ֵ
*****************************************************************************/
void MouseReshow(Coord *CoordXY,short *mouse_buffer)
{
    int i,j;
    char OldPage,NewPage;
    unsigned long pos;
    short far *VedioBuffer=(short far *)0xA0000000L;
	OldPage=((CoordXY->y)*1600l+(CoordXY->x))/32768;
    NewPage=OldPage;
	SelectPage(OldPage);
	for(i=0;i<16;i++)
	{
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600l+j+(CoordXY->x);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
				SelectPage(NewPage);
                OldPage=NewPage;
            }
            VedioBuffer[pos%65536]=mouse_buffer[i*16+j];
        }
    }
    return;
}
/**************************************************************************************
	����˵���������ʾ
	����˵������SVGA��h
	����ֵ˵�����޷���ֵ
**************************************************************************/
void MouseShow(Coord *CoordXY)
{
    int i,j;
    unsigned long pos;
    char OldPage,NewPage;
    short far *VedioBuffer=(short far *)0xA0000000L;
	OldPage=((CoordXY->y)*1600l+(CoordXY->x))/32768;
    NewPage=OldPage;
	SelectPage(OldPage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600l+j+(CoordXY->x);
            NewPage=pos/32768;
            if(OldPage!=NewPage)
            {
                SelectPage(NewPage);
                OldPage=NewPage;
            }
             if(MouseDot[i][j]==1)    /* �����*/
				VedioBuffer[pos%32768]=0xffff;
			 else if(MouseDot[i][j]==2)
				VedioBuffer[pos%32768]=0;
        }
    }
    delay(15);
    return;
}




//ֱ�ӵ��øú������ȫ����ʼ��
void initmouse(Coord *MS)
{
	MS->x=320,MS->y=240;
	MouseReset();
	SetMousePosition(MS->x,MS->y);
	SetMouseRange(0,0,640,480);
	MouseSetSpeed(2,4);
}
/*
void mouseview()
{	
	while(1)
	{	
		while(!kbhit())
		{
			
			ReadMouse(&mouse->x,&mouse->y,&status);
			MouseCpy(mouse,Fly->mouse_buffer);
			MouseShow(mouse);
			delay(10);
			MouseReshow(mouse,Fly->mouse_buffer);
			ReadMouse(&mouse->x,&mouse->y,&status);
		}

	}
}
//ʵ��������ʾ���ƶ���ʱ����(������)
*/