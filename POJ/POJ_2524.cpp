/**
 * @file POJ_2524.cpp
 * @brief   并查集，水题
 * @hint    注意合并的是根节点
 * @feeling 没仔细想居然WA了两发，尼玛……
 * @author FinalTheory
 * @version 0.1
 * @date 2014-04-12
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

#define MAX 50010
int Tree[MAX];

int Find(int v){
    if(Tree[v]!=v)
        Tree[v]=Find(Tree[v]);
    return Tree[v];
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
    int n, m, idx = 1;
    while ( scanf("%d %d", &n, &m) != EOF && n + m )
    {
        int a, b;
        rep(i, n + 1) Tree[i] = i;
        rep(i, m)
        {
            a = INT();
            b = INT();
            int root_a = Find(a);
            int root_b = Find(b);
            if ( root_a != root_b )
                Tree[root_b] = root_a;
        }
        int res = 0;
        REP(i, 1, n + 1) if ( Tree[i] == i )
            res++;
        printf("Case %d: %d\n", idx++, res);
    }
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
