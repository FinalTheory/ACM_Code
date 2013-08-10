/**
 * @file POJ_3259.cpp
 * @brief   读懂题意，按照输入建图就可以，然后SPFA判断负环。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
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
#define MAX_p 510
#define MAX_e 6000
#define CLR(arr,val) memset(arr,val,sizeof(arr))
const int INF = 0x3f3f3f3f;
using namespace std;
int u[MAX_e], v[MAX_e], head[MAX_p], next_e[MAX_e], in_queue_times[MAX_p], w[MAX_e], d[MAX_p];
bool in_queue[MAX_p];
queue<int> q;

bool SPFA( int N )
{
	int S = 1;
	while ( !q.empty() ) q.pop();
	CLR( d, 0x3f );
	d[S] = 0;
	CLR( in_queue, 0 );
	CLR( in_queue_times, 0 );
	q.push(S); in_queue[S] = true;
	while ( !q.empty() )
	{
		int p = q.front(); q.pop();
		in_queue[p] = false;
		for ( int e = head[p]; e != -1; e = next_e[e] ) if ( d[v[e]] > d[p] + w[e] )
		{
			d[v[e]] = d[p] + w[e];
			if ( !in_queue[v[e]] )
			{
				in_queue[v[e]] = true;
				in_queue_times[v[e]]++;
				q.push(v[e]);
				if ( in_queue_times[v[e]] >= N )
					return false;
			}
		}
	}
	return true;
}
int p_edges;
void Add_Edge( int uu, int vv, int ww )
{
	u[p_edges] = uu; v[p_edges] = vv; w[p_edges] = ww;
	next_e[p_edges] = head[u[p_edges]];
	head[u[p_edges]] = p_edges;
	p_edges++;
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
	int F, N, M, W, S, E, T;
	scanf("%d", &F);
	while ( F-- )
	{
		p_edges = 0;
		CLR( head, -1 ); CLR( next_e, -1 );
		scanf("%d %d %d", &N, &M, &W);
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d %d", &S, &E, &T);
			Add_Edge( S, E, T );
			Add_Edge( E, S, T );
		}
		for ( int i = 0; i < W; ++i )
		{
			scanf("%d %d %d", &S, &E, &T);
			Add_Edge( S, E, -T );
		}
		if ( !SPFA( N ) )
			printf("YES\n");
		else
			printf("NO\n");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
