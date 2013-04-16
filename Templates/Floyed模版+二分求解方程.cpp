/**
 * @file OUC_1130.cpp
 * @brief   带浮点的最短路问题,数据规模较小.
 * 首先跑一遍Floyed，算出每个点之间的最短路。
 * 然后遍历每条路，从左往右走和从右往左走各算一遍。
 * 如果到端点需要的时间比较最值时间长，就直接走；否则在这里等待一下。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-04-09
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
#include <sstream>
#include <iomanip>
#define precise 0.00000001
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

double map[110][110];
double dist[110][110];
struct TMD
{
	int x, y;
	double v, a;
} roads[510];

double calc( double t, double v, double a )
{
	return ( 1 - log(a) * v * pow( a, -t ) );
}

//求解最短时间
double solve( double low, double high, double v, double a )
{
	double mid;
	while ( fabs( high - low ) > precise )
	{
		mid = ( high + low ) / 2;
		if ( calc( low, v, a ) * calc( mid, v, a ) < 0 )
			high = mid;
		else if ( calc( high, v, a ) * calc( mid, v, a ) < 0 )
			low = mid;
		else
			break;
	}
	return low;
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
	int C, R, i, j, k, x, y;
	double v, a;
	while ( cin >> C >> R && C )
	{
		for ( i = 1; i <= C; ++i )
			for ( j = 1; j <= C; ++j )
				map[i][j] = 1000000.;
		for ( i = 0; i < R; ++i )
		{
			cin >> x >> y >> v >>a;
			roads[i].x = x;
			roads[i].y = y;
			roads[i].v = v;
			roads[i].a = a;
			map[x][y] = map[y][x] = v;
		}
		memcpy( dist, map, sizeof(map) );
		//初始化并开始运行Floyed
		for ( i = 1; i <= C; ++i )
			dist[i][i] = 0;
		for ( k = 1; k <= C; ++k )
			for ( i = 1; i <= C; ++i )
				for ( j = 1; j <= C; ++j )
					if ( dist[i][j] > dist[i][k] + dist[k][j] )
						dist[i][j] = dist[i][k] + dist[k][j];
		//枚举每条边，计算最短时间
		double time_min = 100000., time1, res;
		for ( i = 0; i < R; ++i )
		{
			if ( dist[1][roads[i].x] >= ( res = solve( 0, 2100., roads[i].v, roads[i].a ) ) )
				time1 = dist[1][roads[i].x] + roads[i].v * pow( roads[i].a, -dist[1][roads[i].x] );
			else
				time1 = res + roads[i].v * pow( roads[i].a, -res );
			time1 += dist[roads[i].y][C];
			if ( time1 < time_min )
				time_min = time1;
			if ( dist[1][roads[i].y] >= ( res = solve( 0, 2100., roads[i].v, roads[i].a ) ) )
				time1 = dist[1][roads[i].y] + roads[i].v * pow( roads[i].a, -dist[1][roads[i].y] );
			else
				time1 = res + roads[i].v * pow( roads[i].a, -res );
			time1 += dist[roads[i].x][C];
			if ( time1 < time_min )
				time_min = time1;
		}
		cout << fixed << setprecision(3) << time_min << endl;
		
	}


#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
