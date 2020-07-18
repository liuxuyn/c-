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
	char mode1pass; //ģʽ1���Ѿ�ͨ���Ĺؿ���
	char interface; //������
	char sound;   //=1��ϵͳ��������=0������
	char diretion; //��Ļ�л�����=1���ң�=0����
	int logwid;	
    short *buffer;
	short *mouse_buffer;  
	int pig;//����Ϸ��ʹ�õ���ı��
}GamePara;/*��Ϸ�������ò�������*/
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
	char a[18];  //ͼƬ·��1
	char b[18];  //ͼƬ·��2
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
} body;/*��Ϸ��ÿһ����������Ĳ���*/

typedef struct node
{
	char name[20];
	int score;
	int type;
}data;

#endif