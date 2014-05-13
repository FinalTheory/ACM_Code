/**
 * @file HDU_2444.cpp
 * @brief   二分图匹配模版题
 * @hint    无
 * @feeling 1A
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-04
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

const int MAX = 210;
//vector存储邻接表
VI Adja[MAX];
//保存节点的染色情况
int color[MAX];
//保存节点的二分图匹配，以及是否访问过
int match[MAX], visited[MAX];
//点数、边数
int n, m;
//二分图判定
bool judge( int u, int prev )
{
    if ( color[u] != 0 ) {
        if ( color[u] != -prev ) return false;
        else  return true;
    }
    color[u] = -prev;
    rep(i, Adja[u].size()) {
        if ( !judge(Adja[u][i], color[u]) )
            return false;
    }
    return true;
}
//初始化
void Init()
{
    CLR(color, 0);
    rep(i, n + 1) Adja[i].clear();
}
//数据读入
void Read()
{
    int a, b;
    rep(i, m) {
        scanf("%d %d", &a, &b);
        Adja[a].PB(b);
        Adja[b].PB(a);
    }
}
//DFS寻找增广路
bool DFS( int u )
{
	rep(i, Adja[u].size())
	{
		//枚举与点u相邻的所有点（邻接表存储）
		int v = Adja[u][i];
		if ( !visited[v] )
		{
			visited[v] = true;
			if ( match[v] == -1 || DFS( match[v] ) )
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}
//二分图匹配
int Hungary()
{
	int res = 0;
	CLR(match, -1);
	REP(u, 1, n + 1)
	{
		CLR( visited, 0 );
		if ( DFS(u) ) res++;
	}
	return res;
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

    while ( scanf("%d %d", &n, &m) != EOF )
    {
        Init();
        Read();
        if ( !judge(1, 1) ) {
            puts("No");
        } else {
            int res = Hungary();
            printf("%d\n", res / 2);
        }
    }
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
