/***************************************************************
*                *���ļ�Ϊʮ��·�ڽ�ͨ�ƿ���                    *
*                *���ߣ�������                                 *
*                *�����޸�ʱ�䣺2011.11.4                      *
****************************************************************/

#include <graphics.h>
#include "all.h"
#include "lamp_s.h"

        
/**********************************************************
*��������void lighten_lamp_s                              *
*���ܣ����ֿ�ִ�н�ͨ����ɫ�л��ĺ���                      *
*������plΪ��ͨ�ƽṹ�����׵�ַ��kΪ�л��ı�ţ�            *
*      colorΪ�л�����ɫ                                   *
************************************************************/
void lighten_lamp_s(struct LAMP *pl,int k,int color)
{
        //sc��ʾֱ�еƵ���ɫ��lc��ʾ��Ƶ���ɫ    
    switch(k)//��ʼɫ���Ǻ�ƣ�k�ǵƵ�flag��־�������л�Ϊcolorָʾ����ɫ    
    {
        case 1:
                pl->sc=(pl+2)->sc=color;//ֻ�л�����ֱ��
                pl->lc=(pl+2)->lc=RED;
                (pl+1)->sc=(pl+3)->sc=RED;
                (pl+1)->lc=(pl+3)->lc=RED;
                break;

        case 2: 
                pl->lc=(pl+2)->lc=color;//ֻ�л���������
                pl->sc=(pl+2)->sc=RED;
                (pl+1)->sc=(pl+3)->sc=RED;
                (pl+1)->lc=(pl+3)->lc=RED;
                break;

        case 3:
                (pl+1)->sc=(pl+3)->sc=color;//ֻ�л��ϱ�ֱ��
                (pl+1)->lc=(pl+3)->lc=RED;
                pl->sc=(pl+2)->sc=RED;
                pl->lc=(pl+2)->lc=RED;
                break;

        case 4:
                (pl+1)->lc=(pl+3)->lc=color;//ֻ�л��ϱ�����
                (pl+1)->sc=(pl+3)->sc=RED;
                pl->sc=(pl+2)->sc=RED;
                pl->lc=(pl+2)->lc=RED;
                break;
        default:
                break;
    }
}


/**********************************************************
*��������void control_norlamp_s                           *
*���ܣ����ֿ���ͨ����ģʽ�Ľ�ͨ�ƵĿ��ƺ���                 *
*������plΪ��ͨ�ƽṹ�����׵�ַ��kΪ�л��ı�ţ�            *
*      colorΪ�л�����ɫ                                   *
************************************************************/
void control_norlamp_s(struct LAMP *pl,int *flag)
{
    static int t=0;
      
    if(*flag==0)                       //lighten��1234�ֱ�Ϊ����ֱ���������ϱ�ֱ���ϱ���
    {
    	++t;//tΪ������
    	switch(t)
        {
            case 1:
                    lighten_lamp_s(pl,1,LIGHTGREEN);//��������ֱ�е�Ϊ�̵�
                    break;
            case  TGREEN:
                    lighten_lamp_s(pl,1,YELLOW);//������ֱ��Ϊ�Ƶ�
                    break;
            case TGREEN+TYELLOW:
                    lighten_lamp_s(pl,2,LIGHTGREEN);//���������ת��Ϊ��ɫ
                    break;
            case 2*TGREEN+TYELLOW:
                    lighten_lamp_s(pl,2,YELLOW);//����������Ϊ�Ƶ�
                    break;
            case 2*TGREEN+2*TYELLOW:
                    lighten_lamp_s(pl,3,LIGHTGREEN);//���ϱ�ֱΪ�̵�
                    break;
            case 3*TGREEN+2*TYELLOW:
                    lighten_lamp_s(pl,3,YELLOW);//���ϱ�ֱΪ�Ƶ�
                    break;
            case 3*TGREEN+3*TYELLOW:
                    lighten_lamp_s(pl,4,LIGHTGREEN);//���ϱ�����Ϊ�̵�
                    break;
            case 4*TGREEN+3*TYELLOW:
                    lighten_lamp_s(pl,4,YELLOW);//���ϱ�����Ϊ�Ƶ�
                    break;
            case 4*TGREEN+4*TYELLOW:
                    t=0;//����������
                    break;
            default:
                    break;
        }
    }
    if(*flag==1)
        t=0;
}

/**********************************************************
*��������void check_number_s                              *
*���ܣ����ֿڼ�����·�ڳ�����Ŀ�ĺ���                     *
*������ nΪ������Ŀ��pΪ���ṹ������ָ�룬
*             gΪʱ���¼�����׵�ַ                        *
*ע����control_intlamp_s����                               *
************************************************************/
void check_number_s(int n,struct CAR *p,int g[])
{
    int i=0;
    int c[8]={0,0,0,0,0,0,0,0},a[4]={0,0,0,0}; 
    int lx[4]={BXO-3*RY-RR-20*D,BXO-3*RY-RR,BXO+3*RY+RR,BXO+3*RY+RR+20*D};
    int ly[4]={BYO-3*RX-RR-20*D,BYO-3*RX-RR,BYO+3*RX+RR,BYO+3*RX+RR+20*D};//̽����޴���
	
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
            case 32:
                    if( ( (p+i)->x<lx[1] )&&( (p+i)->x>lx[0] ))
                        c[3]++;
                    break;
            case 21:
                    if( ( (p+i)->y>ly[2] )&&( (p+i)->y<ly[3] ))
                        c[4]++;
                    break;
            case 41:
                    if( ( (p+i)->y<ly[1] )&&( (p+i)->y>ly[0] ))
                        c[5]++;
                    break;
            case 22:
                    if( ( (p+i)->y>ly[2] )&&( (p+i)->y<ly[3] ))
                        c[6]++;
                    break;
            case 42:
                    if( ( (p+i)->y<ly[1] )&&( (p+i)->y>ly[0] ))
                        c[7]++;
                    break;
        }
    }
    for(i=0;i<4;i++)
    {
        if(c[2*i]>c[2*i+1])  
            a[i]=c[2*i];
        else  
            a[i]=c[2*i+1];
    }
    for(i=0;i<4;i++)
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
*��������void control_intlamp_s                           *
*���ܣ�ʮ�ֿ����ܷ���ģʽ�Ľ�ͨ�ƿ��ƺ���                   *
*������plΪ��ͨ�ƽṹ�����׵�ַ��nΪ����������            *
*      gʱ���¼�����׵�ַ��flag�����־λ                  *
*ע����intell����                                          *
************************************************************/
void control_intlamp_s(struct CAR *p,int n,struct LAMP *pl,int g[],int *flag)
{
    static int t=0;		      
    //tΪ������
    ++t;
     
    if(t==1)
    {	
        check_number_s(n,p,g); 
        lighten_lamp_s(pl,1,LIGHTGREEN);//��������ֱ�е�Ϊ�̵�
    }    

    if(t==g[0])
        lighten_lamp_s(pl,1,YELLOW); //������ֱ��Ϊ�Ƶ�
    if(t==(g[0]+TYELLOW))
        lighten_lamp_s(pl,2,LIGHTGREEN);//����������Ϊ�̵�
					  
    if(t==(g[0]+TYELLOW+g[1]))
        lighten_lamp_s(pl,2,YELLOW);//����������Ϊ�Ƶ�

    if(t==(g[0]+2*TYELLOW+g[1]))
        lighten_lamp_s(pl,3,LIGHTGREEN);//���ϱ�ֱ��Ϊ�̵�
					
    if(t==(g[0]+2*TYELLOW+g[1]+g[2]))
        lighten_lamp_s(pl,3,YELLOW);//���ϱ�ֱ��Ϊ�Ƶ�					
 
    if(t==(g[0]+3*TYELLOW+g[1]+g[2]))          
        lighten_lamp_s(pl,4,LIGHTGREEN);// �ϱ����ת��Ϊ��ɫ
						
    if(t==(g[0]+3*TYELLOW+g[1]+g[2]+g[3]))
        lighten_lamp_s(pl,4,YELLOW);//���ϱ�����Ϊ�Ƶ�
							  
    if(t==(g[0]+4*TYELLOW+g[1]+g[2]+g[3]))  
        t=0;           //ѭ����һ�Σ���ʱ������

    if(*flag==1)
        t=0;  //��ʱ������
}