#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"head.h"
#include"mouse.h"
#include"sound.h"
#include"SVGA.h"          
#include"mouse.h"
#include"anima.h"

/*******************************************************************************************
	函数说明：此函数用于当屏幕逻辑扫描长度为1600时，ping的移动，
	参数说明： way=0代表向左滑，way=1代表向右滑
				next=1；代表转向第一屏幕，next=2，代表转向第二屏幕  
				第一屏幕第二屏幕只是我自己定义的，就是1600宽扫描的屏的左右边
	返回值说明：无
************************************************************************************************/
void MoveScreen(int way,int next)
{
	int i;
	if(next==2) //to Scrren 2
	{
		if(way==1)
		{
			for(i=1;i<=800;i++)
			{
				SetShowBegin(i,0);
				delay(1);
			}
		}
		else if(way==0)
		{
			for(i=1600;i>=800;i--)
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
			for(i=1;i<=800;i++)
			{
				SetShowBegin(800-i,0);
				delay(1);
			}
		}
		else if(way==1)
		{
			for(i=800;i<=1600;i++)
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
/**************************************************
	功能说明：开始动画
	参数说明：
	返回值说明：无
*****************************************************/
void animation()
{
	int i=2;
	char a=0;
	Coord mouse;
	char s[15];
	//SetShowBegin(800,0);
	while(i<147)
	{
		ReadMouse(&mouse.x,&mouse.y,&a);
		if(a==1||a==2)
			break;
		sprintf(s,"smov\\%d.bmp",i);
		ReadBMP16(0,0,s);
		SetShowBegin(0,0);
		delay(DELAYTIME);
		i++;
		ReadMouse(&mouse.x,&mouse.y,&a);
		if(a==1||a==2)
		{
			SetShowBegin(800,0);
			break;
		}
		sprintf(s,"smov\\%d.bmp",i);
		ReadBMP16(800,0,s);
		SetShowBegin(800,0);
		delay(DELAYTIME);
		i++;
	}
	return ;
}



void animation_new(char* filename, float delaytime,unsigned int Base )
{
    FILE *WAVFile;
    WAVEDATA Voice;
    Coord nlog;
	char s[15];
    unsigned char mn;
    long i=0,count=0,rest=0;/*必须用long型*/
    int count_im=2;/*动画的第一幅图画*/
    /*If it can't be opened...*/
    WAVFile = fopen(filename, "rb");
    if (WAVFile == NULL)
    {
        /*..display error message*/
        printf(" %s  fail to find file,press any key to exit",filename);
        getch();
        exit(0);
    }
    /*Return length of file for sound length minus 48 bytes for .WAV header*/
    fseek(WAVFile, 0L, SEEK_END); /*SEEK_SET==0,SEEK_CUR==1,SEEK_END==2*/
    Voice.SoundLength = ftell (WAVFile) - 44;//减去44bytes，即文件表示信息的长度
    fseek(WAVFile, 0L, SEEK_SET);//回到文件头
    /*Check RIFF header*/
    if (Voice.SoundLength >LOADSIZE)
    {
        count = Voice.SoundLength /LOADSIZE; /*load进的音频分成的多少个小音频断的整数部分*/
        rest = Voice.SoundLength %LOADSIZE;  /*小数部分*/
        if (rest != 0)
    	{
			count=count+1;/*计算会load进多少个整体*/
    	}	
        Voice.SoundLength =LOADSIZE;
    }
    else
    {
        count = 1;
        rest = Voice.SoundLength;
    }


    /*Load wave file*/
    for (i=0; i<count; i++)
    {
        ReadMouse(&(nlog.x),&(nlog.y),&mn);
        if (mn!=0) //鼠标按下，退出动画
        {
			if(i%2==0)
			{
				SetShowBegin(800,0);
			}
			 WriteDSP(0xD0,Base);
            break;

        }
        if (i == count -1)
        {
            Voice.SoundLength = rest;/*一个整体一个整体地播放进去，然后当到最后一部分凑不成一个整体时，用rest*/
        }
		if (LoadVoice(&Voice,WAVFile,i))
        {
            /*Start playback*/
            PlayBack (&Voice,count,Base);
            if (i != count -1)
        	{
				DelayTime((float)LOADSIZE/Voice.Frequency*60+delaytime-10);/*注意是float型的*/
				if(count_im<149)
            	{

					if(count_im%2)
					{
						sprintf(s,"smov\\%d.bmp",count_im);
						ReadBMP16(0,0,s);
						SetShowBegin(0,0);
						count_im++;
					}
					else
					{
						sprintf(s,"smov\\%d.bmp",count_im);
						ReadBMP16(800,0,s);
						SetShowBegin(800,0);
						count_im++;
				}
					

				if(count_im==149)
            	{
					WriteDSP(0xD0,Base);/*停止DMA信道的传送，回收总线控制权*/
					break;
            	}
        		
            	}
        	
            }

        }
        /*Stops DMA-transfer*/
        WriteDSP(0xD0,Base);/*停止DMA信道的传送*/
    }


    fclose (WAVFile); 

}



void  movie(char*filename,int time)
{
    unsigned int Base=0;/* 声卡地址*/

    Base=DSP_check();
    animation_new(filename,time,Base);
}                                      