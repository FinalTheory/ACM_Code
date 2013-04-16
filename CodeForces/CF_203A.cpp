/*
	不多说，看明白题意就行。
	注意这个SB可能得零分！
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int x, t, a, b, da, db, i, j, found;
	while ( scanf("%d %d %d %d %d %d", &x, &t, &a, &b, &da, &db) != EOF )\
	{
		found = 0;
		if ( x == 0 )
		{
			printf("YES\n");
			continue;
		}
		for ( i = 0; i < t && !found; i++ )
			for ( j = 0; j < t && !found; j++ )
			{
				if ( x == a - i * da + b - j * db )
					found = 1;
			}
			for ( i = 0; i < t && !found; i++ )
			{
				if ( x == a - i * da || x == b - i * db )
					found = 1;
			}
			if ( found )
				printf("YES\n");
			else
				printf("NO\n");
	}
	return 0;
}