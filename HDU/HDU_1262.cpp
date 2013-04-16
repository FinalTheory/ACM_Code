#include <stdio.h>
#include <math.h>

void main()
{
	int store[10000]={2,3,5,7};
	int n,m,a,b;
	int i,j=0,k=0,check,p=4;
	
	for(i=9;i<10000;i+=2)
	{
	k=(int)sqrt((double)i);
	check=1;
	while(store[j]<k+1)
	{
		if (i%store[j]==0){check=0;break;}
		j++;
	}
	if (check) store[p++]=i;
	j=0;
	}
	while(scanf("%d",&n)!= EOF)
	{
	m=n/2;
	for(i=0;i<10000;i++)
		if (store[i]<=m&&store[i+1]>=m) {k=i+1;break;}
	b=k;
	while(b<10000)
	{
		a=k;
		while(a>=0)
			{
				if ((store[a]+store[b])==n){break;}
				a--;
			}
		if ((store[a]+store[b])==n){break;}
		b++;
	}
	printf("%d %d\n",store[a],store[b]);
	}
}