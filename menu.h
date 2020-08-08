#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "common.h"
#include "draw.h"
typedef struct menu
{
    int local[4];
    char *item;
    unsigned int No;
}Menu;
void setmenu(Menu *mainmenu, Menu *submenu[4], Menu *thirdmenu[5]);//�趨�����˵��ļ��ɺ���
void setmainmenu(Menu *mainmenu);
void drawmainmenu(Menu *mainmenu);  //�������˵���
void nowmainmenu(Menu *mainmenu,int No,int status);//�ڳ����ѭ���У�ѭ�������˵���һ�ʼ�����������Ƿ�����������ĳ��󣬸�����Ϊ��Ծ������μ��˵���
void setsubmenu(Menu *submenu[4],Menu *mainmenu);
int drawsubmenu(Menu *submenu[4],Menu mainmenu);//����μ��˵���ѭ������Ƿ����˴μ��˵���ĳһ�����ֵ���򣺵�a�����˵��ĵ�b���Ӳ˵���Ӧ����ֵΪ10*a+b.
//����11�򿪣�12���棬24����ʱ��Ҫ������򣻷���21���ȣ�22��ת��23����31��ɢ��32�񻯣�33�ữ��35�˾���Ҫ�������˵���41��42��43�ǰ���ѡ�������ѡ�����赯���Ի���
//���棬�򿪲����ɹ�ʧ��ʱ������Ӧ��ʾ�򡣷���-1˵�����δ��Ӳ˵�û��ִ�й��ܡ�

void exitmenu(imagesave *storage);//��Ҫ���ڴμ��˵��˳����ָ������ǵ�����
void nowsubmenu(Menu *submenu,int No,int now,int status);//status: 1,��ʾ���ѡ�ʵ���������ڿ��ϲ������0��ʾ����������
void setthirdmenu(Menu *thirdmenu[5]);
int drawthirdmenu(Menu *thirdmenu[5],int No)//�������No��ʾ���͡�1����ת����ѡ�2������ѡ�3�Ǿ���ѡ�4���˾�ѡ�5�ǳ̶�ѡ�����ֵ��1-5������̶ȣ�6��7��һ��������������
//8��ԭ���ȣ�9��10��һ���������䰵��11��12��˳ʱ�룬��ʱ�룻13��14�����£����ҷ�ת��21-25������˾���
void nowthirdmenu(Menu *thirdmenu[5],int No,int now,int status)
#endif // MENU_H_INCLUDED
