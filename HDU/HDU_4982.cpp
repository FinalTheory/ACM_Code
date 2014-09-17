/**
 * @file HDU_4982.cpp
 * @brief   一个经典的构造问题
 * @hint    参考注释
 * @feeling 被cha了，郁闷……好在也cha了别人
 * @author FinalTheory
 * @version 0.1
 * @date 2014-08-26
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

bool check( int num, int k, int rem )
{
    if ( rem == 0 ) return false;
    int inc = 1;
    //首先尝试前1~k-1的和，并且要跳过不合法值
    //如果这些数就已经装满了，则可以判为失败
    rep(i, k - 1) {
        if ( inc == rem ) inc++;
        if ( num <= inc ) return false;
        num -= inc;
        inc++;
    }
    //然后处理最后一个数的情况
    //因为判断完前面的情况后，如果再出现问题，则一定是最后一个数的问题
    while ( 1 ) {
        //需要的最后一个数大于剩余的数，则失败
        if ( num < inc ) return false;
        //剩余的数不等于不合法值，并且大于等于inc，那么就可以直接作为最后一个数，确保合法
        if ( num != rem ) return true;
        //如果都不满足，则增加增量，减少剩余的数
        //这个的意思是说，把倒数第二个数往前挪，再看最后一个数能否合法放置
        inc++;
        num--;
    }
    return false;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int n, k;
    while ( cin >> n >> k )
    {
        bool found = false;
        for ( int i = 1; i * i <= n; i++ ) {
            int rem = n - i * i;
            if ( check(i * i, k - 1, rem) ) {
                found = true;
                break;
            }
        }
        if ( found ) puts("YES");
        else puts("NO");
    }
}
