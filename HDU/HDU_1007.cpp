/**
 * @file HDU_1007.cpp
 * @brief   平面最近点距离
 * @hint    简单写的实现，用来理解算法模型，待改进
 * @feeling 参照了别人的代码
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-03
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

const int MAX = 100100;

struct TMD
{
    double x, y;
} data[MAX], tmp[MAX];

inline double dist( const TMD & a, const TMD & b )
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline bool cmp_x( const TMD & a, const TMD & b )
{
    if ( fabs(a.x - b.x) < eps )
        return a.x > b.x;
    else
        return a.y > b.y;
}

inline bool cmp_y( const TMD & a, const TMD & b )
{
    if ( fabs(a.y - b.y) < eps )
        return a.y > b.y;
    else
        return a.x > b.x;
}

double get_min( int l, int r )
{
    if ( r - l == 1 ) return double(INF);
    if ( r - l == 2 ) return dist(data[l], data[r - 1]);
    int m = ( l + r ) >> 1;
    double d1 = get_min(l, m);
    double d2 = get_min(m, r);
    double dm = min(d1, d2);
    int k = 0;
    REP(i, l, r) if ( fabs(data[m].x - data[i].x) < dm )
        tmp[k++] = data[i];
    sort(tmp, tmp + k, cmp_y);
    rep(i, k)
    REP(j, i + 1, k) dm = min(dm, dist(tmp[i], tmp[j]));
    return dm;
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
    int n;
    while ( scanf("%d", &n) != EOF && n )
    {
        rep(i, n) scanf("%lf %lf", &data[i].y, &data[i].x);
        sort(data, data + n, cmp_x);
        double res = get_min(0, n);
        printf("%.2lf\n", res / 2.);
    }
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
