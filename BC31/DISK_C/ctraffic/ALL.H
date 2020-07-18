#ifndef __all_h__
    #define __all_h__

/*************键盘操作宏定义******************/
/******功能键******/
#define F1 15104
#define F2 15360
#define F3 15616
#define F4 15872
#define ESC 283
#define ENTER 7181
#define START 14624           //BLANK空格  仿真时开始 
#define PAUSE 14624           //BLANK too
#define REPLAY 4978           //r 键仿真时重播replay
#define BACK 3592             //backspace返回和删除
#define DELETE	21248         
#define LEFT 19200            
#define RIGHT 19712           
#define TAB 3849    
/******数字键******/        
#define ZERO 2864
#define ONE 561
#define TWO 818
#define THREE 1075
#define FOUR 1332
#define FIVE 1589
#define SIX 1846
#define SEVEN 2103
#define EIGHT 2360
#define NINE 2617


/****"return"函数返回值状态****/
#define EXIT   -1  //表示退出


/******win_xy界面初始和结束坐标******/
#define STARTX 0
#define ENDX   639
#define STARTY 0
#define ENDY   479


/*****button_dxdy按钮边缘距离修正值*******/
#define BTDX 3
#define BTDY 2


/************car num车辆数量的宏定义************/
#define CAR_MAX  20      //车辆最大数目
#define CAR_MOREN 12     //车辆初始化默认数据
#define CAR_SPMAX 3      //快速车数目
#define LEVEL1   2       //智能模式车辆检测
#define LEVEL2   4       //**************
#define LEVEL3   6       //**************


/*********road仿真界面路面图像的参数**********/
#define BX 640		//路面图像的总x长
#define BY 352  	//路面图像的总y长
#define BXO  320	//s十字路面中心点x坐标
#define BYO  174	//s十字路面中心点y坐标
#define BXO1  320	//d丁字路面中心点x坐标
#define BYO1  150	//d丁字路面中心点y坐标
#define RX  18		//x轴方向的路的宽度
#define RY  18		//y轴方向的路的宽度
#define RR   15		//转角缓冲区的尺寸
#define FW   40         //仿真路面播放重播按钮宽
#define FH   30         //仿真路面播放重播按钮高


/*************交通灯的宏定义*************/
#define H	 20	//交通灯每个框格的高度
#define W	 20	//交通灯每个框格的宽度
#define TGREEN	 50     //绿灯时间
#define TRED     80 	//红灯时间
#define TYELLOW  30     //黄灯时间
#define REDUCE   30     //智能模式减少时间     
#define DELAY    30     //智能模式延长时间


/**************控制车的宏定义****************/
#define   P  3.1415926       //圆周率
#define   A  1.3             //车子的尺寸比例系数
#define   D  13		     //车子中心到车头车尾的绝对距离
#define   WC  5              //停车线的邻域宽
#define   RATE  3	     //车子的速度比率基准
#define   ALARMDIS 32        //车中心相距的警戒距离
#define   DIS  37            //短警戒距离(*考虑到转角及车身长，这是最长的*)
#define   DIL  74            //长警戒距离


/***********输入框结构************/
typedef struct INPUT_BOX
{
    int bx0;       //首x坐标
    int by0;       //首y坐标
    int blen;      //长
    int bwid;      //宽
    int bn[2];     //存储数据
    int bstate;    //输入框状态
}BOX;


/**********按钮结构***********/
typedef struct BUTTON
{
    int btx1;      //首x坐标
    int bty1;      //首y坐标
    int btx2;      //尾x坐标
    int bty2;      //尾y坐标
    char *btname;  //按钮名字
    char *btmsg;   //提示信息
}BT;


/********交通灯结构***********/
struct LAMP
{
    int x;         //灯框当前x坐标
    int y;         //灯框当前y坐标
    int lc;        //左灯的颜色
    int sc;        //中间灯的颜色
    int rc;        //右灯的颜色
    int flag;      //灯的顺序号	
};


/***************车的结构****************/
struct  CAR
{
    int x;	     //车子中心当前x坐标
    int y;	     //车子中心当前y坐标
    int color;	     //车子颜色
    int cnum;        //车牌号
    int alarm;	     //警戒距离警报
    int dirt1;	     //车子所在的初始路向
    int dirt2;	     //车子转向的路向
    int speed;	     //车子当前速度
    int std_speed;   //车子本来的速度
    int spflag;      //超速标志位
    int justment;    //首位为所在路，次位为所在道
    int count;	     //在转弯时计算记步
    int flag;	     //用于标志车子是否驶出桌面
    double angle;    //车子当前的角度，正北为零度，逆时针
};


/***********时间记录结构***********/
struct TM
{
    int minute;      //分位
    int second;      //秒位
};

#endif