/**
 * @file HDU_1824.cpp
 * @brief   简单的2-SAT判定问题
 * @hint    只需要把队长和队员看作对立的，然后每次读入队伍的时候把队员和队长分别哈希到两个节点；
 *	    这样就可以直接操作哈希数组来当2-SAT成模版题做了。
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
#define MAX_e 5010 * 2
int LOW[MAX_v], DFN[MAX_v];
bool Instack[MAX_v];
int Belong[MAX_v];
int TimeStamp, ans;
int p_edges;
int _hash[MAX_v];
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
	int T, M;
	int a, b, c;
	while ( scanf("%d %d", &T, &M) != EOF )
	{
		Init();
		for ( int i = 0; i < T; ++i )
		{
			scanf("%d %d %d", &a, &b, &c);
			_hash[a] = i * 2;
			_hash[b] = _hash[c] = i * 2 + 1;
		}
		for ( int i = 0; i < M; ++i )
		{
			scanf("%d %d", &a, &b);
			Add_Edge( _hash[a], _hash[b] ^ 1 );
			Add_Edge( _hash[b], _hash[a] ^ 1 );
		}
		for ( int i = 0; i < 2 * T; ++i ) if ( !DFN[i] )
			Tarjan(i);
		bool flag = true;
		for ( int i = 0; i < T; ++i ) if ( Belong[i * 2] == Belong[i * 2 + 1] )
		{
			flag = false;
			break;
		}
		if (flag)
			puts("yes");
		else
			puts("no");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

