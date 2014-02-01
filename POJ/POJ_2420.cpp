/**
 * @file POJ_2420.cpp
 * @brief   N个点的费马点问题
 * @hint    还是一样的思路，取重心作为初始点，随机走步并重新计算函数；
 *	    如果函数值变小就更新。注意初始步长设置为任何两点之间的最大距离即可。
 * @feeling 顺手敲出来的，1A甚爽！
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

#define MAX 110
#define TIMES 20

struct TMD
{
	double x, y;
	TMD( double _x = 0., double _y = 0. )
	{
		x = _x;
		y = _y;
	}
	void read()
	{
		scanf("%lf %lf", &x, &y);
	}
} p[MAX];

int N;

inline double dist( TMD a, TMD b )
{
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}

inline double judge( TMD cur )
{
	double sum = 0.;
	rep( i, N ) sum += dist(cur, p[i]);
	return sum;
}

void solve( double delta, TMD s )
{
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
	printf("%.0f\n", judge(s));
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
		TMD s;
		rep(i, N)
		{
			p[i].read();
			s.x += p[i].x; s.y += p[i].y;
		}
		s.x /= N; s.y /= N;
		double tmp, len = 0.;
		rep(i, N)
		rep(j, N) if ( i != j )
			if ( ( tmp = dist(p[i], p[j]) ) > len ) len = tmp;
		solve( len, s );
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
