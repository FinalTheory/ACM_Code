#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	unsigned sum, i, j, k, num2[32000];
	int t, end;
	char out;
	char num[32000], number[6];
	//freopen("123.txt", "r", stdin);
	memset(num2, 0, sizeof(num2));
	num[0] = num2[0] = 1;
	for ( i = 2; i <= 32000; i++  )
	{
		sprintf( number, "%d", i );
		num[i-1] = strlen( number );
		num2[i-1] += num2[i-2];
		for ( j = 0; j < i; j++ )
		{
			num2[i-1] += num[j];
		}

	}
	scanf("%d", &t);
	while ( t-- )
	{
		out = sum = 0;
		scanf("%u", &i);
		for ( j = 0; j < 32000; j++ )
		{
			if ( num2[j] > i ) 
			{
				k = j;
				break;
			}
		}
		k--;
		sum = num2[k];
		if ( i == sum ) 
		{
			sprintf( number,"%d", k + 1 );
			printf("%c\n", number[strlen(number)-1]);
			continue;
		}
		for ( j = 0; j <= k; j++ )
			if ( sum + num[j] < i )
				sum += num[j];
			else if ( sum + num[j] > i )
			{
				sprintf( number, "%d", j + 1 );
				printf("%c\n", number[i - sum - 1]);
				out = 1;
				break;
			}
			else
			{
				sprintf( number,"%d", j + 1 );
				printf("%c\n", number[strlen(number)-1]);
				out = 1;
				break;
			}
	}
}