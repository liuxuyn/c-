#include "menu.h"

void setmenu(Menu *mainmenu, Menu *submenu[4], Menu *thirdmenu[5])
{
    setmainmenu(mainmenu);
    setsubmenu(submenu,mainmenu);
    setthirdmenu(thirdmenu);
}

void setmainmenu(Menu *mainmenu)
{
    int characterlong=0;
    int space=0;
    int i=0,j=0;
    int wordh=textheight("w"),wordw=textwidth("w");
    char *items[]={"文件","调整","修改","帮助"};
    for(i=0;i<4;i++)
    {
        characterlong+=Chinesestrlen(items[i]);
    }
    space=(480/textw-characterlong)/4/2;
    for(i=0;i<4;i++)
    {
        mainmenu[i].item=items[i];
        mainmenu[i].local[0]=120*i+space;
        mainmenu[i].local[1]=15;
        mainmenu[i].local[2]=mainmenu[i]->local[0]+chinesestrelen(items[i])*textw;
        mainmenu[i].local[3]=15+texth;
        mainmenu[i].No=i+1;
    }
}

void drawmainmenu(Menu *mainmenu)
{
    int i=0;
    int left,top,right,bottom;
    int wordw=textwidyh("w"),wordh=textheight("w");
    bar_new(0,10,479,15+texth+5,RED,0);
    for(i=0;i<4;i++)
    {
        left=1+120*i;
        top=10;
        right=left+119;
        bottom=15+texth+5;
        bar_new(left,top,right,bottom,BLACK,0);
    }
    for(i=0;i<4;i++)
    {
        left=mainmenu[i].local[0];
        top=mainmenu[i].local[1];
        hanzi_s(left,top,mainmenu[i]->item,LIGHTGRAY);
    }

}

void nowmainmenu(Menu *mainmenu,int No,int status)
{
    int left,top,right,bottom;
    int wordh=textheight("w");
    left=119+120*(No-1);
    top=10;
    right=left+120;
    bottom=top+10+wordh;
    if(status)
    {
        bar_new(left,top,right,bottom,DARKGRAY,0);
        hanzi_s(mainmenu[No-1].local[0],mainmenu[No-1].local[1],mainmenu[No-1].item,WHITE);
    }else{
        bar_nem(left,top,right,bottom,BLACK,0);
        hanzi_s(mainmenu[No-1].local[0],mainmenu[No-1].local[1],mainmenu[No-1].item,LIGHTGRAY);
    }
}

void setsubmenu(Menu *submenu[4],Menu *mainmenu)
{
    char *subitem1[]={"打开","保存","恢复", "关闭"};
    char *subitem2[]={"亮度","旋转","镜像","缩放","裁剪"};
    char *subitem3[]={"扩散","柔化","锐化","浮雕","滤镜"};
    char *subitem4[]={"关于","调整","修改"};
    char *subitem[5];
    int i,j;
    int wordw=textwidth("w"),wordh=textheight("w");
    for(i=0;i<4;i++){
        switch(i+1)
        {
            case 1:
            for(j=0;subitem1[j]!=NULL;j++)
                strcpy(subitem[j],subitem1[j]);
            break;
            case 2:
            for(j=0;subitem2[j]!=NULL;j++)
                strcpy(subitem[j],subitem2[j]);
            break;
            case 3:
            for(j=0;subitem3[j]!=NULL;j++)
                strcpy(subitem[j],subitem3[j]);
            break;
            case 4:
            for(j=0;subitem4[j]!=NULL;j++)
                strcpy(subitem[j],subitem4[j]);
            break;
        }
        for(j=0;subitem[j]!=NULL;j++){
            submenu[i][j].No=j+1;
            submenu[i][j].item=submenu[j];
            submenu[i][j].local[0]=mainmenu[i]->local[0];
            submenu[i][j].local[1]=20+texth+(10+texth)*(submenu[i][j]->No-1)+5;
            submenu[i][j].local[2]=submenu[i][j]->local[0]+texth;
            submenu[i][j].local[3]=submenu[i][j]->local[1]+chinesestrlen(subitem[j])*textw;
        }
    }
}


int drawsubmenu(Menu *submenu[4],Menu mainmenu)//返回值规则：第a个主菜单的第b个子菜单对应返回值为10*a+b.返回-1说明本次打开子菜单没有执行功能。
{
    int i,j;
    int wordh=textheight("w"),wordw=textheight("w");
    int numofitems=0,No=mainmenu.N0;
    int left,top,right,bottom;
    for(i=0;submenu[No-1][i]!=NULL;i++);
    numofitems=i;
    imagesave storage ;

    if((storage.ibuffer=(unsigned char*)malloc(imagesize(119+120*(No-1),20+wordth,119+120*No,20+wordh+(10+wordh)*numofitems)))==NULL)
    {
        return 0;
    }else{
    getimage(119+120*(No-1),20+wordth,119+120*No,20+wordh+(10+wordh)*numofitems,storage.ibuffer);
    }
    bar_new(119+120*(No-1),20+wordth,119+120*No,20+wordh+(10+wordh)*numofitems,WHITE,0);

    for(i=0;i<numofitems;i++){
        left=submenu[No-1][i]->local[0];
        top=submenu[No-1][i]->local[1];
        hanzi_s(left,top,submenu[No-1][i],BLACK);
    }
    while(1)
    {
        mou_pos(&MouseX,&MouseY,&press);
        for(i=0;i<numofitems;i++)
        {
            left=119+120*(No-1);
            top=20+wordh+(10+wordh)*i;
            right=left+120;
            bottom=top+10+wordh;
            if (mouse_press(left,top,right,bottom)==2)
            {
            nowsubmenu(submenu[No-1],No,i+1,1);
            }else
            {
            nowsubmenu(submenu[No-1],No,i+1,0);
            }
            if(mouse_press(left,top,right,bottom)==1)
            {
                clrmouse(MouseX,MouseY);
                delay(50);
                exitmenu(&storage);
                return 10*No+i+1;
            }else if(mouse_press(left,top,right,bottom)==4)
            {
                clrmouse(MouseX,MouseY);
                delay(50);
                exitmenu(&storage);
                return -1;
            }
        }
    }
}

void exitmenu(imagesave *storage)
{
    int i;
    if(storage->ibuffer != NULL)
	{
		putimage(storage->local[0],storage->local[1],storage->ibuffer,COPY_PUT);
		for(i = 0; i < 4; i ++)
		{
			storage->ibuffer = 0;
		}
		free(storage->ibuffer);	//释放缓存区指针
		storage->ibuffer=NULL;
}

void nowsubmenu(Menu *submenu,int No,int now,int status)//status: 1,表示点击选项，实质是鼠标放在框上不点击；0表示其他鼠标情况
{
    int left,top,right,bottom;
    int wordh=textheight("w"),wordw=textwidth("w");
    left=119+120*(No-1);
    top=20+wordh+(10+wordh)*(now-1);
    right=left+120;
    bottom=top+10+wordh;
    if(status){
        bar_new(left,top,right,bottom,BLUE,0);
        hanzi_s(submenu[now-1].local[0],submenu[now-1].local[1],submenu[now-1].item,WHITE);
    }else{
        bar_new(left,top,right,bottom,WHITE,0);
        hanzi_s(submenu[now-1].local[0],submenu[now-1].local[1],submenu[now-1].item,BLACK);
    }
}
void setthirdmenu(Menu *thirdmenu[5])
{
    char *thirditems1[]={"顺时针","逆时针"};
    char *thirditems2[]={"二级调亮","一级调亮","原亮度","一级变暗","二级变暗"};
    char *thirditems3[]={"一级","二级","三级","四级","五级"};
    char *thirditems4[]={"反色","复古","敬请期待","敬请期待","敬请期待"};
    char *thirditems5[]={"左右","上下"};
    char *thirditems[5];
    int i,j;
    int wordh=textheight("w"),wordw=textwidth("w");
    int space;
    for(i=0;i<5;i++){
        switch(i+1)
        {
            case 1:
                for(j=0;thirditems1[j]!=NULL;j++)
                    strcpy(thirditems[j],thirditems1[j]);
                break;
            case 2:
                for(j=0;thirditems2[j]!=NULL;j++)
                    strcpy(thirditems[j],thirditems2[j]);
                break;
            case 3:
                for(j=0;thirditems3[j]!=NULL;j++)
                    strcpy(thirditems[j],thirditems3[j]);
                break;
            case 4:
                for(j=0;thirditems4[j]!=NULL;j++)
                    strcpy(thirditems[j],thirditems4[j]);
                break;
            case 5:
                for(j=0;thirditems5[j]!=NULL;j++)
                    strcpy(thirditems[j],thirditems5[j]);
                break;
        }
        for(j=0;thirditems[j]!=NULL;j++){
            thirdmenu[i][j]->No=j+1;
            thirdmenu[i][j]->item=thirditems[j];
            space=(160-ChineseStrlen(thirditems[j])*wordw)/(ChineseStrlen(thirditems[j])+1)
            thirdmenu[i][j]->local[0]=539+space;
            thirdmenu[i][j]->local[1]=174+(wordh+10)*j;
            thirdmenu[i][j]->local[2]=639-space;
            thirdmenu[i][j]->local[3]=174+(wordh+10)*j+wordh;
        }
    }
}

int drawthirdmenu(Menu *thirdmenu[5],int No)//输入参数No表示类型。1是旋转方向选项，2是亮度选项，3是镜像选项，4是滤镜选项，5是程度选项。返回的是对应的选项的次序。
{
    int i,j,numofitems;
    int left,top,right,bottom;
    int wordh=textheight("w"),wordw=textwidth("w");
    bar_new(539,169,639,479,DARKGRAY,0);
    imagesave storage;
    storage.local[0]=539;
    storage.local[1]=169;
    storage.local[2]=639;
    storage.local[3]=479;
    if((storage.ibuffer=(unsigned char*)malloc(imagesize(539,169,639,479))==NULL)
    {
        return 0;
    }else{
    getimage(539,169,639,479,storage.ibuffer);
    }

    switch(No)
    {
        case 1://旋转
            for(i=0;thirdmenu[0][i]!=NULL;i++)
            {
                rectangle_new(539,169+i*(10+wordh),639,169+(i+1)*(10+wordh),WHITE,0);
                hanzi_s(thirdmenu[0][i]->local[0],thirdmenu[0][i]->local[1],thirdmenu[0][i]->item,LIGHTGRAY);
            }
            break;
        case 2://亮度
            for(i=0;thirdmenu[1][i]!=NULL;i++)
            {
            rectangle_new(539,169+i*(10+wordh),639,169+(i+1)*(10+wordh),WHITE,0);
            hanzi_s(thirdmenu[1][i]->local[0],thirdmenu[1][i]->local[1],thirdmenu[1][i]->item,LIGHTGRAY);
            }
            break;
        case 3://镜像
            for(i=0;thirdmenu[4][i]!=NULL;i++)
            {
            rectangle_new(539,169+i*(10+wordh),639,169+(i+1)*(10+wordh),WHITE,0);
            hanzi_s(thirdmenu[4][i]->local[0],thirdmenu[4][i]->local[1],thirdmenu[4][i]->item,LIGHTGRAY);
            }
            break;
        case 4://滤镜
            for(i=0;thirdmenu[3][i]!=NULL;i++)
            {
            rectangle_new(539,169+i*(10+wordh),639,169+(i+1)*(10+wordh),WHITE,0);
            hanzi_s(thirdmenu[3][i]->local[0],thirdmenu[3][i]->local[1],thirdmenu[3][i]->item,LIGHTGRAY);
            }
            break;
        case 5://程度
            for(i=0;thirdmenu[2][i]!=NULL;i++)
            {
            rectangle_new(539,169+i*(10+wordh),639,169+(i+1)*(10+wordh),WHITE,0);
            hanzi_s(thirdmenu[2][i]->local[0],thirdmenu[2][i]->local[1],thirdmenu[2][i]->item,LIGHTGRAY);
            }
            break;
    }
    numofitems=i;
    while(1){
        mou_pos(&MouseX,&MouseY,&press);
        for(i=0;i<numofitems;i++){
                left=539;
                top=169+(10+wordh)*i;
                right=639;
                bottom=top+10+wordh;
            if (mouse_press(left,top,right,bottom)==2)
            {
                nowthirdmenu(Menu *thirdmenu[5],No,i+1,1);
            }else{
                nowthirdmenu(Menu *thirdmenu[5],No,i+1,0);
            }
            if (mouse_press(left,top,right,bottom)==1){
                clrmous(MouseX,MouseY);
				delay(20);
				exitmenu(storage);
				return i+1;
            }
            if (mouse_press(left,top,right,bottom)==4){
                clrmous(MouseX,MouseY);
				delay(20);
				exitmenu(storage);
				return 0;
            }
        }
    }

}

void nowthirdmenu(Menu *thirdmenu[5],int No,int now,int status)
{
    int left,top,right,bottom;
    int wordh=textheight("w");
    left=559;
    top=169+(10+wordh)*(now-1);
    right=639;
    bottom=top+10+wordh;
    if(status)
    {
        bar_new(left,top,right,bottom,LIGHTGRAY,0);
        hanzi_s(thirdmenu[No-1][now-1].local[0],thirdmenu[No-1][now-1].local[1],thirdmenu[No-1][now-1].item,WHITE);
    }else{
        bar_new(left,top,right,bottom,DARKGRAY,0);
        hanzi_s(thirdmenu[No-1][now-1].local[0],thirdmenu[No-1][now-1].local[1],thirdmenu[No-1][now-1].item,LIGHTGRAY);
    }
}

