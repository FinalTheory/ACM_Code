/**
 * @file HDU_4292.cpp
 * @brief   最大流问题
 * @hint    核心是如何建图，首先将每个人拆成两个点，之间的容量为1；
 *	    然后增加超级源点与超级汇点，分别与食物、饮料相连，容量为对应的食物、饮料可用量；
 *	    最后是将每个人的两端分别与实物、饮料相连，容量大于1即可，也可以为INF。
 *	    剩下的任务就是Dinic模版了。
 * @feeling 一开始忘了是双向加边，RE了一发；然后发现汇点写笔误了WA了两发，郁闷ing~
 * @author FinalTheory
 * @version 0.1
 * @date 2013-09-01
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
#define MAX 200000
#define MAX_p 1000
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long LL;
int to[MAX], cap[MAX], head[MAX_p], next_e[MAX];
//记录分层图
int dist[MAX_p];
//源点、汇点
int Src, Dst;

int p_edges;
void Add_Edge( int _u, int _v, int _cap )
{
	to[p_edges] = _v; cap[p_edges] = _cap;
	next_e[p_edges] = head[_u];
	head[_u] = p_edges++;
	to[p_edges] = _u; cap[p_edges] = 0;
	next_e[p_edges] = head[_v];
	head[_v] = p_edges++;
}

//BFS构建分层图
bool BFS()
{
	int u, v;
	queue<int> q;
	while ( !q.empty() ) q.pop();
	CLR( dist, -1 ); dist[Src] = 0; q.push(Src);
	while ( !q.empty() )
	{
		u = q.front(); q.pop();
		for ( int i = head[u]; i != -1; i = next_e[i] )
		{
			v = to[i];
			if ( cap[i] > 0 && dist[v] == -1 )
			{
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[Dst] != -1;
}
//按照分层图DFS找出一条增广路
int DFS( int u, int low )
{
	if ( u == Dst )
		return low;
	int tmp, v;
	for ( int i = head[u]; i != -1; i = next_e[i] )
	{
		v = to[i];
		if ( cap[i] > 0 && dist[v] == dist[u] + 1 && ( tmp = DFS( v, min( low, cap[i] ) ) ) )
		{
			cap[i] -= tmp;
			cap[i^1] += tmp;
			return tmp;
		}
	}
	dist[u] = -1;
	return 0;
}

int Dinic()
{
	int max_flow = 0, tmp;
	while ( BFS() )
	{
		while (true)
		{
			tmp = DFS( Src, INF );
			if ( tmp == 0 ) break;
			max_flow += tmp;
		}
	}
	return max_flow;
}

char buffer[300];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, F, D, cap;
	while ( scanf("%d %d %d", &N, &F, &D) != EOF )
	{
		p_edges = 0;
		CLR( head, -1 ); CLR( next_e, -1 );
		Src = 0; Dst = F + D + 2 * N + 1;
		for ( int i = 1; i <= F; ++i )
		{
			scanf("%d", &cap);
			Add_Edge( Src, i, cap );
		}
		for ( int i = F + 2 * N + 1; i <= F + 2 * N + D; ++i )
		{
			scanf("%d", &cap);
			Add_Edge( i, Dst, cap );
		}
		for ( int i = F + 1; i <= F + N; ++i )
			Add_Edge( i, i + N, 1 );
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%s", buffer);
			for ( int j = 0; j < F; ++j )
				if ( buffer[j] == 'Y' )
					Add_Edge( j + 1, F + i, INF );
		}
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%s", buffer);
			for ( int j = 0; j < D; ++j )
				if ( buffer[j] == 'Y' )
					Add_Edge( F + N + i, F + 2 * N + j + 1, INF );
		}
		int ans = Dinic();
		printf("%d\n", ans);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
