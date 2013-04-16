#include <stdio.h>
#include <string.h>
char wall[101][101];
char flags[101][101];
int walls[101];
int x_max, y_max;
void update()
{
	int i, j, k0;
	memset(walls, 0, sizeof(walls));
	for ( j = 0; j <= x_max; j++ )
	{
		k0 = 0;
		for ( i = 0; i <= y_max; i++ )
		{
			if ( wall[i][j] == 1 ) k0++;
		}
		walls[j] = k0;
	}
}
int len( int i, int j )
{
	int len = 0, k;
	for ( k = j; k <= x_max; k++ )
		if ( flags[i][k] != 2 )
			len++;
		else
		{
			len++;
			break;
		}
		return len;
}
void remove( int i, int j )
{
	int k;
	for ( k = j; k <= x_max; k++ )
		if ( flags[i][k] != 2 )
			wall[i][k] = 0;
		else
		{
			flags[i][k] = 2;
			wall[i][k] = 0;
			break;
		}
}
int main()
{
	int t, n, k, x1, y1, x2, y2, i, j, to_remove, max_len, max_pos, removed;
	//freopen("test.txt", "r", stdin);
	scanf("%d", &t);
	while ( t-- )
	{
		x_max = y_max = removed = 0;
		memset( wall, 0, sizeof(wall) );
		memset(flags, 0, sizeof(flags));
		scanf("%d %d", &n, &k);
		while ( n-- )
		{
			scanf( "%d %d %d %d", &x1, &y1, &x2, &y2 );
			if ( x1 > x2 )
			{
				x1 ^= x2;
				x2 ^= x1;
				x1 ^= x2;
			}
			if ( x2 > x_max )
				x_max = x2;
			if ( y2 > y_max )
				y_max = y2;
			for ( i = x1; i <= x2; i++ )
				wall[y1][i] = 1;
			flags[y2][x2] = 2;
		}
		update();
		for ( j = 0; j <= x_max; j++ )
		{
			if ( walls[j] > k )
			{
				to_remove = walls[j] - k;
				while ( to_remove-- )
				{
					max_len = max_pos = 0;
					for ( i = 0; i <= y_max; i++ )
					{
						if ( wall[i][j] )
							if ( len(i, j) > max_len )
							{
								max_len = len(i ,j);
								max_pos = i;
							}
					}
					remove(max_pos, j);
					removed++;
				}
				update();
			}
		}
		printf("%d\n", removed);
	}
	return 0;
}