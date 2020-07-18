
#include <stdio.h>
#include <string.h>
int main()
{  char a[100];
  char b[20][100];
   char en[100];
   int m;

  int i=0,j=0,n=0;
     gets(a);
  while(a[i]!='\0')
   {  if(a[i]==" ")
      { b[j][n]='\0';
     j++;
     n=0;
     continue;

    }
    b[j][n++]=a[i];

       i++;
   }

   for(m=j;m>=0;m--)
    { strcat(en,b[m]);
      if(m!=0)
      {
	  strcat(en," ");
      }

    }
    printf("%s",en);
    return 0;
}
