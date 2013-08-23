/**
 * @file HDU_4463.cpp
 * @brief   数据规模很小，近乎裸的最小生成树，但是注意是两个点初始化进MST。
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
const int INF = 0x3f3f3f3f;
struct TMD
{
	int u, v;
	double w;
} roads[2510];
bool fuck( const TMD & A, const TMD & B )
{
	return A.w < B.w;
}
inline double dist( double x1, double x2, double y1, double y2 )
{
	return sqrt( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) );
}
double x[101], y[101];
bool intree[101], flag[10001];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int N, p, q, idx;
	double sum;
	bool changed;
	while ( scanf("%d", &N) && N )
	{
		idx = 0; sum = 0.;
		scanf("%d %d", &p, &q);
		if ( p > q ) swap(p, q);
		for ( int i = 1; i <= N; ++i )
			scanf("%lf %lf", &x[i], &y[i]);
		for ( int i = 1; i <= N; ++i )
			for ( int j = i + 1; j <= N; ++j )
			{
				roads[idx].u = i; roads[idx].v = j;
				if ( i == p && j == q ) {
					continue;
				}
				roads[idx++].w = dist( x[i], x[j], y[i], y[j] );
			}
		sort( roads, roads + idx, fuck );
		CLR( intree, 0 ); CLR( flag, 0 );
		intree[p] = intree[q] = changed = true;
		while ( changed )
		{
			changed = false;
			for ( int j = 0; j < idx; ++j )
			{
				if ( flag[j] )
					continue;
				if ( intree[roads[j].u] && !intree[roads[j].v] || !intree[roads[j].u] && intree[roads[j].v] )
				{
					intree[roads[j].u] = intree[roads[j].v] = true;
					sum += roads[j].w;
					flag[j] = true;
					changed = true;
					break;	
				}
			}
		}
		double _dist = dist( x[p], x[q], y[p], y[q] );
		printf("%.2lf\n", sum + _dist );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
