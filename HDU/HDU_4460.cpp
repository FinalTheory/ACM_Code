/**
 * @file HDU_4460.cpp
 * @brief   裸的SPFA求所有点之间最短路的最大值，贴模版800多MS水过。
 * @feeling 爽！但是无向图要注意边数，RE一发！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-23
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
#define MAX_p 1010
#define MAX_e 20010
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
map<string, int> _stoi;
char _names[MAX_p][12];
int u[MAX_e], v[MAX_e], head[MAX_p], next_e[MAX_e], in_queue_times[MAX_p], w[MAX_e], d[MAX_p];
bool in_queue[MAX_p];
queue<int> q;
int N, _max;
bool SPFA( int S )
{
	while ( !q.empty() ) q.pop();
	for ( int i = 1; i <= N; ++i )
		d[i] = INF;
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
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int M, idx, u, v;
	char str1[12], str2[12];
	string _name, a, b;
	while ( scanf("%d", &N) && N )
	{
		_stoi.clear();
		for ( int i = 1; i <= N; ++i )
		{
			scanf("%s", _names[i]);
			_name = _names[i];
			_stoi[_name] = i;
		}
		scanf("%d", &M);
		p_edges = 0;
		CLR( head, -1 ); CLR( next_e, -1 );
		for ( int i = 0; i < M; ++i )
		{
			scanf("%s %s", str1, str2);
			a = str1; b = str2;
			u = _stoi[a]; v = _stoi[b];
			Add_Edge( u, v, 1 );
			Add_Edge( v, u, 1 );
		}
		_max = -1;
		for ( int i = 1; i <= N; ++i )
		{
			SPFA(i);
			for ( int j = 1; j <= N; ++j )
				if ( _max < d[j] )
					_max = d[j];
		}
		if ( _max < MAX_p )
			printf("%d\n", _max);
		else
			puts("-1");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
