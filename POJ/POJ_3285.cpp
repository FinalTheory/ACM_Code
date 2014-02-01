/**
 * @file POJ_3285.cpp
 * @brief   在放有三个圆的平面上求一个点，使得这三个圆相对于这一点的视角相等。
 * @hint    其实和1379是一样的，也是设定一个初始点然后随机地走，只要新位置的函数值更小就更新。
 *	    但是这题的特点在于评估函数不好找，它既然要求是三个尽量相等，那么就应该想到：
 *	    表征数值的差异性的常用指标是……方差。
 *	    然后注意一下，题目要求视角最大的点，也就是不能超出这三个圆盘的边界。
 *	    而边界是什么呢？显然就是三个点的横纵坐标所围成的矩形。
 * @feeling 又是照着题解写的，不然得调试很久。
 * @author FinalTheory
 * @version 0.1
 * @date 2014-02-01
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
using namespace std;

#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define SQR(x) ((x)*(x))
#define REP(i,a,b) for(int i=a;i<b;i++)
#define REV(i,a,b) for(int i=a-1;i>=b;i--)
#define rep(i,n) REP(i,0,n)
#define rev(i,n) REV(i,n,0)
#define ITER(i,x) for(typeof(x.begin()) i=x.begin();i!=x.end();i++)
#define ALL(v) v.begin(),v.end()
#define PB push_back
#define MP make_pair
#define PQ priority_queue
#define MPQ priority_queue<int, std::vector<int>, std::greater<int> >

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const double PI = 3.141592653589793238;
const double eps = 1e-8;

inline int INT()
{
    register int c = getchar();
    int x = 0;
    for( ; ( c < 48 || c > 57 ); c = getchar() );
    for( ; ( c > 47 && c < 58 ); c = getchar() ) x = x * 10 + c - 48;
		return x;
}

#define TIMES 20

struct TMD
{
	double x, y, r;
	TMD( double _x = 0., double _y = 0., double _r = 0. )
	{
		x = _x;
		y = _y;
		r = _r;
	}
} p[3];

inline double dist( TMD a, TMD b )
{
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}

double max_x = -INF, max_y = -INF;
double min_x = INF, min_y = INF;

inline double judge( TMD cur )
{
	if ( cur.x < min_x || cur.x > max_x || cur.y < min_y || cur.y > max_y ) return INF;
	double agl[3], aver = 0., sum = 0.;
	rep( i, 3 )
	{
		agl[i] = p[i].r / dist(cur, p[i]);
		aver += agl[i];
	}
	aver /= 3.;
	rep(i, 3) sum += ( agl[i] - aver ) * ( agl[i] - aver );
	return sqrt(sum / 3);
}

void solve( double delta )
{
	TMD s;
	rep(i, 3)
	{
		s.x += p[i].x;
		s.y += p[i].y;
	}
	s.x /= 3; s.y /= 3;
	double val = judge(s), t;
	while ( delta > eps )
	{
		rep(i, TIMES)
		{
			double theta = rand();
			TMD tmp( s.x + delta * cos(theta), s.y + delta * sin(theta) );
			if ( ( t = judge(tmp) ) < val )
			{
				val = t;
				s = tmp;
			}
		}
		delta *= .88;
	}
	if ( val < eps )
		printf("%.2f %.2f\n", s.x, s.y);
	else
		puts("No solution");
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
	while ( 1 )
	{
		double sum = 0.;
		rep(i, 3)
		{
			scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].r);
			sum += ( p[i].x + p[i].y + p[i].r );
		}
		if ( sum < eps ) break;
		rep(i, 3)
		{
			max_x = max(max_x, p[i].x);
			max_y = max(max_y, p[i].y);
			min_x = min(min_x, p[i].x);
			min_y = min(min_y, p[i].y);
		}
		solve( max(max_x - min_x, max_y - min_y) );
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
