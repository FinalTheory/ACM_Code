/**
 * @file HDU_1534.cpp
 * @brief  差分约束模版题，注意对大于等于关系，求的是最长路。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-07
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
#define MAX_p 1000
#define MAX_e 1000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;
const int INF = 0x3f3f3f3f;
int _time[MAX_p];
int u[MAX_e], v[MAX_e], head[MAX_p], next_e[MAX_e], in_queue_times[MAX_p], w[MAX_e], d[MAX_p];
bool in_queue[MAX_p];
queue<int> q;
int N;
bool SPFA()
{
	int S = 0;
	while ( !q.empty() ) q.pop();
	for ( int i = 1; i <= N; ++i )
		d[i] = -INF;
	d[S] = 0;
	CLR( in_queue, 0 );
	CLR( in_queue_times, 0 );
	q.push(S); in_queue[S] = true;
	while ( !q.empty() )
	{
		int p = q.front(); q.pop();
		in_queue[p] = false;
		for ( int e = head[p]; e != -1; e = next_e[e] ) if ( d[v[e]] < d[p] + w[e] )
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
	int idx = 1, a, b, ww;
	char str[10];
	while ( scanf("%d", &N) != EOF && N )
	{
		p_edges = 0;
		CLR( head, -1 ); CLR( next_e, -1 );
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%d", &_time[i]);
			Add_Edge( 0, i, 0 );
		}
		while (true)
		{
			scanf("%s", str);
			if ( str[0] == '#' ) break;
			scanf("%d %d", &a, &b);
			ww = 0;	//修正为小于等于
			if ( str[0] == 'F' )
				ww -= _time[a];
			if ( str[2] == 'F' )
				ww += _time[b];
			Add_Edge( b, a, ww );
		}
		printf("Case %d:\n", idx++);
		if ( SPFA() )
		{
			int min_num = INF;
			for ( int i = 1; i <= N; ++i ) if ( d[i] < min_num )
				min_num = d[i];
			for ( int i = 1; i <= N; ++i )
				printf("%d %d\n", i, d[i] - min_num);
		}
		else
			printf("impossible\n");
		puts("");
	}


#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
