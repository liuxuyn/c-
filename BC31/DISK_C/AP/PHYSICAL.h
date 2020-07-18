#ifndef _PHYSICAL_h_
#define _PHYSICAL_h_
#define SCREENX 800
#define SCREENY 600
#define G 4 //定义重力加速度


/*********游戏物理效果函数********/
int IsDestroy(struct body *a,struct body *b);
void destroy(struct body *a);
int Isshock(struct body *a,struct body *b) ;
void shock(struct body *,struct body *);
void move(struct body *a,GamePara *para);
void CollideEdge(struct body* a,GamePara *para);

/*********游戏异常情况坐标重置********/
void reset(struct body *a,int x,int y,GamePara *para);
void resetCC(struct body *a,struct body *b,GamePara *para);

/*********按照物体类型显示图片********/
void ShowShape(struct body*a,GamePara *para);
void HideShape(struct body*a);
#endif