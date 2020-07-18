#ifndef _head_h_
#define _head_h_
#define INTERFACE1 1
#define INTERFACE2 2
#define ABOUT 3
#define HIGH 4
#define MODSEL 5
#define LEVSEL1 6
#define LEVSEL2 7
#define FREEMODE 9
typedef struct GamePara
{
	char gamemode;
	char mode1pass; //模式1中已经通过的关卡数
	char interface; //界面编号
	char sound;   //=1则系统有声音，=0则无声
	char diretion; //屏幕切换方向，=1向右，=0向左
	int logwid;	
    short *buffer;
	short *mouse_buffer;  
	int pig;//主游戏中使用的猪的编号
}GamePara;/*游戏环境常用参量变量*/
typedef struct Coord
{
    int x,y;
}Coord;
typedef struct Area
{
	int left,top,right,bottom;
}Area;
typedef struct Button
{
	int top,left,right,bottom;
	char a[18];  //图片路径1
	char b[18];  //图片路径2
} Button;
typedef struct body
{
	double x;
	double y;
	double r;
	double vx;
	double vy;
    int ac;
	int state;
	int move;
	int type;
	int flag;
	int HP;
	char *VIP;
} body;/*游戏中每一个物体所需的参数*/

typedef struct node
{
	char name[20];
	int score;
	int type;
}data;

#endif