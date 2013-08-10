/**
 * @file POJ_3662.cpp
 * @brief   Dijkstra模版+二分答案
 * 此题题意是求第k+1边长最小的Dijkstra最短路。这样我们对边长进行排序然后二分。
 * 对于每一个边长，把比它长的边权设为1，小于等于的边权设为零，然后跑一遍Dijkstra。
 * 返回值是Dijkstra最短路中比这个边长要长的边的数目。
 * 如果小于等于k，说明这条边还可以再短一点；如果大于k，说明有点长了需要缩短。
 * 注意要先判断一下这个图是不是连通的。如果是，看是否可以免费建好。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-10
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

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
#define MAX 1010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
typedef pair<int, int> TMD;
priority_queue< TMD, vector<TMD>, greater<TMD> > q;
bool visited[10010];
struct NND
{
	int u, v, w;
} edges[10010];

vector<int> Adja[MAX];

const int INF = 0x3f3f3f3f;
int map[MAX][MAX], d[MAX+10];;


bool fuck( const NND & A, const NND & B )
{
	return A.w < B.w;
}
int N, P;
int Dijkstra( int len )
{
	for ( int i = 1; i <= P; ++i )
	{
		if ( edges[i].w <= len )
			map[edges[i].u][edges[i].v] = map[edges[i].v][edges[i].u] = 0;
		else
			map[edges[i].u][edges[i].v] = map[edges[i].v][edges[i].u] = 1;
	}
	CLR( d, 0x3f );
	CLR( visited, 0 );
	int S = 1, T = N;
	d[S] = 0;
	q.push( make_pair(d[S], S) );
	while ( !q.empty() )
	{
		TMD tmp = q.top(); q.pop();
		int p = tmp.second;
		if ( visited[p] )
			continue;
		visited[p] = true;
		for ( int i = 0; i < Adja[p].size(); ++i ) if ( d[Adja[p][i]] > d[p] + map[p][Adja[p][i]] )
		{
			d[Adja[p][i]] = d[p] + map[p][Adja[p][i]];
			q.push( make_pair(d[Adja[p][i]], Adja[p][i]) );
		}
	}
	return d[T];
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
	int K, a, b, l;
	while ( scanf("%d %d %d", &N, &P, &K) != EOF )
	{
		CLR(map, 0x3f);
		for ( int i = 1; i <= N; ++i )
			Adja[i].clear();
		for ( int i = 1; i <= P; ++i )
		{
			scanf( "%d %d %d", &a, &b, &l );
			edges[i].u = a; edges[i].v = b; edges[i].w = l;
			Adja[edges[i].u].push_back( edges[i].v );
			Adja[edges[i].v].push_back( edges[i].u );
		}
		sort( edges + 1, edges + P + 1, fuck );
		int len = Dijkstra(-1);
		if ( len >= 20000 )
		{
			printf("-1\n");
			continue;
		}
		else if ( len <= K )
		{
			printf("0\n");
			continue;
		}
		int low = 1, high = P, mid;
		while ( low <= high )
		{
			mid = ( low + high ) / 2;
			int tmp = Dijkstra( edges[mid].w );
			if ( tmp <= K )
				high = mid - 1;
			else 
				low = mid + 1;
		}
		printf("%d\n", edges[low].w);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
