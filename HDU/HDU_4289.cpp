/**
 * @file HDU_4289.cpp
 * @brief   最大流求最小割，几乎是裸的模版题
 * @hint    拆点建图，将点u、v拆为u'，u''，v'，v''，然后加入边u'->u''的容量为c；
 *	    边u''->v'，v''->u'的容量为INF，然后直接求最大流即可。
 * @feeling 我似乎是把源点和汇点给弄反了，跪烂！贴对模版之后1A。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-30
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
#define MAX 400
int cap[MAX+10][MAX+10], flow[MAX+10][MAX+10], a[MAX+10];
int parent[MAX+10];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	queue<int> q;
	int N, M, start, end, u, v, c, x, y;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		while ( !q.empty() ) q.pop();
		CLR(cap, 0); CLR(flow, 0);
		scanf("%d %d", &x, &y);
		start = x; end = y;
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &c);
			cap[i][i + N] = c;
		}
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d", &u, &v);
			cap[v + N][u] = INF;
			cap[u + N][v] = INF;
		}
		end += N;
		N *= 2;
		unsigned long long max_flow = 0;
		for (;;)
		{
			CLR( a, 0 );
			a[start] = INF;
			q.push(start);
			while ( !q.empty() )
			{
				int u = q.front(); q.pop();
				for ( int v = 1; v <= N; ++v ) if ( !a[v] && cap[u][v] > flow[u][v] )
				{
					parent[v] = u; q.push(v);
					a[v] = min( a[u], cap[u][v] - flow[u][v] );
				}
			}
			if ( a[end] == 0 ) break;
			for ( int u = end; u != start; u = parent[u] )
			{
				flow[parent[u]][u] += a[end];
				flow[u][parent[u]] -= a[end];
			}
			max_flow += a[end];
		}
		cout << max_flow << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
