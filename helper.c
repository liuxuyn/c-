#include "helper.h"

void help(int No)//No:41 ���� 42�������� 43���ν���
{
    int wordh=textheight("w"),wordw=textwidth("w");
    imagesave storage;
    storage.local[0]=1;
    storage.local[1]=11;
    storage.local[2]=638;
    storage.local[3]=478;

     if((storage.ibuffer=(unsigned char*)malloc(imagesize(1,11,639,479)))==NULL)
    {
        return 0;
    }
    else
    {
    getimage(1,11,638,478,storage.ibuffer);
    }

    bar_new(1,11,638,478,DARKGRAY,0);

    char *s1="���������Ϣ";
    char *s2="������Ա��λ"
    char *s3="���пƼ���ѧ�˹��������Զ���ѧԺ";
    char *s4="������ ������ ���";
    char *s5="�ó�����c���Կγ������Ŀ"
    char *s6="ˮƽ���� ��ӭ����";
    char *s7="ϣ���˳���Ϊ�����������������";
    char *s8="���̰��»س��ص�������";

    char *x1="�������ֹ��ܽ���";
    char *x2="���� ����ˮƽ��ת����ֱ��ת";
    char *x3="���� ��Ҫ���Ⱥ����������������ű��� ������һ����С���Ҳ�Ҫ����һ����";
    char *x4="�ü� ��Ҫ���Ⱥ���ͼƬ��������Ϊ��ͼƬ��һ���Խ��ߵ����˵�";

    char *y1="���β��ֹ��ܽ���"
    char *y2="��ɢ �ữ �񻯶�������ȼ����ȼ�Խ��Ч��Խ����";
    char *y3="�˾� ����������ͬ���� ��ӭ����";

    switch(No)
    {
        case 41:
            {
                hz48(200,30,630,470,s1,217);
                hz24kaiti(20,100,620,460,s2,217);
                hz24kaiti(20,150,620,460,s3,217);
                hz24kaiti(20,200,620,460,s4,217);
                hz24kaiti(20,250,620,460,s5,217);
                hz24kaiti(20,300,620,460,s6,217);
                hz24kaiti(20,350,620,460,s7,217);
                hz48(200,400,630,470,s8,217);
            }
            break;

        case 42:
            {
                hz48(200,30,630,470,x1,217);
                hz24kaiti(20,100,620,460,x2,217);
                hz24kaiti(20,150,620,460,x3,217);
                hz24kaiti(20,300,620,460,x4,217);
                hz48(200,400,630,470,s8,217);
            }
            break;

        case 43:
            {
                hz48(200,30,630,470,y1,217);
                hz24kaiti(20,100,620,460,y2,217);
                hz24kaiti(20,150,620,460,y3,217);
                hz24kaiti(20,250,620,460,y4,217);
                hz48(200,400,630,470,s8,217);
            }
    }


	while(1)
    {
        mos_pos(&MouseX,&MouseY,&press);
        if(bioskey(1)||mouse_press(1,11,638,478)==1)
        {
            exitmenu(&storage);
            return ;
        }
    }
}
