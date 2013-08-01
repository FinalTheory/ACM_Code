/**
 * @file ZOJ_1456.cpp
 * @brief   这题就是个变种的Dijkstra，每次通过一个城市的时候要求收取固定的税费，
 * 也就是在松弛的时候多加一项而已。甚至不用考虑边界情况。
 * 输出字典序最小的路径就稍微有点麻烦了，我们知道Dijkstra是可以记录路径的，但是这里面不能这样做。
 * 这道题是采用DFS的思想，因为DFS是按照顺序搜索的，所以找到的第一条满足要求的路径一定是最短路。
 * 并且由于最短路的长度已知，所以可以在发现不满足条件的时候立刻回溯，减少搜索的时间开销。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-07-31
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
#define MAX 100
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int map[MAX+10][MAX+10], tax[MAX+10], len[MAX+10], visited[MAX+10], realway[MAX+10];
int p, N;
bool found;

void DFS( int current, int goal, int end )
{
	if ( found ) return;
	if ( current > goal ) return;
	if ( current == goal && realway[p - 1] == end )
	{
		found = true;
		cout << realway[0];
		for ( int i = 1; i < p; ++i )
			cout << "-->" << realway[i];
	}
	int cost;
	for ( int i = 1; i <= N; ++i ) if ( !visited[i] )
	{
		visited[i] = 1;
		realway[p] = i;
		cost = current + map[realway[p - 1]][i] + tax[realway[p - 1]];
		p++;
		DFS( cost, goal, end );
		--p;
		visited[i] = 0;
	}
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
	int start, end;
	while ( cin >> N  && N )
	{
		for ( int i = 1; i <= N; ++i )
			for ( int j = 1; j <= N; ++j )
			{
				cin >> map[i][j];
				if ( map[i][j] < 0 )
					map[i][j] = INF;
			}
		for ( int i = 1; i <= N; ++i )
			cin >> tax[i];
		while (true)
		{
			cin >> start >> end;
			if ( start == -1 && end == -1 )
				break;
			cout << "From " << start << " to " << end << " :\n";
			CLR( len, 0 );
			CLR( visited, 0 );
			for ( int i = 1; i <= N; ++i )
				len[i] = map[start][i];
			for ( int i = 1; i <= N; ++i )
			{
				int index = INF, min = INF;
				for ( int j = 1; j <= N; ++j )
					if ( !visited[j] && len[j] < min )
					{
						index = j;
						min = len[index];
					}
					if ( index != INF )
						visited[index] = 1;
					else
						break;
					for ( int j = 1; j <= N; ++j )
						if ( len[j] > len[index] + map[index][j] + tax[index] )
							len[j] = len[index] + map[index][j] + tax[index];
			}
			cout << "Path: ";
			if ( start == end )
				cout << start << endl;
			else
			{
				CLR( visited, 0 );
				CLR( realway, 0 );
				p = 1; realway[0] = start; visited[start] = 1; found = false;
				DFS( -tax[start], len[end], end );
				cout << endl;
			}
			cout << "Total cost : " << len[end] << endl << endl;
		}

	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
