/**
 * @file FZU_2141.cpp
 * @brief   图上的贪心问题，不错的题目
 * @hint    题意是从图中选出两部分点，构成二分图，并且能用上大于等于m/2条边
 *	    仔细思考一下，其实不管你怎么选点，因为允许去掉边构二分图，所以一定是可以构造的。
 *	    问题在于如果选取尽量多的边使得满足使用边数的条件。
 *	    这里用到了贪心的思想，对于每个点，统计它周围已经被染色的点的染色情况。
 *	    如果黑比白多，那么这个点就该染色成白色，因为这样的话连向黑点的边就都能够利用上了；
 *	    否则的话，为了尽可能利用边，就要染成黑色。因为是SPJ，所以其实判断条件不需要精准。
 *	    难道是能证明只要用这样的策略，选出的边数一定满足条件？
 * @feeling 自己写了一发，1A
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-08
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

VI Adja[110];
int color[110];


int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
    int T;
    scanf("%d", &T);
    while ( T-- )
    {
        int n, m;
        scanf("%d %d", &n, &m);
        rep(i, n + 1) Adja[i].clear();
        CLR(color, -1);
        int x, y;
        rep(i, m) {
            scanf("%d %d", &x, &y);
            Adja[x].PB(y);
            Adja[y].PB(x);
        }
        color[1] = 0;
        int b, w;
        REP(u, 2, n + 1) {
            b = w = 0;
            rep(i, Adja[u].size()) {
                int v = Adja[u][i];
                if ( color[v] == 0 ) w++;
                else if ( color[v] == 1 ) b++;
            }
            if ( w > b ) color[u] = 1;
            else color[u] = 0;
        }
        int sum1 = 0, sum2 = 0;
        REP(i, 1, n + 1) {
            if ( color[i] == 0 ) sum1++;
            else if ( color[i] == 1 ) sum2++;
        }
        printf("%d", sum1);
        REP(i, 1, n + 1) if ( color[i] == 0 )
            printf(" %d", i);
        puts("");
        printf("%d", sum2);
        REP(i, 1, n + 1) if ( color[i] == 1 )
            printf(" %d", i);
        puts("");
    }
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
