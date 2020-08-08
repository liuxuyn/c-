#include "edit.h"

void drawmainpage()
{
    int wordw=textwidth("w"),wordh=textheight("w");
    cleardevice();
    bar_new(1,1,639,479,LIGHTGRAY,0);//ҳ���ɫ
    rectangle_new(1,1,639,479,DARKGRAY,0);//���
    rectangle_new(1,1,639,10,DARKGRAY,0);//����
    rectangle_new(479,10,639,169,BLACK,0);//��Ϣ���߿�
    rectangle_new(2,20+wordh,478,478,WHITE,0);//ͼ��༭���߿�

    rectangle_new(619,0,639,10,RED,0);//�˳�ͼ��
    line_new(624,0,634,10,WHITE,0);
    line_new(624,10,634,0,WHITE,0);
}

int edit()
{
    //bmp�ļ���ر������弰��ʼ��
    int height=0,width=0, bicount=0,linebyte=0;//ͼƬ�ߣ���ÿ����λ����ÿ���ֽ���
    char* pixelspace;//��������ֵ�洢�ռ䣻
    BMPHEADER head;//�����ļ�ͷ�洢������
    char initaddr[50];//�����ʼ�ļ���ַ
    char aftraddr[50];//���屣���ļ���ַ��
    point a,b;//���������㡣point�ṹ���а����˵��x,y������Ϣ
    double ratex,ratey;//��������ʱx��y�����ű�����
    BITMAPINFOHEADER p;//����ͼ����Ϣͷ�Ĵ洢����t

    //���������Ķ��弰��ʼ��
    int page=1;//�˳�������ҳ��Ϊ1.������Ͻ��˳���ť����0ҳ���ʾ����ر�
    int flagofopen=0,flagofsave=0;//������־�� �� ����
    int numofclick=0;//�����������¼ ���ڲü�����
    int freturn;//����ֵ�ݴ�
    char rate1[50],rate2[50];//��¼����������ԭʼ�ַ�����̬
    int wordw=textwidth("w"),wordh=textheight("w");//�����ֿ��ֳ�
    int direction;//���巽�� ������ת����
    Menu mainmenu[4],submenu[4][10],thirdmenu[5][10];//�˵�����
    imagesave storage;//����������
    int level;//�̶ȶ��� ���������˵����̶�1~5��������-2~2��������
    double present;//��ǰ����ˮƽ��¼ �ڴ�ˮƽ�������ж���һ�������䰵
    int i,j,k;//����������
    point a[2];

    //Ԥ����
    setmenu(mainmenu,submenu,thirdmenu);
    clrmous(MouseX,MouseY);
    delay(50);

    drawmainpage();
    drawmainmenu(mainmenu);

    //��ѭ��
    while(page==1)
    {
        drawinfo();//��Ϣ���༭������
        for(i=1;i<=4;i++)
        {
            j=i-1;
            mos_pos(&MouseX,&MouseY,&press);
            if(mouse_press(120*j,10,119+120*j,20+wordh)==2||mouse_press(120*j,10,119+120*j,20+wordh)==1)
            {
                nowmainmenu(mainmenu,i,1);
            }
            else
            {
                nowmainmenu(mainmenu,i,0);
            }

            if(mouse_press(120*j,10,119+120*j,20+wordh)==1)
            {
                clrmous(MouseX,MouseY);
                delay(50);
                switch(i)
                {
                    case 1://���˵� �ļ�ѡ��
                    {
                        switch(drawsubmenu(submenu,mainmenu[0]))
                        {
                            case 11://��ѡ��
                                {
                                    if(flagofopen==0)
                                    {
                                        clearpic();//���ͼ��༭������
                                        if(inputdialog(11,initaddr,&storage)==1)//�򿪳ɹ�������Ϸ���
                                        {
                                            ��bmp�ļ�����(initaddr,&head);
                                            if(�ж�ͷ�ļ�head��Ϣ����(&head)==1)
                                            {
                                                p=head.infoheader;
                                                height=p.biHeight;
                                                width=p.biWidth;
                                                bicount=p.biBitCount;
                                                linebyte=(width*bicount/8+3)/4*4;
                                                pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                                ��ȡ���������ݺ���(pixelspace,linebyte*height,initaddr);
                                                ��ʾͼ����(&head,pixelspace);
                                                flagofopen=1;
                                            }
                                            else
                                            {
                                                inputdialog(5,initaddr,&storage);
                                            }
                                        }
                                        else
                                        {
                                            inputdialog(5,initaddr,&storage);
                                        }
                                    }
                                }
                                break;

                            case 12://����ѡ��
                                {
                                    if(flagofopen!=1) break;
                                    if(inputdialog(12,aftraddr,&storage)==2)
                                    {
                                        flagofsave=��������������ز������(&head,pixelspace,aftraddr);
                                        if(flagofsave==1)
                                        {
                                            inputdialog(1,aftraddr,&storage);

                                        }
                                        else
                                        {
                                            inputdialog(2,aftraddr,&storage);
                                        }

                                    }

                                }
                                break;

                            case 13://�ָ��ļ� �ļ��Ѵ�ʱ�ɽ���
                                {
                                    if(flagofopen!=1) break;
                                    flagofopen=0;
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;
                                    free(pixelspace);
                                    clearpic();//���ͼ��༭��

                                    //���´�ԭ���ļ�
                                    ��bmp�ļ�����(initaddr,&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    ��ȡ���������ݺ���(pixelspace,linebyte*height,initaddr);
                                    ��ʾͼ����(&head,pixelspace);
                                    flagofopen=1;
                                }
                                break;

                            case 14://�ر��ļ�
                                {
                                    if(flagofopen!=1) break;
                                    flagofopen=0;
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;
                                    free(pixelspace);
                                    clearpic();//���ͼ��༭��
                                }
                                break;
                        }//�ļ����˵��Ĵμ��˵���֧
                    }//�ļ����˵�

                    case 2: //������ѡ��
                    {
                        switch(drawsubmenu(submenu,mainmenu[1]))
                        {
                            case 21://����
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thirdmenu,2)-3;
                                    ���ȵ�������(&head,pixelspace,level,&present);
                                    clearpic();
                                    չʾͼƬ����(&head,pixelspace);
                                }

                            case 22://��ת
                                {
                                    if(flagofopen!=1) break;
                                    direction=drawthirdmenu(thirdmenu,1);
                                    ��ת����(&head,pixelspace,direction);//�˺����ڲ������ת���ļ��ݴ�Ϊ.//picture//cache//tempicture.bmp
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    ��bmp�ļ�����(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    ��ȡ���������ݺ���(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    ��ʾͼ����(&head,pixelspace);
                                    �Ƴ������ļ�����(".//picture//cache//tempicture.bmp");
                                }
                                break;

                            case 23://����
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thirdmenu,3);
                                    ������(&head,pixelspace,level);
                                    clearpic();
                                    չʾͼƬ����(&head,pixelspace);
                                }
                                break;

                            case 24://����
                                {
                                    if(flagofopen!=1) break;
                                    //x�������ж�
                                    freturn=inputdialog(241,rates1,storage);
                                    if(freturn==3)
                                    {
                                    ratex=atof(rates1);
                                    }
                                    else
                                    {
                                        if (freturn==0)//���ȡ��
                                        {
                                            break;
                                        }
                                        if (freturn==-3)//���벻�Ϸ�
                                        {
                                            inputdialog(4,rates1,storage);
                                            break;
                                        }
                                    }
                                    //y�������ж�
                                    freturn=inputdialog(242,rates2,storage);
                                    if(freturn==3)
                                    {
                                    ratey=atof(rates2);
                                    }
                                    else
                                    {
                                        if (freturn==0)//���ȡ��
                                        {
                                            break;
                                        }
                                        if (freturn==-3)//���벻�Ϸ�
                                        {
                                            inputdialog(4,rates2,storage);
                                            break;
                                        }
                                    }
                                    //���ſ����ж�
                                    if(���ſ����жϺ���(&head,ratex,ratey)==0)//�ü�ʧ��
                                    {
                                        inputdialog(4,rates2,storage);
                                        break;
                                    }
                                    //���Ų���
                                    ���ź���(&head,pixelspace,ratex,ratey);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    ��bmp�ļ�����(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    ��ȡ���������ݺ���(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    ��ʾͼ����(&head,pixelspace);
                                    �Ƴ������ļ�����(".//picture//cache//tempicture.bmp");
                                }
                                break;

                            case 25://�ü�
                                {
                                    if(flagofopen!=1) break;
                                    if(inputdialog(3," ",storage)==1)
                                    {
                                        for(numofclick=0;numofclick<2;numofclick++)
                                        {
                                            mou_pos(&MouseX,&MouseY,&press);
                                            if(flag1==1)
                                            {
                                            information(width,height);
                                            }
                                            if(press==1&&(numofclick==0||(numofclick==1&&(MouseX!=a[0].x||MouseY!=a[0].y))))
                                            {
                                            a[numofclick].x=MouseX;
                                            a[numofclick].y=MouseY;
                                            number++;
                                            }
                                        }
                                        numofclick=0;
                                        clrmous(MouseX,MouseY);//������  ��ֹ����
                                        delay(50);

                                        if (�жϲü��������(&head,a)==1)
                                        {
                                            �ü�����(&head,pixelspace,a);
                                            clearpic();
                                            free(pixelspace);
                                            width=0;
                                            height=0;
                                            bicount=0;
                                            linebyte=0;

                                            ��bmp�ļ�����(".//picture//cache//tempicture.bmp",&head);
                                            p=head.infoheader;
                                            height=p.biHeight;
                                            width=p.biWidth;
                                            bicount=p.biBitCount;
                                            linebyte=(width*bicount/8+3)/4*4;
                                            pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                            ��ȡ���������ݺ���(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                            ��ʾͼ����(&head,pixelspace);
                                            �Ƴ������ļ�����(".//picture//cache//tempicture.bmp");
                                        }
                                    }
                                }
                                break;
                        }//�������˵��Ĵμ��˵���֧
                    }//�������˵�

                    case 3://�������˵�
                    {
                        switch(drawsubmenu(submenu,mainmenu[2]))
                        {
                            case 31://��ɢ
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thiremenu,5);
                                    ��ɢ����(&head,pixelspace,level);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    ��bmp�ļ�����(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    ��ȡ���������ݺ���(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    ��ʾͼ����(&head,pixelspace);
                                    �Ƴ������ļ�����(".//picture//cache//tempicture.bmp");

                                }

                            case 32://�ữ
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thiremenu,5);
                                    �ữ����(&head,pixelspace,level);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    ��bmp�ļ�����(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    ��ȡ���������ݺ���(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    ��ʾͼ����(&head,pixelspace);
                                    �Ƴ������ļ�����(".//picture//cache//tempicture.bmp");
                                }

                            case 33://��
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thiremenu,5);
                                    �񻯺���(&head,pixelspace,level);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    ��bmp�ļ�����(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    ��ȡ���������ݺ���(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    ��ʾͼ����(&head,pixelspace);
                                    �Ƴ������ļ�����(".//picture//cache//tempicture.bmp");
                                }

                            case 34://����
                                {
                                    if(flagofopen!=1) break;
                                    ������(&head,pixelspace);
                                    clearpic();
                                    չʾ����(&head,pixelspace);
                                }

                            case 35://�˾�
                                {
                                    if(flagofopen!=1) break;
                                    freturn=drawthirdmenu(thirdmenu,4);
                                    switch(freturn)
                                    {
                                        case 1://��ɫ
                                        {
                                            ��ɫ����(&head,pixelspace);
                                            clearpic();
                                            չʾ����(&head,pixelspace);
                                        }
                                        break;

                                        case 2://����
                                        {
                                            ���ź���(&head,pixelspace);
                                            clearpic();
                                            չʾ����(&head,pixelspace);
                                        }
                                        break;

                                        case 3://��ɫ
                                        {
                                            ��ɫ����(&head,pixelspace);
                                            clearpic();
                                            չʾ����(&head,pixelspace);
                                        }
                                        break;

                                        case 4://��ɫ
                                        {
                                            ��ɫ����(&head,pixelspace);
                                            clearpic();
                                            չʾ����(&head,pixelspace);
                                        }
                                        break;

                                        case 5://��ɫ
                                        {
                                            ��ɫ����(&head,pixelspace);
                                            clearpic();
                                            չʾ����(&head,pixelspace);
                                        }
                                        break;
                                    }
                                }
                        }//�������˵��Ĵμ��˵���֧
                    }//�������˵�
                    case 4://����
                    {
                        switch(drawsubmenu(submenu,mainmenu[3]))
                        {
                            case 41://����
                                {
                                    help_about();
                                }
                                break;

                            case 42://�������ܽ���
                                {
                                    help_adjust();
                                }
                                break;

                            case 43://���ι��ܽ���
                                {
                                    help_decorate();
                                }
                                break;
                        }//�������˵��Ĵμ��˵���֧
                    }//�������˵�
                }//���˵���֧
            }//��������˵��ж�
        }//ѭ�����˵�

        if(mouse_press(619,0,639,10) == 1)
        {
            page=0;
        }
    }//��ѭ��
    return page;
}//����
