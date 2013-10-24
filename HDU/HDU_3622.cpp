/**
 * @file HDU_3622.cpp
 * @brief   2-SAT配合二分
 * @hint    这个问题中2-SAT的思路部分很是巧妙。
 *	    对于每一个给出的半径值，我们枚举所有点对，这样可以检查出哪些点是相互排斥的。
 *	    有了这样的排斥关系，并且我们又已知每对点能且必须选一个，这样就转化成一个明显的2-SAT问题了。
 *	    然后对于这种几何求最优值的问题，如果我们无法枚举、没有既有结论，就只能二分。
 *	    这样我们对可能的值域进行二分，每次判定一下在这个半径下2-SAT问题是否有解即可。
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
const double eps = 1e-4;
#define MAX_v 210
#define MAX_e 210 * 210 * 2
int LOW[MAX_v], DFN[MAX_v];
bool Instack[MAX_v];
int Belong[MAX_v];
int TimeStamp, ans;
int p_edges;
int _hash[MAX_v];
struct Point
{
	double x, y;
} points[MAX_v];
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
inline double dist( Point a, Point b )
{
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}
int N;
void Solve( double low, double high )
{
	double mid;
	while ( high - low > eps )
	{
		mid = ( high + low ) / 2.;
		Init();
		for ( int i = 0; i < 2 * N; ++i )
			for ( int j = i + 1; j < 2 * N; ++j ) if ( dist( points[i], points[j] ) < mid )
			{
				if ( i != ( j ^ 1 ) )
					Add_Edge( i, j ^ 1 );
				if ( j != ( i ^ 1 ) )
					Add_Edge( j, i ^ 1 );
			}
		for ( int i = 0; i < 2 * N; ++i ) if ( !DFN[i] )
			Tarjan(i);
		bool flag = true;
		for ( int i = 0; i < N; ++i ) if ( Belong[i * 2] == Belong[i * 2 + 1] )
		{
			flag = false;
			break;
		}
		if (!flag)
			high = mid;
		else
			low = mid;
	}
	printf("%.2lf\n", mid / 2.);
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
	while ( scanf("%d", &N) != EOF )
	{
		Init();
		for ( int i = 0; i < 2 * N; i += 2 )
			scanf("%lf %lf %lf %lf", &points[i].x, &points[i].y, &points[i+1].x, &points[i+1].y);
		Solve( 0. - eps, 20000. * sqrt(2.) + eps );
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

