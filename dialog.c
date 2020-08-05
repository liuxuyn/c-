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

int istrue(char *input,char *filelocal,int status)//�ж������Ƿ�Ϸ�������status�� 11��12ʱ�ж��ļ�·���Ƿ�Ϸ���241(2)ʱ�жϱ����Ƿ�Ϸ�������ֵ��1��2��3�ֱ�Ϊ��·���Ϸ�������·���Ϸ�����������Ϸ�
//-1��-2��-3��֮��Ӧ��
{
    char filename[50]=".//picture//";
    double rate;
    char *p;
    switch(status)
    {
        case 11:
            strcat(filename,input);
            if(access(filename,4)==0&&input!=NULL&&strcmp(input,"\0")!=0)   //�ļ��ɶ����ļ�����ʵ������
            {
                 return 1;
            }else{
                 return -1;
            }
            break;

        case 12:
            strcat(filename,input);
            if(input!=NULL&&isbmp(input)&&access(filename,0)==-1)   //�ļ�����Ϊ���Һ�׺��bmp���ļ��������ظ�
            {
                strcpy(filelocal,filename);
                clrmous(MouseX,MouseY);//������
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
                if(*p>='0'&&*p<='9'&&*input=='.')       //������һ��С���ҷ�Χ����0~1.5
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

void drawdialog(int No,int local[4])//11,12,241,242ͬfun_No;1����ɹ���2����ʧ�ܣ�3������ʾ��4����ʧ����ʾ��5��ʧ����ʾ
{
    int texth=textheight("w"),textw=textwidth("w");
    bar_new(local[0],local[1],local[2],local[3],LIGHTGRAY,0);
    bar_new(local[0],local[1],local[2],local[1]+3*texth,WHITE,0);
    bar_new(local[0]+2*textw,local[1]+9*texth,local[0]+6*textw,local[1]+11*texth,WHITE,0);
    bar_new(local[0]+10*textw,local[1]+9*texth,local[0]+14*textw,local[1]+11*texth,WHITE,0);
    hanzi_s(local[0]+2*textw+2,local[1]+9*texth+2,"ȷ��",BLACK);
    hanzi_s(local[0]+10*textw+2,local[1]+9*texth+2,"ȡ��",BLACK);

    switch(No)
    {
        case 11:
        case 12:    //�ļ��������
            bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"�������ļ����·��",BLACK);
            break;
        case 241:  //�������������
            bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"����������ű���(С��)",BLACK);
            break;
        case 242:   //���������
            bar_new(local[0]+2*textw,local[1]+5*texth,local[2]-2*textw,local[1]+8*texth,WHITE,0);
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"�����������ű���(С��)",BLACK);
            break;
        case 1:     //����ɹ�
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"��ʾ",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"����ɹ�",BLACK);
            break;
        case 2:     //����ʧ��
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"��ʾ",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"����ʧ��",BLACK);
            break;
        case 3:     //�ü�������ʾ
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"��ʾ",BLACK);
            hz24kaiti(local[0]+textw+2,local[1]+5*texth+2,local[2]-*textw-2,local[1]+8*texth-2,"���ͼƬ�������������Բü�ͼƬ",BLACK);
            break;
        case 4:    //����ʧ����ʾ
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"��ʾ",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"����ʧ��",BLACK);
            break;
        case 5:     //��ʧ��
            hz24kaiti(local[0]+2,local[1]+2,local[2]-2,local[1]+3*texth-2,"��ʾ",BLACK);
            hz24kaiti(local[0]+2*textw+2,local[1]+5*texth+2,local[2]-2*textw-2,local[1]+8*texth-2,"��ʧ��",BLACK);
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

int inputdialog(int func_No,char *filelocal,imagesave *storage)//fun_No: 11,12·�������241�������������242������������� ;
//25�ü���ʾ�� 1����ɹ���2����ʧ�ܣ�3������ʾ��4����ʧ����ʾ��5��ʧ����ʾ
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
    int freturn;                            //�жϷ���ֵ
    int i;                                  //ѭ��������
    int flagofenter=0,flagofinput=0;        //��־��
    int place;                             //�ı�����λ�ü�¼
    int cursorx=local[0]+2*wordw+2;         //���λ�ü�¼

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
            freturn=istrue(input,filelocal,func_No);//����ֵ��1��2��3�ֱ�Ϊ��·���Ϸ�����ʼִ����Ӧ������������·���Ϸ�����������Ϸ�//-1��-2��-3��֮��Ӧ��0��ʾ���������������ֱ���˳�������
            switch(freturn)
            {
                case 0://��ʾ����ȷ��Ҳ�˳��������ط�0ֵ����ʾҪִ�ж�Ӧ����
                    exitdialog(storage);
                    delay(50);
                    return 1;
                    break;

                case 1:                     //�򿪳ɹ��˳��Ի���
                    exitdialog(storage);
                    return 1;
                    break;

                case -1:                    //��ʧ������ʾ���˳��Ի���
                    drawdialog(5,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return -1;
                    }
                    flagofenter=1;
                    break;

                case 2:                     //����ɹ���ʾ���˳�
                    drawdialog(1,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return 2;
                    }
                    flagofenter=1;
                    break;

                case -2:                    //����ʧ�ܡ���ʾ���˳�
                    drawdialog(2,local);
                    if(flagofenter==1)
                    {
                        exitdialog(storage);
                        return 2;
                    }
                    flagofenter=1;
                    break;

                case 3:                     //���ű����Ϸ����˳��Ի���
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
                    freturn=istrue(input,filelocal,func_No);//����ֵ��1��2��3�ֱ�Ϊ��·���Ϸ�������·���Ϸ�����������Ϸ�//-1��-2��-3��֮��Ӧ��0��ʾ���������������ֱ���˳�������
                    switch(freturn)
                    {
                        case 0://��ʾ����ȷ��Ҳ�˳�
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
