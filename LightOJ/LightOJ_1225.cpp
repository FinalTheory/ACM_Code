/*
	回文数，水爆了！
*/
#include <stdio.h>
#include <string.h>
int main()
{
	int T, i, j, k, flag;
	char num[30];

	scanf("%d", &T);
	for ( k = 1; k <= T; k++ )
	{
		scanf("%s", num);
		flag = 0;
		for ( i = 0, j = strlen(num) - 1; i < j; i++, j-- )
			if ( num[i] != num[j] )
			{
				printf("Case %d: No\n", k);
				flag = 1;
				break;
			} 
			if ( !flag )
				printf("Case %d: Yes\n", k);
	}

	return 0;
}
