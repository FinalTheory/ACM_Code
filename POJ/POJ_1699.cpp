/**
 * @file POJ_1699.cpp
 * @brief   求一堆DNA字符序列拼接在一起之后的最短长度（拼接时相同部分可以重叠抵消掉）。
 * @hint    搜遗传算法的时候碰见此题，本来以为是神题，结果尼玛居然是大水。
 *	    建图很简单，求任意两个字符串连接起来能够抵消掉的长度即为边权。
 *	    这样问题转化为求权值和最大的路径，也就是TSP问题。
 *	    由于数据规模太小，所以TSP部分直接暴力搜索就可以。
 *	    构图部分，计算边权可以直接枚举，完全没必要上扩展KMP。
 * @feeling 
 * @author FinalTheory
 * @version 0.1
 * @date 2014-02-03
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

int get_dist( char * a, char * b )
{
	int len_A = strlen(a);
	int len_B = strlen(b);
	int len;
	rep(i, len_A)
	{
		len = 0;
		rep(j, len_A - i)
		{
			if ( j >= len_B ) break;
			if ( a[i + j] == b[j] ) len++;
			else break;
		}
		if ( len == len_A - i ) return len;
	}
	return 0;
}

char DNA[12][24];
int _map[12][12];

int ans, N;

bool vis[12];

void DFS( int prev, int n, int sum )
{
	if ( n == N )
	{
		if ( sum > ans ) ans = sum;
		return;
	}
	rep(i, N) if ( !vis[i] )
	{
		vis[i] = true;
		DFS(i, n + 1, ( prev == -1 ? 0 : sum + _map[prev][i] ) );
		vis[i] = false;
	}
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
	int T = INT(), len;
	while ( T-- )
	{
		CLR(vis, 0);
		CLR(_map, 0);
		len = ans = 0;
		N = INT();
		rep(i, N)
		{
			scanf("%s", DNA[i]);
			len += strlen(DNA[i]);
		}
		rep(i, N)
		rep(j, N) if ( i != j )
			_map[i][j] = get_dist(DNA[i], DNA[j]);
		DFS(-1, 0, 0);
		cout << len - ans << endl;
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
