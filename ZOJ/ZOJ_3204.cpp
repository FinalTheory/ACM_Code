/**
 * @file ZOJ_3204.cpp
 * @brief   最小生成树水题，注意字典序的处理方法。
 * PE两次WA两次，尼玛……似乎多输出超过一个空格就会被判为WA……
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-30
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
#define MAX 30000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int map[110][110];
char real_map[110][110];
char intree[110], flags[10001];
struct TMD
{
	int u, v, w;
} roads[10001];
int p_roads;
bool fuck( const TMD & A, const TMD & B )
{
	if ( A.w != B.w )
		return A.w < B.w;
	else if ( A.u != B.u )
		return A.u < B.u;
	else
		return A.v < B.v;
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
	int T, i, j, n, sum;
	scanf("%d", &T);
	while ( T-- )
	{
		CLR( map, 0 );
		scanf("%d", &n);
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
			{
				scanf("%d", &map[i][j]);
				map[j][i] = map[i][j];
			}
		p_roads = 0;
		for ( i = 1; i < n; ++i )
			for ( j = i + 1; j <= n; ++j )
			{
				if ( map[i][j] )
				{
					roads[p_roads].u = i;
					roads[p_roads].v = j;
					roads[p_roads++].w = map[i][j];
				}
			}
		sort( roads, roads + p_roads, fuck );
		CLR(intree, 0);
		CLR(flags, 0);
		CLR(real_map, 0);
		intree[1] = 1; char changed = 1;
		sum = 0;
		while ( changed )
		{
			changed = 0;
			for ( i = 0; i < p_roads; ++i )
			{
				if ( flags[i] )
					continue;
				if ( intree[roads[i].u] && !intree[roads[i].v] || !intree[roads[i].u] && intree[roads[i].v] )
				{
					real_map[roads[i].u][roads[i].v] = real_map[roads[i].v][roads[i].v] = 1;
					intree[roads[i].u] = intree[roads[i].v] = 1;
					sum += roads[i].w;
					flags[i] = 1;
					changed = 1;
					break;
				}
			}
		}
		char fail = 0, out = 0;
		for ( i = 1; i <= n; ++i )
		{
			if( !intree[i] )
			{
				fail = 1;
				break;
			}
		}
		if ( fail )
		{
			printf("-1\n");
		}
		else
		{
			out = 0;
			for ( i = 1; i <n; ++i )
			{
				for ( j = i + 1; j <= n; ++j )
					if ( real_map[i][j] )
					{
						if ( out )
							printf( " %d %d", i, j );
						else
						{
							printf( "%d %d", i, j );
							out = 1;
						}
					}
			}
			printf("\n");
		}
	}
	

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

