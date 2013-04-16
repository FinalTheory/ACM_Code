#include <stdio.h>


void main()
{
	int count,n;
	int i=0,j=1,p=0,a,b;
	int num[100][100]={0};
	scanf("%d",&count);
	while(count--)
	{
		scanf("%d",&n);
		for (i=0;i<n;i++)
			for (j=0;j<i+1;j++)
				scanf("%d",&num[i][j]);
		for(i=n-1;i>0;i--)
			for(j=0;j<i;j++)
			{
			a=num[i-1][j]+num[i][j];
			b=num[i-1][j]+num[i][j+1];
			num[i-1][j]=(a>b)?a:b;
			}
		printf("%d\n",num[0][0]);
	}
}