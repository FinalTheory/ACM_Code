/**
 * @file HDU_3062.cpp
 * @brief   最基础的2-SAT模版题
 * @hint    搞明白怎么建图就可以了。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-25
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
#define MAX_v 2010
#define MAX_e 1010 * 1010 * 2
int LOW[MAX_v], DFN[MAX_v];
bool Instack[MAX_v];
int Belong[MAX_v];
int TimeStamp, ans;
int p_edges;
struct TMD
{
	int from, to, next;
} edges[MAX_e];
struct NND
{
	int top;
	int elem[MAX_v];
} stk;
int head[MAX_v];
void Add_Edge( int _u, int _v )
{
	edges[p_edges].from = _u; edges[p_edges].to = _v;
	edges[p_edges].next = head[_u];
	head[_u] = p_edges++;
}
void Tarjan( int u )
{
	int v;
	DFN[u] = LOW[u] = ++TimeStamp;
	stk.elem[++stk.top] = u;
	Instack[u] = true;
	for ( int e = head[u]; e != -1; e = edges[e].next )
	{
		v = edges[e].to;
		if ( !DFN[v] )
		{
			Tarjan(v);
			LOW[u] = min( LOW[u], LOW[v] );
		}
		else if ( Instack[v] )
		{
			LOW[u] = min( LOW[u], DFN[v] );
		}
	}
	if ( DFN[u] == LOW[u] )
	{
		++ans;
		do
		{
			v = stk.elem[stk.top--];
			Instack[v] = false;
			Belong[v] = ans;
		} while ( v != u );
	}
}
void Init()
{
	ans = TimeStamp = p_edges = 0;
	stk.top = -1;
	CLR( DFN, 0 ); CLR( Instack, 0 ); CLR( head, -1 );
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
	int n, m;
	int a1, a2, c1, c2;
	while ( scanf("%d", &n) != EOF )
	{
		scanf("%d", &m);
		Init();
		for ( int i = 0; i < m; ++i )
		{
			scanf("%d %d %d %d", &a1, &a2, &c1, &c2);
			Add_Edge( a1 * 2 + c1, a2 * 2 + !c2 );
			Add_Edge( a2 * 2 + c2, a1 * 2 + !c1 );
		}
		for ( int i = 0; i < 2 * n; ++i ) if ( !DFN[i] )
			Tarjan(i);
		bool flag = true;
		for ( int i = 0; i < n; ++i ) if ( Belong[i * 2] == Belong[i * 2 + 1] )
		{
			flag = false;
			break;
		}
		if (flag)
			puts("YES");
		else
			puts("NO");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

