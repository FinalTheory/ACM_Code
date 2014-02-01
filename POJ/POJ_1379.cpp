/**
 * @file POJ_1379.cpp
 * @brief   求平面内离所有点最远的位置（即最小距离最大）。
 * @hint    标准做法是利用平面Voronoi图，不过算法代码量大。
 *	    这里利用模拟退火的思想。
 *	    但是其实根本不用设定接受函数，设定一个迭代次数就足够了。
 *	    在迭代次数以内，不断在包围每个可能点的矩形内寻找更优的点。
 *	    其实本质上就是蒙特卡洛（随机化）算法的一种优化而已。
 * @feeling 很细心地写了半天，没意思。
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
const double eps = 1e-9;

inline int INT()
{
    register int c = getchar();
    int x = 0;
    for( ; ( c < 48 || c > 57 ); c = getchar() );
    for( ; ( c > 47 && c < 58 ); c = getchar() ) x = x * 10 + c - 48;
		return x;
}


#define MAX 1010
#define NUM 20

struct TMD
{
	double x, y, val;
	TMD( double _x = 0., double _y = 0. )
	{
		x = _x;
		y = _y;
	}
} points[MAX], Possible[NUM];
double X, Y;
int m;

inline double dist( TMD a, TMD b )
{
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}

inline double Rand()
{
	return rand() / double(RAND_MAX);
}

void judge( TMD & cur )
{
	double len = INF;
	rep(i, m) len = min( len, dist( cur, points[i] ) );
	cur.val = len;
}

TMD get_point( TMD left_down, TMD right_up )
{
	TMD ret = TMD( left_down.x + ( right_up.x - left_down.x ) * Rand(), \
				   left_down.y + ( right_up.y - left_down.y ) * Rand() );
	judge(ret);
	return ret;
}

void solve( double d )
{
	Possible[0] = TMD(0, 0);
	Possible[1] = TMD(X, Y);
	Possible[2] = TMD(X, 0);
	Possible[3] = TMD(0, Y);
	rep(i, 4) judge(Possible[i]);
	REP(i, 4, NUM) Possible[i] = get_point(Possible[0], Possible[1]);
	while ( d > 0.01 )
	{
		rep(i, NUM)
		rep(j, NUM)
		{
			TMD tmp = get_point( TMD( max(0., Possible[i].x - d), max(0., Possible[i].y - d) ), \
								 TMD( min(X , Possible[i].x + d), min(Y , Possible[i].y + d) ) );
			if ( tmp.val > Possible[i].val ) Possible[i] = tmp;
		}
		d *= 0.9;
	}
	TMD ans;
	ans.val = 0;
	rep(i, NUM) if ( Possible[i].val > ans.val ) ans = Possible[i];
	printf("The safest point is (%.1lf, %.1lf).\n", ans.x, ans.y);
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
	int c = INT();
	while ( c-- )
	{
		X = INT(); Y = INT(); m = INT();
		rep(i, m)
		{
			points[i].x = INT();
			points[i].y = INT();
		}
		solve(max(X, Y));
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
