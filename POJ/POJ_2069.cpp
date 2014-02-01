/**
 * @file POJ_2069.cpp
 * @brief   求覆盖空间所有点的最小圆半径，模拟退火可解。
 * @hint    跟1379类似，不过这次生成下一步的方法发生了变化。
 *	    本质上，模拟退火的思路是每次温度降低之后，接受的概率变小。
 *	    而在这题里面，相当于是每次朝着最远的方向移动；
 *	    但是移动的距离这个量慢慢地在发生“退火”，逐渐地变小。
 *	    这样也是一种退火的思路，而且码量减小了很多。
 * @feeling 又是相当于贴了别人的代码，不甚光彩。
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

#define STEP 25000

struct TMD
{
	double x, y, z;
	TMD(){}
	TMD( double _x, double _y, double _z )
	{
		x = _x;
		y = _y;
		z = _z;
	}
} points[40];

int n;

inline double dist( TMD a, TMD b )
{
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) + ( a.z - b.z ) * ( a.z - b.z ) );
}

inline double Rand()
{
	return rand() / double(RAND_MAX);
}

inline int judge( TMD cur )
{
	double len = 0., tmp;
	int idx = -1;
	rep(i, n) if ( ( tmp = dist( cur, points[i] ) ) > len )
	{
		len = tmp;
		idx = i;
	}
	return idx;
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
	while ( scanf("%d", &n) && n )
	{
		TMD s(0., 0., 0.);
		rep(i, n)
		{
			scanf("%lf %lf %lf", &points[i].x, &points[i].y, &points[i].z);
			s.x += points[i].x;
			s.y += points[i].y;
			s.z += points[i].z;
		}
		double delta = 0.1;
		s.x /= n; s.y /= n; s.z /= n;
		rep(k, STEP)
		{
			int dst = judge(s);
			s.x += ( points[dst].x - s.x ) * delta;
			s.y += ( points[dst].y - s.y ) * delta;
			s.z += ( points[dst].z - s.z ) * delta;
			delta *= 0.9993;
		}
		printf("%.5f\n", dist(s, points[judge(s)]));
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
