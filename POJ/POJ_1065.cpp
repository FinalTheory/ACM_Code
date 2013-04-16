#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stick
{
	int l;
	int w;
} sticks[5000];
int cmp( const void *a ,const void *b)
{
	if ( (*(struct stick *)a).l != (*(struct stick *)b).l )
		return (*(struct stick *)a).l > (*(struct stick *)b).l ? 1 : -1;
	else
		return (*(struct stick *)a).w > (*(struct stick *)b).w ? 1 : -1;
}
int main()
{
	int t, n, end, i, min, keep_l, keep_w;
	char flags[5000];
	//freopen( "123.txt", "r", stdin );
	scanf("%d", &t);
	while ( t-- )
	{
		scanf("%d", &n);
		min = 0;
		memset(flags, 1, sizeof(flags));
		for ( i = 0; i < n; i++ )
			scanf("%d %d", &sticks[i].l, &sticks[i].w);
		qsort(sticks, n, sizeof(stick), cmp);
		for ( end = n - 1; end >= 0; end-- )
		{
			if ( flags[end] )
			{
				keep_l = sticks[end].l;
				keep_w = sticks[end].w;
				for ( i = end ; i >= 0; i-- )
				{
					if ( flags[i] )
						if ( keep_w >= sticks[i].w )
						{
							keep_w = sticks[i].w;
							keep_l = sticks[i].l;
							flags[i] = 0;
						}
				}
				min++;
			}
		}
		printf("%d\n", min);
	}
}