#ifndef _Game_h_
#define _Game_h_

#define N 10 //定义游戏中物体的个数
#define V 20 //定义调试时发射速度
#define G 4 //定义重力加速度
#define PIGX 139
#define PIGY 370
#define  PIG  1
#define  BIRD1  2
#define BIRD2  3
#define ICE    4
#define STEEL 5
#define WOOD  6
#define STONE 7
/*********游戏输赢规则及计分函�?*******/
void gameinti(int ,struct body *);
void begin(struct body *,GamePara *para);
void win(int ,GamePara *para);
void InputName(char *name);
void IsHighScore(int level, int score,GamePara *para);
void BodyLife(struct body *a,int BodyNum);
#endif