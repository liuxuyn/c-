#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{
	unsigned char xiangsu;
	float fangcha=0,biaozhuncha=0, pingfanghe=0,xiangsuhe=0,xiangsuaverage=0;
	short row=0,col=0;
	int i=0,j=0, N=0;
	int qujian1=0,qujian2=0,qujian3=0,qujian4=0,qujian5=0,qujian6=0,qujian7=0,qujian8=0,qujian9=0,qujian10=0;
	FILE *fp;
	if((fp=fopen("C:\\Users\\86131\\Desktop\\U201914742.dat","rb"))==NULL) 
	{
    printf("File Open Error!\n");
	exit(1);
	}
	fread(&row, sizeof(short), 1, fp);
	fread(&col, sizeof(short), 1, fp);
	for(i=0; i<row; i++)
	{
    	for(j=0; j<col; j++)
   		{
        //单个像素值的读入、
        fread(&xiangsu, sizeof( unsigned char), 1, fp);
        
		//统计、
		xiangsuhe=xiangsuhe+xiangsu;
		pingfanghe=pingfanghe+xiangsu*xiangsu;
		//每个区间的计数等处理
		if(xiangsu>=0&&xiangsu<=24) qujian1++;
		else if(xiangsu>=25&&xiangsu<=49) qujian2++;
		else if(xiangsu>=50&&xiangsu<=74) qujian3++;
		else if(xiangsu>=75&&xiangsu<=99) qujian4++;
		else if(xiangsu>=100&&xiangsu<=124) qujian5++;
		else if(xiangsu>=125&&xiangsu<=149) qujian6++;
		else if(xiangsu>=150&&xiangsu<=174) qujian7++;
		else if(xiangsu>=175&&xiangsu<=199) qujian8++;
		else if(xiangsu>=200&&xiangsu<=224) qujian9++;
		else //if(xiangsu>=225&&xiangsu<=255) 
		qujian10++;
		/*0 -  24 | *
 		25 -  49 | **
 		50 -  74 | ***
 		75 -  99 | *********
		100 - 124 | ***********
		125 - 149 | *****************
		150 - 174 | ***********
		175 - 199| ******
		200 - 224| *********
		225 - 255| **********
		*/
		}	
	}
	fclose(fp);
	N=row*col;
	xiangsuaverage=xiangsuhe/N;
	fangcha=(pingfanghe-N*xiangsuaverage*xiangsuaverage)/(N-1);
	biaozhuncha=sqrt(fangcha);
	printf("灰度平均值为%f\n",xiangsuaverage);
	printf("灰度标准差为%f\n",biaozhuncha) ;

	
	int I=0;
	
		printf("0 -  24 \t");
	for(I=0;I<qujian1/200;I++){
		printf("*");	
	}	printf("\n");
		
		printf("25 -  49 \t");
	for(I=0;I<qujian2/200;I++){
		printf("*");	
	}printf("\n");
	
		printf("50 -  74 \t");
	for(I=0;I<qujian3/200;I++){
		printf("*");		
	}printf("\n");
		
		printf("75 -  99 \t");
	for(I=0;I<qujian4/200;I++){
		printf("*");
	}printf("\n");
	
		printf("100 -  124 \t");
	for(I=0;I<qujian5/200;I++){
		printf("*");	
	}printf("\n");
	
		printf("125 -  149 \t");
	for(I=0;I<qujian6/200;I++){
		printf("*");	
	}printf("\n");
		
		printf("150 -  174 \t");
	for(I=0;I<qujian7/200;I++){
		printf("*");	
	}printf("\n");
		
		printf("175 -  199 \t");
	for(I=0;I<qujian8/200;I++){
		printf("*");	
	}printf("\n");
		
		printf("200 -  224 \t");
	for(I=0;I<qujian9/200;I++){
		printf("*");		
	}printf("\n");
		
		printf("225 -  255 \t");
	for(I=0;I<qujian10/200;I++){
		printf("*");	
	}printf("\n");

	

}
