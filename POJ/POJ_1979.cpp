/*
	����DFS������������һ������Dijkstra�ķ������ظ�ѭ�����λ�ã����Ծ�û�õݹ顣
	VS�ĵ�������ʾ���������⣬û�м�ʱ���£�����ӵ�������
	�������������һ��AC�ˡ�
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
char map[22][22];
int W, H;
int z[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0 };
bool check( int a, int b )
{
	if ( a < 0 || b < 0 )
		return 0;
	if ( a >= H || b >= W )
		return 0;
	return 1;
}
int main()
{
	freopen("in.txt", "r", stdin);
	int sum, i, j, k, changed, x, y;
	while ( cin >> W >> H && W )
	{
		sum = 0;
		changed = 1;
		for ( i = 0; i < H; i++ )
			scanf("%s", map[i]);
		for ( i = 0; i < H; i++ )
			for ( j = 0; j < W; j++ )
				if ( map[i][j] == '@' )
				{
					x = j;
					y = i;
					map[i][j] = 48;
					break;
				}
		//cout << x << ' ' << y << endl;
		while( changed )
		{
			changed = 0;
			for ( i = 0; i < H; i++ )
				for ( j = 0; j < W; j++ )
					if ( map[i][j] == 48 )
						for ( k = 0; k < 4; k++ )
						{
							x = j + z[k][1];
							y = i + z[k][0];
							if  ( check( y, x ) && map[y][x] == '.' )
							{
								map[y][x] = 48;
								changed = 1;
							}
						}
		}
		for ( i = 0; i < H; i++ )
			for ( j = 0; j < W; j++ )
				if ( map[i][j] == 48 )
					sum++;
		cout << sum << endl;
	}
}