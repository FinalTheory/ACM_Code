/**
 * @file POJ_3083.cpp
 * @brief   这题实际上算是一个模拟加广搜，BFS的部分我很清楚怎么写，但是模拟就很捉鸡了。
 * 一直也搞不清楚方向是怎么区分的，最后迫不得已扒了别人的代码，不想一直WA在这上。
 * 那个递归形式的DFS模拟。凑合看吧。但是个人感觉我的BFS写的还是很漂亮的，虽然还是调试了半天。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-18
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <iomanip>
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char map[50][50];
int map_bfs[50][50];

int w, h;

bool check( int i, int j )
{
	if ( i < 0 || i >= h || j < 0 || j >= w || map_bfs[i][j] == -1 )
		return false;
	return true;
}
int moves_left[4][2] =  { {0,1}, {1,0}, {0,-1}, {-1,0} };
int moves_right[4][2] = { {0,1}, {-1,0}, {0,-1}, {1,0} };
void BFS()
{
	bool changed = 1;
	while ( changed )
	{
		changed = 0;
		for ( int i = 0; i < h; ++i )
			for ( int j = 0; j < w; ++j )
				for ( int k = 0; k < 4; ++k )
					if ( map_bfs[i][j] != -1 && map_bfs[i][j] < INF && check( i + moves_left[k][0], j + moves_left[k][1] ) )
						if ( map_bfs[i + moves_left[k][0]][j + moves_left[k][1]] > map_bfs[i][j] + 1 )
						{
							changed = 1;
							map_bfs[i + moves_left[k][0]][j + moves_left[k][1]] = map_bfs[i][j] + 1;
						}
					
	}
}

int end_i, end_j;

int DFS( int ii, int jj, int direct, int mv[4][2] )
{
	if ( ii == end_i && jj == end_j )
		return 1;
	int t, a, b;
	for ( int k = 0; k < 4; ++k )
	{
		t = ( direct + k ) % 4;
		a = ii + mv[t][0];
		b = jj + mv[t][1];
		if ( check( a, b ) )
			return DFS( a, b, ( t + 3 ) % 4, mv ) + 1;
	}
	return -1;
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int t, direct, start_i, start_j;
	cin >> t;
	while ( t-- )
	{
		CLR(map_bfs, 0x3f);
		cin >> w >> h;
		for ( int i = 0; i < h; ++i )
			cin >> map[i];
		for ( int i = 0; i < h; ++i )
			for ( int j = 0; j < w; ++j )
			{
				if ( map[i][j] == 'S' )
				{
					map_bfs[i][j] = 1;
					start_i = i;
					start_j = j;
				}
				if ( map[i][j] == 'E' )
				{
					end_i = i;
					end_j = j;
				}
				if ( map[i][j] == '#' )
					map_bfs[i][j] = -1;
			}
		BFS();
		//确定出发方向
		if ( start_i == 0 )
			direct = 0;
		else if ( start_i == h - 1 )
			direct = 2;
		else if ( start_j == 0 )
			direct = 1;
		else if ( start_j == w - 1 )
			direct = 3;
		//int tmp = DFS( start_i, start_j, direct, moves_left );
		printf("%d %d %d\n", DFS( start_i, start_j, direct, moves_left ), DFS( start_i, start_j, direct, moves_right ), map_bfs[end_i][end_j]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
