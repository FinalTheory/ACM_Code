/**
 * @file POJ_2187.cpp
 * @brief   计算几何入门题，凸包问题。
 * 首先求出凸包，枚举边缘上所有点求最长距离就可以。其实极端数据的话可能会WA，用旋转卡壳更好。
 * POJ上面1A，感觉太爽了……可惜时间上比较捉鸡……学旋转卡壳的时候再优化一下。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-06-03
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
#define MAX 50010
#define INF 10000000
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

struct TMD
{
	int x, y;
	double angle, dist;
} Points[MAX];

bool operator < ( const TMD & A, const TMD & B )
{
	if ( A.y != B.y )
		return A.y < B.y;
	else
		return A.x < B.x;
}

bool fuck( const TMD & A, const TMD & B )
{
	if ( A.angle != B.angle )
		return A.angle < B.angle;
	else
		return A.dist < B.dist;
}

double polar_angle( double x, double y )
{
	double L = sqrt( x * x + y *y );
	return acos( x / L );
}

TMD get_Next_To_Top( stack<TMD> & P )
{
	TMD tmp, res;
	tmp = P.top();
	P.pop();
	res = P.top();
	P.push(tmp);
	return res;
}

int calc( TMD A, TMD B, TMD C )
{
	int x1, x2, y1, y2;
	x1 = B.x - A.x;
	y1 = B.y - A.y;
	x2 = C.x - B.x;
	y2 = C.y - B.y;
	return x1 * y2 - x2 * y1;
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
	int N, i, j;
	TMD min_point;
	int min_pos;
	stack<TMD> P;
	while ( cin >> N )
	{
		min_pos = -1;
		min_point.x = min_point.y = INF;
		while ( !P.empty() ) P.pop();
		for ( i = 0; i < N; ++i )
		{
			cin >> Points[i].x >> Points[i].y;
			if ( Points[i] < min_point )
			{
				min_point = Points[i];
				min_pos = i;
			}
		}
		//如果点数少于3，直接输出两点间距离
		if ( N < 3 )
		{
			printf( "%d\n", ( Points[0].x - Points[1].x ) * ( Points[0].x - Points[1].x ) + ( Points[0].y - Points[1].y ) * ( Points[0].y - Points[1].y ) );
			continue;
		}
		Points[min_pos].angle = -INF;
		for ( i = 0; i < N; ++i ) if ( i != min_pos )
		{
			Points[i].angle = polar_angle( Points[i].x - Points[min_pos].x, Points[i].y - Points[min_pos].y );
			Points[i].dist = sqrt( (double)(Points[i].x - Points[min_pos].x) * (Points[i].x - Points[min_pos].x) + \
				(Points[i].y - Points[min_pos].y) * (Points[i].y - Points[min_pos].y) );
		}
		sort( Points, Points + N, fuck );
		P.push( Points[0] ); P.push( Points[1] ); P.push( Points[2] );
		for ( i = 3; i < N; ++i )
		{
			while ( calc( get_Next_To_Top(P), P.top(), Points[i] ) < 0 )
				P.pop();
			P.push( Points[i] );
		}
		N = P.size();
		for ( i = 0; i < N; ++i )
		{
			Points[i] = P.top();
			P.pop();
		}
		int _max = -1;
		for ( i = 0; i < N - 1; ++i )
			for ( j = i + 1; j < N; ++j )
			{
				int tmp = ( Points[i].x - Points[j].x ) * ( Points[i].x - Points[j].x ) + ( Points[i].y - Points[j].y ) * ( Points[i].y - Points[j].y );
				if ( tmp > _max )
					_max = tmp;
			}
		cout << _max << endl;
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
