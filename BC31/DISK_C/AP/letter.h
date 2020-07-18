#ifndef _letter_h_
#define _letter_h_
/*********显示游戏字符********/
void ShowScore(int s,GamePara *para);
int GetData(data *s,int n);
int SaveData(data *s,int n);
void ShowOne(data dat,GamePara *para);
void ShowHighScore(int,GamePara *para);
int GetLevStar(int level);
int GetLevNum();
void ResetHighScore();
#endif