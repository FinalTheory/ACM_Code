/*
	用一下位运算就可以了，0MS过，速度还是很快的。
	注意输出格式，WA了一次……
*/
#include <stdio.h>

int main()
{
	int T, i, j, num;
	unsigned n, n2;
	scanf("%d" ,&T);
	for ( j = 1; j <= T; j++ )
	{
		num = 0;
		scanf("%d" ,&n);
		for ( i = 0; i < 32; i++ )
		{
			n2 = n>>i;
			n2 &= 1;
			if ( n2 )
				num++;
		}
		printf("Case %d: %s\n", j, ( num%2 ) ? "odd" : "even");
	}
}