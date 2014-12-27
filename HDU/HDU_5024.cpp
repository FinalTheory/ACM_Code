/**
 * @file HDU_5024.cpp
 * @brief   广州网络赛题目，记忆化搜索
 * @hint    主要是考虑如何记录状态，在每个位置不仅要记录方向，也要记录转弯了几次。
 *	    这样按照最基础的方式进行状态转移即可。
 * @feeling 普通DFS各种无力，写不出来，需要练习DP啊！！！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-09-21
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

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef priority_queue<int, std::vector<int>, std::greater<int> > MPQ;

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

char mp[200][200];
int dp[200][200][8][2];

int _max, n;
int mov[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

inline bool check( int row, int col )
{
    if ( row < 0 || row >= n || col < 0 || col >= n ) return false;
    if ( mp[row][col] == '#' ) return false;
    return true;
}

//记忆化搜索
int DFS( int row, int col, int direct, int turned )
{
    if ( dp[row][col][direct][turned] != -1 ) return dp[row][col][direct][turned];

    //判断是否可以直走
    int new_r = row + mov[direct][0];
    int new_c = col + mov[direct][1];
    if ( check(new_r, new_c) ) {
        dp[row][col][direct][turned] = \
        max(DFS(new_r, new_c, direct, turned) + 1, dp[row][col][direct][turned]);
    }
    if ( turned ) goto finish;
    //判断是否可以拐弯
    for ( int i = -2; i <= 2; i += 4 ) {
        int new_direc = direct + i;
        if ( new_direc < 0 ) new_direc += 8;
        if ( new_direc >= 8 ) new_direc %= 8;
        new_r = row + mov[new_direc][0];
        new_c = col + mov[new_direc][1];
        if ( check(new_r, new_c) ) {
            dp[row][col][direct][turned] = \
            max(DFS(new_r, new_c, new_direc, !turned) + 1, dp[row][col][direct][turned]);
        }
    }
    finish:
    if ( dp[row][col][direct][turned] == -1 )
        dp[row][col][direct][turned] = 1;
    return dp[row][col][direct][turned];
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    while ( scanf("%d", &n) != EOF && n ) {
        rep(i, n) scanf("%s", mp[i]);
        _max = 0;
        CLR(dp, -1);
        rep(i, n)
        rep(j, n) if ( mp[i][j] == '.' ) {
            rep(k, 8)
                _max = max(_max, DFS(i, j, k, 0));
        }
        printf("%d\n", _max);
    }
}
