/**
 * @file POJ_2031.cpp
 * @brief   最小生成树模版题，注意浮点。1A
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-04
 */
#include <iostream>
#include <algorithm>
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
#include <iomanip>
#define MAX 110
#define eps 0.0000000001
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

double x[MAX], y[MAX], z[MAX], r[MAX];

struct TMD
{
	int u, v;
	double len;
} roads[6000];
int p_roads;

char flags[6000];
char in_tree[MAX];

double dist( double x1, double y1, double z1, double x2, double y2, double z2 )
{
	return sqrt( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) + ( z1 - z2 ) * ( z1 - z2 ) );
}

bool fuck( const TMD & A, const TMD & B )
{
	return A.len < B.len;
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
	int n, i, j;
	char changed;
	double sum;
	while ( scanf("%d", &n) && n )
	{
		p_roads = 0;
		CLR( in_tree, 0 );
		CLR( flags, 0 );
		for ( i = 0; i < n; ++i )
			scanf("%lf %lf %lf %lf", &x[i], &y[i], &z[i], &r[i]);
		for ( i = 0; i < n - 1; ++i )
			for ( j = i + 1 ; j < n; ++j )
			{
				double tmp = dist( x[i], y[i], z[i], x[j], y[j], z[j] ) - ( r[i] + r[j] );
				if ( tmp > eps )
				{
					roads[p_roads].u = i + 1;
					roads[p_roads].v = j + 1;
					roads[p_roads++].len = tmp;
				}
				else
				{
					roads[p_roads].u = i + 1;
					roads[p_roads].v = j + 1;
					roads[p_roads++].len = 0.;
				}
			}
		sort( roads, roads + p_roads, fuck );
		sum = 0.;
		in_tree[1] = changed = 1;
		while ( changed )
		{
			changed = 0;
			for ( i = 0; i < p_roads; ++i )
			{
				if ( flags[i] ) continue;
				if ( !in_tree[roads[i].u] && in_tree[roads[i].v] || !in_tree[roads[i].v] && in_tree[roads[i].u] )
				{
					in_tree[roads[i].u] = in_tree[roads[i].v] = 1;
					sum += roads[i].len;
					flags[i] = changed = 1;
					break;
				}
			}
		}
		printf("%.3lf\n", sum);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
