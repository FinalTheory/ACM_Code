/**
 * @file HDU_1599.cpp
 * @brief   图论求最小环，朴素算法。
 * 枚举去除每条边，用Dijkstra求该边两端点的最短距离。
 * 如果这两点连通，用边权+最短距离更新答案。
 * 一开始用邻接表存储，未知原因WA到死……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-07
 */
#include <iostream>
#include <algorithm>
#include <functional>
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
#include <queue>
#include <iomanip>
#define MAX_p 100
#define INF 0x3f3f3f3f
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
typedef pair<int, int> TMD;
int map[MAX_p+10][MAX_p+10];
int d[MAX_p+10];
bool visited[MAX_p+10];
priority_queue< TMD, vector<TMD>, greater<TMD> > q;
int N, M, S, T;

void Dijkstra()
{
	CLR( d, 0x3f );
	CLR( visited, 0 );
	while ( !q.empty() ) q.pop();
	d[S] = 0;
	q.push( make_pair(d[S], S) );
	while ( !q.empty() )
	{
		TMD tmp = q.top(); q.pop();
		int u = tmp.second;
		if ( u == T )
			break;
		if ( visited[u] )
			continue;
		visited[u] = true;
		for ( int i = 1; i <= N; ++i ) if ( map[u][i] < INF )
		{
			if ( d[i] > d[u] + map[u][i] )
			{
				d[i] = d[u] + map[u][i];
				q.push( make_pair(d[i], i) );
			}
		}
	}
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		CLR( map, 0x3f );
		int a, b, c;
		int k = 0;
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d %d", &a, &b, &c);
			if ( a == b ) continue;
			if ( c < map[a][b] && c < map[b][a] )
				map[a][b] = map[b][a] = c;
		}
		int min_cost = INF;
		for ( int i = 1; i < N; ++i )
			for ( int j = i + 1; j <= N; ++j ) if ( map[i][j] != INF )
			{
				int tmp = map[i][j];
				S = i; T = j;
				map[j][i] = map[i][j] = INF;
				Dijkstra();
				map[j][i] = map[i][j] = tmp;
				min_cost = min( min_cost, d[T] + tmp );
			}
		if ( min_cost < INF )
			printf("%d\n", min_cost);
		else
			printf("It's impossible.\n");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
