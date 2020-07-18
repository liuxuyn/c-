/****************************************************
*             *本文件为十字口车辆及路灯初始化文件    *
*             *作者：国悦婷                           *
*             *最终修改时间：2011.11.4              *
*****************************************************/

#include <graphics.h>
#include <stdlib.h>
#include "all.h"
#include "init_s.h"
    
/***************************************************
*函数名：void car_init_xy0_s                       *
*功能：十字口设置车的位置                           *
*参数：p为当前车结构首地址，                        *
*      rx、ry、bx、by为车位置限制数组首地址         *
*      state为清零标志位                           *
****************************************************/
void car_init_xy0_s(struct CAR *p,int *limit_rx,int *limit_ry,int *limit_bx,int *limit_by,int state)
{
    static int count[12]={0,0,0,0,0,0,0,0,0,0,0,0};    //12个道口车的数量数组
    int i=0;
    switch(p->justment)
    {
            //50A为第一辆车距停车线的距离   30A为两辆车之间的前后车距
            //A为车辆尺寸比率，车辆绝对长度为25，定位以车辆中心为标准
        case 10: p->y=limit_ry[0];    //在东道最右边向北转弯的直道上
                 p->x=limit_bx[2]+50*A+30*A*count[0];       
                 count[0]++;             //依次往后叠放
                 break;

        case 11: p->y=limit_ry[1];
                 p->x=limit_bx[2]+50*A+30*A*count[1];
                 count[1]++;
                 break;

        case 12: p->y=limit_ry[2];
                 p->x=limit_bx[2]+50*A+30*A*count[2];
                 count[2]++;
                 break;


        case 20: p->x=limit_rx[5];
                 p->y=limit_by[2]+50*A+30*A*count[3];
                 count[3]++;
                 break;

        case 21: p->x=limit_rx[4];
                 p->y=limit_by[2]+50*A+30*A*count[4];
                 count[4]++;
                 break;

        case 22: p->x=limit_rx[3];
                 p->y=limit_by[2]+50*A+30*A*count[5];
                 count[5]++;
                 break;

        case 30: p->y=limit_ry[5];
                 p->x=limit_bx[1]-50*A-30*A*count[6];
                 count[6]++;
                 break;

        case 31: p->y=limit_ry[4];
                 p->x=limit_bx[1]-50*A-30*A*count[7];
                 count[7]++;
                 break;

        case 32: p->y=limit_ry[3];
                 p->x=limit_bx[1]-50*A-30*A*count[8];
                 count[8]++;
                 break;


        case 40: p->x=limit_rx[0];
                 p->y=limit_by[1]-50*A-30*A*count[9];
                 count[9]++;
                 break;

        case 41: p->x=limit_rx[1];
                 p->y=limit_by[1]-50*A-30*A*count[10];
                 count[10]++;
                 break;

        case 42: p->x=limit_rx[2];
                 p->y=limit_by[1]-50*A-30*A*count[11];
                 count[11]++;
                 break;
    }
    if(state<0)
   	for(i=0;i<12;i++)
   	    count[i]=0;
}

/***************************************************
*函数名：void car_init_xy_s                        *
*功能：十字口对车辆所在的车道位置进行初始化的函数    *
*参数：p为当前车结构首地址，                        *
*     state为清零标志位                            *
****************************************************/
int car_init_xy_s(struct CAR *p,int state)
{
    int limit_rx[6],limit_ry[6];    //用于限定车位左右偏移
              //用于运行距离的限定和随机定位的限定
    int limit_bx[4]={BXO-BX/2,BXO-3*RY-RR,BXO+3*RY+RR,BXO+BX/2};
    int	limit_by[4]={BYO-BY/2,BYO-3*RX-RR,BYO+3*RX+RR,BYO+BY/2};            
    int i=0;
    for(i=0;i<6;i++)
    {
        limit_rx[i]=BXO-(5*RY/2)+RY*i;  //y路 也就是南北路车在x方向上的位置限制
        limit_ry[i]=BYO-(5*RX/2)+RX*i;  //x路 也就是东西路车在y方向上的位置限制
    }
    car_init_xy0_s(p,limit_rx,limit_ry,limit_bx,limit_by,state);
    return 1;
}


/***************************************************
*函数名：int car_init_judge_s                      *
*功能：十字口判断出过程控制的参数justment           *
*参数：p为当前车结构首地址，                        *
****************************************************/
int car_init_judge_s(struct CAR *p)
{
    //justment由两位数组成，
    //首位代表当前所处的路径，1234代表东南西北道路；
    //末尾代表将要进行的转向，012分别表示向右中左转的车道

    switch(p->dirt1)
    {

        case 1:                    //车头朝向正西方，即在东一路上
                if(p->dirt2==2) p->justment=12;
                if(p->dirt2==3) p->justment=11;
                if(p->dirt2==4) p->justment=10;
                break;

        case 2:                      //车头朝向正北方，即在南二路上
                if(p->dirt2==1) p->justment=20;
                if(p->dirt2==3) p->justment=22;
                if(p->dirt2==4) p->justment=21;
                break;

        case 3:                      //车头朝向正东方，即在西三路上
                if(p->dirt2==1) p->justment=31;
                if(p->dirt2==2) p->justment=30;
                if(p->dirt2==4) p->justment=32;
                break;

        case 4:                      //车头朝向正南方，即在北四路上
                if(p->dirt2==1) p->justment=42;
                if(p->dirt2==2) p->justment=41;
                if(p->dirt2==3) p->justment=40;
                break;
    }
    return 1;
}

/***************************************************
*函数名：int car_init_dir_random_s                 *
*功能：十字口随机生成车辆转向的函数                 *
*参数：p为当前车结构首地址，                        *
****************************************************/
int car_init_dir_random_s(struct CAR *p)
{
    int a,b;
    a=random(1001);
    b=(a%4)+1;
    p->dirt2=b;
    while((p->dirt1)==(p->dirt2))           //避免dir1和dir2重合
    {
        a=random(1001);
        b=(a%4)+1;
        p->dirt2=b;
    }
    return 1;
}



/***************************************************
*函数名：int single_car_init_s                     *
*功能：十字口初始化车速已定的单个车辆的函数         *
*参数：p为当前车结构首地址，                        *
****************************************************/
int single_car_init_s(struct CAR *p)
{
	p->justment=0;             //初始化车位  用于debug时看是否赋值
	p->alarm=0;                //车前警报设置为空
	p->count=0;                //已经转过的角度             

	car_init_dir_random_s(p);    //由该函数初始化基础参数要转向的路dir2
	car_init_judge_s(p);         //由该函数根据dir1,dir2判断得到所在路口及车道，记录在justment中
	car_init_xy_s(p,1);            //根据以上两个函数得到的参数，进行判断，得到车子的初始位置
	return 1;                  //成功执行

}

/***************************************************
*函数名：int init_car_choice_s                     *
*功能：十字口初始化车角度颜色路函数                *
*参数：p为车结构数组首地址，a为车数量数组首地址      *
****************************************************/
int init_car_choice_s(struct CAR p[],int a[])
{
	int i=0;
	//东路车初始化
	for(i=0;i<a[0];i++)
	{
		p[i].color=LIGHTGREEN;               //东路车是亮绿色
		p[i].dirt1=1;                        //1234分别表示东南西北
		p[i].angle=P/2;                      //车头方向
		single_car_init_s(&p[i]);              //初始化其他参数
	}

	//南路车初始化
	for(i=a[0];i<(a[0]+a[1]);i++)
	{
		p[i].color=LIGHTRED;                //南路车是亮红色
		p[i].dirt1=2;
		p[i].angle=0;
		single_car_init_s(&p[i]);
	}

	//西路车初始化
	for(i=a[0]+a[1];i<(a[0]+a[1]+a[2]);i++)
	{
		//p->flag=0;                         //待用 //为车是否驶出屏幕的标志位
		p[i].color=BLACK;                   //西路车是黑色
		p[i].dirt1=3;
		p[i].angle=3*P/2;
		single_car_init_s(&p[i]);
	}

	//北路车初始化
	for(i=a[0]+a[1]+a[2];i<(a[0]+a[1]+a[2]+a[3]);i++)
	{
		p[i].color=YELLOW;                       //北路车是黄色
		p[i].dirt1=4;
		p[i].angle=P;
		single_car_init_s(&p[i]);
	}

	return 1;
}

/***************************************************
*函数名：void init_car_s                           *
*功能：十字口初始化车总函数                         *
*参数：p为车结构数组首地址，pnum为车数量数组首地址   *
*      n为车数量总数                               *
****************************************************/

void init_car_s(int pnum[],int n,struct CAR p[])
{
	int i,a[4];                  //a[]为保存各路口车数的数组
	int spn=0;
	randomize();
	for(i=0;i<n;i++)             //所有车辆车速初始化
	{
		p[i].speed=(random(1001)%3+1)*RATE;
		if(p[i].speed>=3*RATE)
		{
                    spn++;
                    if(spn>CAR_SPMAX)
                    {
                        p[i].speed=2*RATE;
                        spn=CAR_SPMAX;
                    }
		}
		p[i].std_speed=p[i].speed;
		p[i].flag=0;               //flag==1时表示驶离桌面
		p[i].spflag=0;             //超速标志位
		p[i].cnum=i;
	}

	for(i=0;i<4;i++)              //保存四个路口车数量，防止原数据被修改
	{
	   a[i]=pnum[i];
	}

        init_car_choice_s(p,a);         //除了车辆速度以外的其他数据初始化
}

/***************************************************
*函数名：void init_lamp_s                          *
*功能：十字口初始化交通灯总函数                     *
*参数：lamp为交通灯结构数组首地址                   *
****************************************************/
void init_lamp_s(struct LAMP lamp[])
{
	int i,j;
	
	//用于限定交通灯所在位置的数组
	int lamp_x[4]={BXO+3*RY+RR+H,BXO-3*RY,BXO-3*RY-RR-H,BXO+3*RY};
	int lamp_y[4]={BYO+3*RX,BYO+3*RX+RR+H,BYO-3*RX,BYO-3*RX-RR-H};

	for(j=0;j<4;j++)
	{
		lamp[j].flag=j+1;            //给每个交通灯定下标志号
	}

	for(i=0;i<4;i++)
	{
		lamp[i].rc = LIGHTGREEN;      //右转灯都赋为绿灯
		lamp[i].sc = lamp[i].lc=RED;  //直行灯和左转灯都赋为红灯
		lamp[i].x = lamp_x[i];
		lamp[i].y = lamp_y[i];
	}

}

/***************************************************
*函数名：void car_zero_s                           *
*功能：十字口交通灯清零函数                         *
*参数：p为当前车结构地址                            *
****************************************************/
void car_zero_s(struct CAR *p)
{
	car_init_xy_s(p,-1);
}