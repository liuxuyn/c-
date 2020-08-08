#include "edit.h"

void drawmainpage()
{
    int wordw=textwidth("w"),wordh=textheight("w");
    cleardevice();
    bar_new(1,1,639,479,LIGHTGRAY,0);//页面底色
    rectangle_new(1,1,639,479,DARKGRAY,0);//外框
    rectangle_new(1,1,639,10,DARKGRAY,0);//上栏
    rectangle_new(479,10,639,169,BLACK,0);//信息区边框
    rectangle_new(2,20+wordh,478,478,WHITE,0);//图像编辑区边框

    rectangle_new(619,0,639,10,RED,0);//退出图标
    line_new(624,0,634,10,WHITE,0);
    line_new(624,10,634,0,WHITE,0);
}

int edit()
{
    //bmp文件相关变量定义及初始化
    int height=0,width=0, bicount=0,linebyte=0;//图片高，宽，每像素位数，每行字节数
    char* pixelspace;//定义像素值存储空间；
    BMPHEADER head;//定义文件头存储变量；
    char initaddr[50];//定义初始文件地址
    char aftraddr[50];//定义保存文件地址；
    point a,b;//定义两个点。point结构体中包含此点的x,y坐标信息
    double ratex,ratey;//定义缩放时x，y的缩放比例；
    BITMAPINFOHEADER p;//定义图像信息头的存储变量t

    //其他变量的定义及初始化
    int page=1;//此程序所在页面为1.点击右上角退出按钮进入0页面表示程序关闭
    int flagofopen=0,flagofsave=0;//两个标志量 打开 保存
    int numofclick=0;//鼠标点击次数记录 用于裁剪功能
    int freturn;//返回值暂存
    char rate1[50],rate2[50];//记录两个比例的原始字符串形态
    int wordw=textwidth("w"),wordh=textheight("w");//定义字宽字长
    int direction;//定义方向 用在旋转功能
    Menu mainmenu[4],submenu[4][10],thirdmenu[5][10];//菜单定义
    imagesave storage;//缓冲区定义
    int level;//程度定义 用在三级菜单”程度1~5“”功能-2~2“两部分
    double present;//当前亮度水平记录 在此水平基础上有二级一级变量变暗
    int i,j,k;//计数器定义
    point a[2];

    //预处理
    setmenu(mainmenu,submenu,thirdmenu);
    clrmous(MouseX,MouseY);
    delay(50);

    drawmainpage();
    drawmainmenu(mainmenu);

    //主循环
    while(page==1)
    {
        drawinfo();//信息区编辑函数。
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
                    case 1://主菜单 文件选项
                    {
                        switch(drawsubmenu(submenu,mainmenu[0]))
                        {
                            case 11://打开选项
                                {
                                    if(flagofopen==0)
                                    {
                                        clearpic();//清空图像编辑区函数
                                        if(inputdialog(11,initaddr,&storage)==1)//打开成功（输入合法）
                                        {
                                            打开bmp文件函数(initaddr,&head);
                                            if(判断头文件head信息函数(&head)==1)
                                            {
                                                p=head.infoheader;
                                                height=p.biHeight;
                                                width=p.biWidth;
                                                bicount=p.biBitCount;
                                                linebyte=(width*bicount/8+3)/4*4;
                                                pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                                读取像素区数据函数(pixelspace,linebyte*height,initaddr);
                                                显示图像函数(&head,pixelspace);
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

                            case 12://保存选项
                                {
                                    if(flagofopen!=1) break;
                                    if(inputdialog(12,aftraddr,&storage)==2)
                                    {
                                        flagofsave=保存操作函数返回操作结果(&head,pixelspace,aftraddr);
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

                            case 13://恢复文件 文件已打开时可进行
                                {
                                    if(flagofopen!=1) break;
                                    flagofopen=0;
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;
                                    free(pixelspace);
                                    clearpic();//清空图像编辑区

                                    //重新打开原来文件
                                    打开bmp文件函数(initaddr,&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    读取像素区数据函数(pixelspace,linebyte*height,initaddr);
                                    显示图像函数(&head,pixelspace);
                                    flagofopen=1;
                                }
                                break;

                            case 14://关闭文件
                                {
                                    if(flagofopen!=1) break;
                                    flagofopen=0;
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;
                                    free(pixelspace);
                                    clearpic();//清空图像编辑区
                                }
                                break;
                        }//文件主菜单的次级菜单分支
                    }//文件主菜单

                    case 2: //调整主选项
                    {
                        switch(drawsubmenu(submenu,mainmenu[1]))
                        {
                            case 21://亮度
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thirdmenu,2)-3;
                                    亮度调整函数(&head,pixelspace,level,&present);
                                    clearpic();
                                    展示图片函数(&head,pixelspace);
                                }

                            case 22://旋转
                                {
                                    if(flagofopen!=1) break;
                                    direction=drawthirdmenu(thirdmenu,1);
                                    旋转函数(&head,pixelspace,direction);//此函数内部会把旋转后文件暂存为.//picture//cache//tempicture.bmp
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    打开bmp文件函数(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    读取像素区数据函数(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    显示图像函数(&head,pixelspace);
                                    移除缓存文件函数(".//picture//cache//tempicture.bmp");
                                }
                                break;

                            case 23://镜像
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thirdmenu,3);
                                    镜像函数(&head,pixelspace,level);
                                    clearpic();
                                    展示图片函数(&head,pixelspace);
                                }
                                break;

                            case 24://缩放
                                {
                                    if(flagofopen!=1) break;
                                    //x轴输入判断
                                    freturn=inputdialog(241,rates1,storage);
                                    if(freturn==3)
                                    {
                                    ratex=atof(rates1);
                                    }
                                    else
                                    {
                                        if (freturn==0)//点击取消
                                        {
                                            break;
                                        }
                                        if (freturn==-3)//输入不合法
                                        {
                                            inputdialog(4,rates1,storage);
                                            break;
                                        }
                                    }
                                    //y轴输入判断
                                    freturn=inputdialog(242,rates2,storage);
                                    if(freturn==3)
                                    {
                                    ratey=atof(rates2);
                                    }
                                    else
                                    {
                                        if (freturn==0)//点击取消
                                        {
                                            break;
                                        }
                                        if (freturn==-3)//输入不合法
                                        {
                                            inputdialog(4,rates2,storage);
                                            break;
                                        }
                                    }
                                    //缩放可行判断
                                    if(缩放可行判断函数(&head,ratex,ratey)==0)//裁剪失败
                                    {
                                        inputdialog(4,rates2,storage);
                                        break;
                                    }
                                    //缩放操作
                                    缩放函数(&head,pixelspace,ratex,ratey);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    打开bmp文件函数(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    读取像素区数据函数(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    显示图像函数(&head,pixelspace);
                                    移除缓存文件函数(".//picture//cache//tempicture.bmp");
                                }
                                break;

                            case 25://裁剪
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
                                        clrmous(MouseX,MouseY);//清除鼠标  防止留痕
                                        delay(50);

                                        if (判断裁剪结果函数(&head,a)==1)
                                        {
                                            裁剪函数(&head,pixelspace,a);
                                            clearpic();
                                            free(pixelspace);
                                            width=0;
                                            height=0;
                                            bicount=0;
                                            linebyte=0;

                                            打开bmp文件函数(".//picture//cache//tempicture.bmp",&head);
                                            p=head.infoheader;
                                            height=p.biHeight;
                                            width=p.biWidth;
                                            bicount=p.biBitCount;
                                            linebyte=(width*bicount/8+3)/4*4;
                                            pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                            读取像素区数据函数(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                            显示图像函数(&head,pixelspace);
                                            移除缓存文件函数(".//picture//cache//tempicture.bmp");
                                        }
                                    }
                                }
                                break;
                        }//调整主菜单的次级菜单分支
                    }//调整主菜单

                    case 3://修饰主菜单
                    {
                        switch(drawsubmenu(submenu,mainmenu[2]))
                        {
                            case 31://扩散
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thiremenu,5);
                                    扩散函数(&head,pixelspace,level);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    打开bmp文件函数(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    读取像素区数据函数(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    显示图像函数(&head,pixelspace);
                                    移除缓存文件函数(".//picture//cache//tempicture.bmp");

                                }

                            case 32://柔化
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thiremenu,5);
                                    柔化函数(&head,pixelspace,level);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    打开bmp文件函数(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    读取像素区数据函数(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    显示图像函数(&head,pixelspace);
                                    移除缓存文件函数(".//picture//cache//tempicture.bmp");
                                }

                            case 33://锐化
                                {
                                    if(flagofopen!=1) break;
                                    level=drawthirdmenu(thiremenu,5);
                                    锐化函数(&head,pixelspace,level);
                                    clearpic();
                                    free(pixelspace);
                                    width=0;
                                    height=0;
                                    bicount=0;
                                    linebyte=0;

                                    打开bmp文件函数(".//picture//cache//tempicture.bmp",&head);
                                    p=head.infoheader;
                                    height=p.biHeight;
                                    width=p.biWidth;
                                    bicount=p.biBitCount;
                                    linebyte=(width*bicount/8+3)/4*4;
                                    pixelspace=(unsigned char*)malloc(sizeof(unsigned char)*height*linebyte);
                                    读取像素区数据函数(pixelspace,linebyte*height,".//picture//cache//tempicture.bmp");
                                    显示图像函数(&head,pixelspace);
                                    移除缓存文件函数(".//picture//cache//tempicture.bmp");
                                }

                            case 34://浮雕
                                {
                                    if(flagofopen!=1) break;
                                    浮雕函数(&head,pixelspace);
                                    clearpic();
                                    展示函数(&head,pixelspace);
                                }

                            case 35://滤镜
                                {
                                    if(flagofopen!=1) break;
                                    freturn=drawthirdmenu(thirdmenu,4);
                                    switch(freturn)
                                    {
                                        case 1://反色
                                        {
                                            反色函数(&head,pixelspace);
                                            clearpic();
                                            展示函数(&head,pixelspace);
                                        }
                                        break;

                                        case 2://复古
                                        {
                                            复古函数(&head,pixelspace);
                                            clearpic();
                                            展示函数(&head,pixelspace);
                                        }
                                        break;

                                        case 3://反色
                                        {
                                            反色函数(&head,pixelspace);
                                            clearpic();
                                            展示函数(&head,pixelspace);
                                        }
                                        break;

                                        case 4://反色
                                        {
                                            反色函数(&head,pixelspace);
                                            clearpic();
                                            展示函数(&head,pixelspace);
                                        }
                                        break;

                                        case 5://反色
                                        {
                                            反色函数(&head,pixelspace);
                                            clearpic();
                                            展示函数(&head,pixelspace);
                                        }
                                        break;
                                    }
                                }
                        }//修饰主菜单的次级菜单分支
                    }//修饰主菜单
                    case 4://帮助
                    {
                        switch(drawsubmenu(submenu,mainmenu[3]))
                        {
                            case 41://关于
                                {
                                    help_about();
                                }
                                break;

                            case 42://调整功能介绍
                                {
                                    help_adjust();
                                }
                                break;

                            case 43://修饰功能介绍
                                {
                                    help_decorate();
                                }
                                break;
                        }//帮助主菜单的次级菜单分支
                    }//帮助主菜单
                }//主菜单分支
            }//点击了主菜单判断
        }//循环主菜单

        if(mouse_press(619,0,639,10) == 1)
        {
            page=0;
        }
    }//主循环
    return page;
}//函数
