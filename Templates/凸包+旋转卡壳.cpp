/**
 * @file POJ 2187
 * @brief  凸包和旋转卡壳模版。
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
#define eps 0.0000001
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define PI 3.14159265358979323846
using namespace std;

struct TMD
{
	int x, y;
	double angle, dist;
} Points[MAX];

bool comp( const TMD & A, const TMD & B )
{
	if ( A.y != B.y )
		return A.y < B.y;
	else
		return A.x < B.x;
}

bool operator < ( const TMD & A, const TMD & B )
{
	//千万注意这里的比较方法！
	if ( fabs(A.angle - B.angle) > eps )
		return A.angle - B.angle < eps;
	else
		return A.dist - B.dist < eps;
}
//计算极角
double polar_angle( double x, double y )
{
	double L = sqrt( x * x + y *y );
	return acos( x / L );
}
//获取栈中第二元素
TMD get_Next_To_Top( stack<TMD> & P )
{
	TMD tmp, res;
	tmp = P.top();
	P.pop();
	res = P.top();
	P.push(tmp);
	return res;
}
//计算三个点之间的旋转关系（注意x轴转至y轴返回正值）
int calc( TMD A, TMD B, TMD C )
{
	int x1, x2, y1, y2;
	x1 = B.x - A.x;
	y1 = B.y - A.y;
	x2 = C.x - B.x;
	y2 = C.y - B.y;
	return x1 * y2 - x2 * y1;
}

int cross( TMD A, TMD B, TMD O )
{
	return ( A.x - O.x ) * ( B.y - O.y ) - ( B.x - O.x ) * ( A.y - O.y );
}

//计算距离
int dist( const TMD & A, const TMD & B )
{
	return ( A.x - B.x ) * ( A.x - B.x ) + ( A.y - B.y ) * ( A.y - B.y );
}

int Rotating_Calipers( int num )
{
	int p, q, ans;
	//注意这里，凸包有可能变为一条线段，这时的最大值显然应该是线段两端的距离
	ans = dist( Points[0], Points[num - 1] );
	//下面开始漂亮的旋转卡壳
	//这里利用了一个性质：最远距离时产生的有向面积最大；
	//并且由于是逆时针枚举，因此算得的有向面积不用取绝对值。
	Points[num] = Points[0];
	for ( p = 0, q = 1; p < num; ++p )
	{
		while ( cross( Points[p + 1], Points[q + 1], Points[p] ) > cross( Points[p + 1], Points[q], Points[p] ) )
			q = ( q + 1 ) % num;
		ans = max( ans, max( dist( Points[p], Points[q] ), dist( Points[p + 1], Points[q + 1] ) ) );
	}
	return ans;
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
	int N, i;
	TMD min_point;
	int min_pos;
	stack<TMD> P;
	while ( scanf("%d", &N) != EOF )
	{
		min_pos = -1;
		min_point.x = min_point.y = INF;
		while ( !P.empty() ) P.pop();
		//首先找到原点
		for ( i = 0; i < N; ++i )
		{
			scanf("%d %d", &Points[i].x, &Points[i].y);
			if ( comp( Points[i], min_point ) )
			{
				min_point = Points[i];
				min_pos = i;
			}
		}
		if ( N < 3 )
		{
			printf( "%d\n", dist( Points[0], Points[1] ) );
			continue;
		}
		//对原点的极角置INF以令其排序后成为第一元素
		Points[min_pos].angle = -INF;
		for ( i = 0; i < N; ++i ) if ( i != min_pos )
		{
			Points[i].angle = polar_angle( Points[i].x - Points[min_pos].x, Points[i].y - Points[min_pos].y );
			Points[i].dist = dist( Points[i], Points[min_pos] );
		}
		sort( Points, Points + N );
		//前三个点入栈(如果题目允许点数小于三，注意特殊处理)
		P.push( Points[0] ); P.push( Points[1] ); P.push( Points[2] );
		for ( i = 3; i < N; ++i )
		{
			//这里的比较不会将极角相同的点出栈
			while ( calc( get_Next_To_Top(P), P.top(), Points[i] ) < 0 )
				P.pop();
			P.push( Points[i] );
		}
		N = P.size();
		//将栈中元素出栈，形成一个顺时针排列的点数组。
		for ( i = N - 1; i >= 0; --i )
		{
			Points[i] = P.top();
			P.pop();
		}
		printf( "%d\n", Rotating_Calipers(N) );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
