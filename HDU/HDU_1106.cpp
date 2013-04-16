#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void quick_sort(int data[], int low, int high)
{
       int i, j, pivot;
       if (low < high)
       {
              pivot=data[low];
              i=low;
              j=high;
             
              while(i<j)
              {
                     while (i<j && data[j]>=pivot)
                            j--;
                     if(i<j)
                            data[i++]=data[j];  
                    
                     while (i<j && data[i]<=pivot)
                            i++;
                     if(i<j)
                            data[j--]=data[i];       
              }
             
              data[i]=pivot;
             
              quick_sort(data,low,i-1);
              quick_sort(data,i+1,high);
       }
}
void main()
{
	int read;
	int all[500]={0};
	char num,str[20];
	int n=0,i=0,j=0,k=0;
	
	while(1)
	{
	num=getchar();
	while(num!='\n')
	{
		read=0;
		while(num!='5'&&num!=10)
		{
			str[k++]=num;
			num=getchar();
			read=1;
		}
		if (read)
		{
		str[k]='\0';
		all[i++]=(atoi(str));
		}
		k=0;
		if(num!=10)
		num=getchar();
	}

	quick_sort(all,0,i-1);

	for(j=0;j<i-1;j++)
		printf("%d ",all[j]);
	printf("%d",all[j]);
	printf("\n");
	for(j=0;j<500;j++)
		all[j]=0;
	i=j=n=k=0;
	}
}