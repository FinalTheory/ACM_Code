/*
	不长眼没看格式要求，吃了一次WA吃了一次PE。
	看起来这题的数据规模不小，用scanf速度快一些，纯C写的就用gcc吧。
*/
#include <stdio.h>
#include <math.h>
#define P 0.00001

int main()
{
	//freopen("123.txt", "r", stdin);
	int N, m, n, a, b, i, num;
	scanf("%d", &N);
	while ( N-- )
	{
		i = 1;
		while ( 1 )
		{
			scanf("%d%d", &n, &m);
			if ( n == 0 && m == 0 ) break;
			num = 0;
			if ( n == 1 || n == 2 )
			{
				printf("Case %d: 0\n", i++);
				continue;
			}
			for ( a = 1; a < n - 1; a++ )
				for ( b = a + 1; b < n; b++ )
					if ( fabs((a*a+b*b+m)/(double)(a*b) - (int)((a*a+b*b+m)/(double)(a*b))) < P )
						num++;
			printf("Case %d: %d\n", i++, num);
		}
		if ( N )
			printf("\n");
	}
	
}