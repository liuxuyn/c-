#ifndef __lamp_d_h__
    #define __lamp_d_h__

/*�������ģʽ�Ľ�ͨ�ƿ��ƺ���(��intell��������)*/
void control_norlamp_d(struct LAMP *pl,int *flag);

/*���ܷ���ģʽ�Ľ�ͨ�ƿ��ƺ���(��intell��������)*/
void control_intlamp_d(struct CAR *p,int n,struct LAMP *pl,int g[],int *flag);

#endif