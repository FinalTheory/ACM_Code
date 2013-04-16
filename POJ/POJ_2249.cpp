/*
	这代码能过真心奇迹！！！直接Copy的别人的，懒得写严谨的了。
*/
#include <stdio.h>

int main()
{
	int n,m;
	int i ;
	int sum ;
	while(scanf("%d %d",&n ,&m ) != EOF )
	{
		if(n ==0 && m==0 )
			break;
		if( m > n / 2 )
			m = n - m;
		double k = 1;
		for(i = 1; i <= m ; i ++ )
			k = k * ( n - m + i ) / i ;   
		printf("%d\n", (long)k );   
	}
	return 0;
}