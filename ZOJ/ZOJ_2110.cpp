/*
	DFS题目，需要奇偶性剪枝，否者TLE。
	原本吃饱了撑的另开了一个数组记录点是否被走过，结果搞得程序混乱，也不知道回溯的对不对，反正WA了好几次。
	后来参考别人的思路，直接在原本的map上做标记，搜索后立刻回溯，这样总算AC了。
	NOTE:仔细理解奇偶性剪枝！！！
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <time.h>
#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)
using namespace std;
char map[8][8], found;
int M, N, T;
int z[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0 }, end_x, end_y, beg_x, beg_y;
bool check( int a, int b )
{
	if ( a < 0 || b < 0 )
		return 0;
	if ( a >= N || b >= M )
		return 0;
	return 1;
}
void search( int i, int j, int t )
{
	if ( found )
		return;
	if ( i == end_y && j == end_x && t == T )
	{
		found = 1;
		return;
	}
	int fac = ( T - t ) - fabs( (double)i - end_y ) - fabs( (double)j - end_x );
	if( fac < 0 || fac % 2)
		return;
	int x, y;
	for ( int k = 0; k < 4; k++ )
	{
		x = j + z[k][1];
		y = i + z[k][0];
		if ( check(y, x) && map[y][x] != 'X' )
		{
			map[y][x] = 'X';
			search(y, x, t + 1);
			map[y][x] = '.';
		}
	}
}
int main()
{
	//freopen( "in.txt", "r", stdin );
	int i, j, walls;
	while ( 1 )
	{
		cin >> N >> M >> T;
		if ( !N && !M && !T ) break;
		walls = found = 0;
		for ( i = 0; i < N; i++ )
			scanf("%s", map[i]);
		for ( i = 0; i < N; i++ )
			for ( j = 0; j < M; j++ )
			{
				if ( map[i][j] == 'D' )
				{
					end_x = j;
					end_y = i;
				}
				if ( map[i][j] == 'S' )
				{
					beg_x = j;
					beg_y = i;
				}
				if ( map[i][j] == 'X' )
					walls++;
			}
		if( M * N - walls < T )
		{
			printf("NO\n");
			continue;
		}
		map[beg_y][beg_x] = 'X';
		search(beg_y, beg_x, 0);
		if ( found )
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}