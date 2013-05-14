/**
 * @file POJ_3669.cpp
 * @brief   BFS裸搜，地图做预处理存上每个地方被破坏的时间，注意标记掉已经走过的位置。
 * 还有就是TMD这玩意会存在走不出去的情况的，不读题真心伤不起……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-13
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
#include <queue>
#define maxn 400
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
int _move[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };
char vis[maxn+10][maxn+10];
int map[maxn+10][maxn+10];
int steps[maxn+10][maxn+10];

struct TMD
{
	int x, y, t;
};

bool check( int x, int y )
{
	if ( x >= 0 && x <= maxn && y >= 0 && y <= maxn )
		return 1;
	else
		return 0;
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
	int M, i, x, y, t, j;
	char found;
	queue<TMD> q;
	while ( scanf("%d", &M) != EOF )
	{
		while ( !q.empty() ) q.pop();
		CLR( steps, 0 );
		CLR( map, 0x3f );
		CLR( vis, 0 );
		for ( j = 0; j < M; ++j )
		{
			scanf("%d %d %d", &x, &y, &t);
			if ( map[x][y] > t )
				map[x][y] = t;
			for ( i = 0; i < 4; ++i )
				if ( check( x + _move[i][0], y + _move[i][1] ) && \
					map[x + _move[i][0]][y + _move[i][1]] > t )
					map[x + _move[i][0]][y + _move[i][1]] = t;
		}
		TMD start = { 0,0,1 }, tmp, to_add;
		vis[0][0] = 1;
		q.push(start);
		found = 0;
		while ( !q.empty() )
		{
			tmp = q.front();
			q.pop();
			if ( map[tmp.x][tmp.y] == INF )
			{
				found = 1;
				break;
			}
			for ( i = 0; i < 4; ++i )
				if ( check( tmp.x + _move[i][0], tmp.y + _move[i][1] ) \
					&& !vis[tmp.x + _move[i][0]][tmp.y + _move[i][1]] \
					&& map[tmp.x + _move[i][0]][tmp.y + _move[i][1]] > tmp.t )
				{
					to_add.x = tmp.x + _move[i][0];
					to_add.y = tmp.y + _move[i][1];
					to_add.t = tmp.t + 1;
					vis[tmp.x + _move[i][0]][tmp.y + _move[i][1]] = 1;
					q.push(to_add);
				}
		}
		if ( !found )
			printf("-1\n");
		else
			printf("%d\n", tmp.t - 1);
	}
	

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
