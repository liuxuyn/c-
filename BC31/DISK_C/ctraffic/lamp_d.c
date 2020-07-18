/*************************************************************
*           *���ļ�Ϊ���ֿڽ�ͨ�Ŀ���                         *
*           *���ߣ�����                                      *
*           *�����޸�ʱ�䣺2011.11.4                         *
**************************************************************/

#include <graphics.h>
#include "all.h"
#include "lamp_d.h"
    
/**********************************************************
*��������void lighten_lamp_d                              *
*���ܣ����ֿ�ִ�н�ͨ����ɫ�л��ĺ���                      *
*������plΪ��ͨ�ƽṹ�����׵�ַ��kΪ�л��ı�ţ�            *
*      colorΪ�л�����ɫ                                   *
************************************************************/
void lighten_lamp_d(struct LAMP *pl,int k,int color)
{
    //sc��ʾֱ�еƵ���ɫ��lc��ʾ��Ƶ���ɫ
    switch(k)//��ʼɫ���Ǻ�ƣ�k�ǵƵ�flag��־�������л�Ϊcolorָʾ����ɫ
    {
        case 1:
                pl->sc=(pl+1)->sc=color;//����ֱ��
                (pl+1)->lc=(pl+2)->lc=RED;//��������Ϊ���
                break;

        case 2: 
                (pl+1)->lc=color;// ��������
                pl->sc=(pl+1)->sc=RED;//����ֱ��Ϊ���
                (pl+2)->lc=RED;      //������Ϊ���
                break;

        case 3:
                (pl+2)->lc=color;//�ϵ�����
                (pl+1)->sc=pl->sc=RED;//����ֱ��Ϊ���
                (pl+1)->lc=RED;//��������Ϊ���
                break;

        default:
                break;
    }
}

/**********************************************************
*��������void control_norlamp_d                           *
*���ܣ����ֿ���ͨ����ģʽ�Ľ�ͨ�ƵĿ��ƺ���                 *
*������plΪ��ͨ�ƽṹ�����׵�ַ��kΪ�л��ı�ţ�            *
*      colorΪ�л�����ɫ                                   *
************************************************************/
void control_norlamp_d(struct LAMP *pl,int *flag)
{
    static int t=0;
      
    if(*flag==0)                   //lighten��1234�ֱ�Ϊ����ֱ���������ϱ�ֱ���ϱ���
    {
    	++t;//tΪ������
        switch(t)
        {
            case 1:
                    lighten_lamp_d(pl,1,LIGHTGREEN);  //��������ֱ�е�Ϊ�̵�
                    break;
            case TGREEN:
                    lighten_lamp_d(pl,1,YELLOW);      //������ֱ��Ϊ�Ƶ�
                    break;
            case TGREEN+TYELLOW:
                    lighten_lamp_d(pl,2,LIGHTGREEN);  //���������ת��Ϊ��ɫ
                    break;
            case 2*TGREEN+TYELLOW:
                    lighten_lamp_d(pl,2,YELLOW);      //����������Ϊ�Ƶ�
                    break;
            case 2*TGREEN+2*TYELLOW:
                    lighten_lamp_d(pl,3,LIGHTGREEN);  //���ϱ������̵�
                    break;
            case 3*TGREEN+2*TYELLOW: 
                    lighten_lamp_d(pl,3,YELLOW);      //���ϱ�����Ϊ�Ƶ�
                    break;
            case 3*TGREEN+3*TYELLOW:
                    t=0;                              //����������
                    break;
            default: 
                    break;
        }
    }
    if(*flag==1)
        t=0;
}

/**********************************************************
*��������void check_number_d                              *
*���ܣ����ֿڼ�����·�ڳ�����Ŀ�ĺ���                     *
*������ nΪ������Ŀ��pΪ���ṹ������ָ�룬
*             gΪʱ���¼�����׵�ַ                        *
*ע����control_intlamp_d����                               *
************************************************************/
void check_number_d(int n,struct CAR *p,int g[])
{
    int i=0;
    int c[4]={0,0,0,0},a[3]={0,0,0}; 
    int lx[4]={BXO1-2*RY-RR-20*D,BXO1-2*RY-RR,BXO1+2*RY+RR,BXO1+2*RY+RR+20*D};
    int ly[2]={BYO1+2*RX+RR,BYO1+2*RX+RR+20*D};//̽����޴���
	
    for(i=0;i<n;i++)
    {
        switch((p+i)->justment)
        {
            //�㷨�����������μ�����ĸ�·�ڣ�Ȼ������Ӧ���������ۼ�
            case 11:
                    if( ( (p+i)->x>lx[2] )&&( (p+i)->x<lx[3] ) )
                        c[0]++;
                    break;
            case 31:
                    if( ( (p+i)->x<lx[1] )&&( (p+i)->x>lx[0] ))
                        c[1]++;
                    break;
            case 12:
                    if( ( (p+i)->x>lx[2] )&&( (p+i)->x<lx[3] ))
                        c[2]++;
                    break;
            case 22:
                    if( ( (p+i)->y>ly[0] )&&( (p+i)->y<ly[1] ))
                        c[3]++;
                    break;
        }
    }
    if(c[0]>c[1])  
        a[0]=c[0];
    else       
        a[0]=c[1];
    a[1]=c[2];
    a[2]=c[3];

    for(i=0;i<3;i++)
    {
        if(a[i]==0)  g[i]=0;
        if((a[i]>0)&&(a[i]<=LEVEL1))
            g[i]=TGREEN-REDUCE;
        if((a[i]>LEVEL1)&&(a[i]<=LEVEL2) )
            g[i]=TGREEN;
        if((a[i]>LEVEL2)&&(a[i]<=LEVEL3) )
            g[i]=TGREEN+DELAY;				
    }
}

/**********************************************************
*��������void control_intlamp_d                           *
*���ܣ����ֿ����ܷ���ģʽ�Ľ�ͨ�ƿ��ƺ���                   *
*������plΪ��ͨ�ƽṹ�����׵�ַ��nΪ����������            *
*      gʱ���¼�����׵�ַ��flag�����־λ                  *
*ע����intell����                                          *
************************************************************/
void control_intlamp_d(struct CAR *p,int n,struct LAMP *pl,int g[],int *flag)
{
    static int t=0;		      
    //tΪ������
    ++t;
     
    if(t==1)
    {	
        check_number_d(n,p,g); 
        lighten_lamp_d(pl,1,LIGHTGREEN);//��������ֱ�е�Ϊ�̵�
    }    
    if(t==g[0])
        lighten_lamp_d(pl,1,YELLOW); //������ֱ��Ϊ�Ƶ�

    if(t==(g[0]+TYELLOW))
        lighten_lamp_d(pl,2,LIGHTGREEN);//����������Ϊ�̵�
					  
    if(t==(g[0]+TYELLOW+g[1]))
        lighten_lamp_d(pl,2,YELLOW);//����������Ϊ�Ƶ�

    if(t==(g[0]+2*TYELLOW+g[1]))
        lighten_lamp_d(pl,3,LIGHTGREEN);//���ϱ�����Ϊ�̵�
					
    if(t==(g[0]+2*TYELLOW+g[1]+g[2]))
        lighten_lamp_d(pl,3,YELLOW);//���ϱ�����Ϊ�Ƶ�	
				
    if(t==(g[0]+3*TYELLOW+g[1]+g[2]))           
        t=0;                       //ѭ����һ�Σ���ʱ������

    if(*flag==1)
        t=0;                       //��ʱ������
}


