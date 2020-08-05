#include "dialog.h"

int isbmp(char *input)
{
    char *bmp=".bmp";
    int i=0;
    char *p=input;
    strlwr(p);
    if(strlen(input)<4)
    {
        return 0;
    }else
    {
        for(i=1;i<=4;i++)
        {
            if(*(p+strlen(input)-i)!=*(bmp-i)) return 0;
        }
    }
    return 1;
}

int istrue(char *input,char *filelocal,int status)//判断输入是否合法函数。status： 11，12时判断文件路径是否合法；241(2)时判断比例是否合法，返回值：1，2，3分别为打开路径合法，保存路径合法，输入比例合法
//-1，-2，-3与之对应；
{
    char filename[50]=".//picture//";
    double rate;
    char *p;
    switch(status)
    {
        case 11:
            strcat(filename,input);
            if(access(filename,4)==0&&input!=NULL&&strcmp(input,"\0")!=0)   //文件可读且文件名有实质内容
            {
                 return 1;
            }else{
                 return -1;
            }
            break;

        case 12:
            strcat(filename,input);
            if(input!=NULL&&isbmp(input)&&access(filename,0)==-1)   //文件名不为空且后缀是bmp且文件不存在重复
            {
                strcpy(filelocal,filename);
                clrmous(MouseX,MouseY);//清除鼠标
                delay(50);
                return 2;
            }else{
            return -2;
            }
            break;

        case 241:
        case 242:
            p=input;
            while(*p)
            {
                if(*p>='0'&&*p<='9'&&*input=='.')       //比例是一个小数且范围符合0~1.5
                    {
                    input++;
                    }else(
                    return -3;
                    )
            }
            rate=atof(input);
            if(rate>0&&rate<=1.5)
            {
                return 3;
            }else {
            return -3;
            }
            break;

        default:
            return 0;
    }
}

void drawcursor(int *cursorx,int local[4])
{
    int wordw=8,wordh=8;
    line_new(*cursorx,local[1]+5*wordh+1,*cursorx,local[1]+8*wordh-1,SOLID_LINE,NORM_WIDTH);
}

void clrcursor(int local[])
{
    int textw=8,texth=8;
    bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
}

void outputtext(int local[],char *input)
{
    int wordh=8,wordw=8;
	setcolor(BLACK);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(local[0]+2*textw+2, coor[1]+5*texth+2, input);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}

int f_backspace(int local[4],int *place,int *cursorx,char *input)
{
    if(place>0)
    {
        *(input+*place-1)='\0';
        clrmous(MouseX,MouseY);
        delay(50);
        (*place)--;
        (*cursorx)-=16;
        clrcursor(local[4]);
        outputtext(local,input);
        drawcursor(cursorx);
    }
    return 1;
}

int f_input(int local[4],int *cursorx,int *place,char word, char *input)
{
    if(place<12)
    {
        clrmous(MouseX,MouseY);
        delay(50);
        input[*place]=word;
        input[*place+1]='\0';
        (*cursorx)+=16;
        (*place)+=1;
        clrcursor(local);
        outputtext(local,input);
        drawcursor(cursorx,local);
    }
    return 1;
}

void drawdialog(int No,int local[4])//11,12,241,242同fun_No;1保存成功；2保存失败；3剪切提示；4缩放失败提示；5打开失败提示
{
    int texth=textheight("w"),textw=textwidth("w");
    bar_new(local[0],local[1],local[2],local[3],LIGHTGRAY,0);
    bar_new(local[0],local[1],local[2],local[1]+3*texth,WHITE,0);
    bar_new(local[0]+2*textw,local[1]+9*texth,local[0]+6*textw,local[1]+11*texth,WHITE,0);
    bar_new(local[0]+10*textw,local[1]+9*texth,local[0]+14*textw,local[1]+11*texth,WHITE,0);
    hanzi_s(local[0]+2*textw+2,local[1]+9*texth+2,"确定",BLACK);
    hanzi_s(local[0]+10*textw+2,local[1]+9*texth+2,"取消",BLACK);

    switch(No)
    {
        case 11:
        case 12:    //文件名输入框
            bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"请输入文件相对路径",BLACK);
            break;
        case 241:  //横轴缩放输入框
            bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"输入横轴缩放比例(小数)",BLACK);
            break;
        case 242:   //纵轴输入框
            bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"输入纵轴缩放比例(小数)",BLACK);
            break;
        case 1:     //保存成功
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"提示",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"保存成功",BLACK);
            break;
        case 2:     //保存失败
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"提示",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"保存失败",BLACK);
            break;
        case 3:     //裁剪操作提示
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"提示",BLACK);
            hz24kaiti(local[0]+textw+2,local[1]+5*texth+2,local[2]-*textw-2,local[1]+8*texth-2,"点击图片左上右下两点以裁剪图片",BLACK);
            break;
        case 4:    //缩放失败提示
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"提示",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"缩放失败",BLACK);
            break;
        case 5:     //打开失败
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"提示",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"打开失败",BLACK);
            break;
    }

}

void exitdialog(imagesive *storage)
{
    int i;
    clrmous(MouseX,MouseY);
    delay(50);
    exitmenu(storage);
    free(storage->ibuffer);
    storage->ibuffer=NULL;
    for(i=;i<4;i++)
    {
        storage->local[i]=0;
    }
    return;
}

int inputdialog(int func_No,char *filelocal,imagesave *storage)//fun_No: 11,12路径输入框；241横轴缩放输入框；242纵轴缩放输入框 ;
//25裁剪提示框 1保存成功；2保存失败；3剪切提示；4缩放失败提示；5打开失败提示
{
    char transport[50]=".//picture//";
    char word;
    char input[50];
    int wordh=textheight("w"),wordw=textwidth("w");
    int numofwordw=480/wordw,numofwordh=640/wordh;
    int local[4];
    local[0]=numofwordw*wordw/2-8*wordw;
    local[1]=numofwordh*wordh/2-6*wordh;
    local[2]=numofwordw*wordw/2+8*wordw;
    local[3]=numofwordh*wordh/2+6*wordh;
    int freturn;                            //判断返回值
    int i;                                  //循环计数器
    int flagofenter=0,flagofinput=0;        //标志器
    int place;                             //文本输入位置记录
    int cursorx=local[0]+2*wordw+2;         //光标位置记录

    for(i=0;i<4;i++)
    {
        storage->local[i]=local[i];
    }
    storage->ibuffer=(unsigned char*)malloc(imagesize(local[0],local[1],local[2],local[3]));
    getimage(local[0],local[1],local[2],local[3],storage->ibuffer);
    drawdialog(func_No,local);

    clrmous(MouseX,MouseY);
    delay(100);

    while(1)
    {
        flagofinput=bioskey(1);
        mou_pos_state(&MouseX,&MouseY,&press);
        if(mouse_press(local[0]+10*textw,local[1]+9*texth,local[0]+14*textw,local[1]+11*texth)==1)
        {
            exitdialog(storage);
            delay(50);
            return 0;
        }
        if(mouse_press(local[0]+2*textw,local[1]+9*texth,local[0]+6*textw,local[1]+11*texth)==1)
        {
            freturn=istrue(input,filelocal,func_No);//返回值：1，2，3分别为打开路径合法（或开始执行相应操作），保存路径合法，输入比例合法//-1，-2，-3与之对应；0表示其他无需后续操作直接退出得类型
            switch(freturn)
            {
                case 0://提示框点击确定也退出，但返回非0值，表示要执行对应操作
                    exitdialog(storage);
                    delay(50);
                    return 1;
                    break;

                case 1:                     //打开成功退出对话框
                    exitdialog(storage);
                    return 1;
                    break;

                case -1:                    //打开失败先提示再退出对话框
                    drawdialog(5,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return -1;
                    }
                    flagofenter=1;
                    break;

                case 2:                     //保存成功提示后退出
                    drawdialog(1,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return 2;
                    }
                    flagofenter=1;
                    break;

                case -2:                    //保存失败。提示后退出
                    drawdialog(2,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return 2;
                    }
                    flagofenter=1;
                    break;

                case 3:                     //缩放比例合法，退出对话框。
                    exitdialog(storage);
                    return 3;
                    break;

                case -3:
                    drawdialog(4,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return -3;
                    }
                    flagofenter=1;
                    break;
            }
        }
        if(flagofinput)
        {
            word=bioskey(0);
            switch(word)
            {
                case ENTER:
                    freturn=istrue(input,filelocal,func_No);//返回值：1，2，3分别为打开路径合法，保存路径合法，输入比例合法//-1，-2，-3与之对应；0表示其他无需后续操作直接退出得类型
                    switch(freturn)
                    {
                        case 0://提示框点击确定也退出
                            exitdialog(storage);
                            delay(50);
                            return 0;
                            break;

                        case 1:
                            exitdialog(storage);
                            return 1;
                            break;

                        case -1:
                            drawdialog(5,local);
                            if(flagofenter==1)
                            {
                                exitdialog(storage);
                                return -1;
                            }
                            flagofenter=1;
                            break;

                        case 2:
                            drawdialog(1,local);
                            if(flagofenter==1)
                            {
                                exitdialog(storage);
                                return 2;
                            }
                            flagofenter=1;
                            break;

                        case -2:
                            drawdialog(2,local);
                            if(flagofenter==1)
                            {
                                exitdialog(storage);
                                return 2;
                            }
                            flagofenter=1;
                            break;

                        case 3:
                            exitdialog(storage);
                            return 3;
                            break;

                        case -3:
                            drawdialog(4,local);
                            if(flagofenter==1)
                            {
                                exitdialog(storage);
                                return -3;
                            }
                            flagofenter=1;
                            break;
                    }
                case BACKSPACE:
                    f_backspace(local,&place,&cursorx,input);
                    break;

                case ESC:
                    exitdialog(storage);
                    return 0;
                    break;

                default:
                    f_input(local,&cursorx,&place,word,input);
                    break;
            }
        }
    }
}
