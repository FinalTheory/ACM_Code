/**
 * @file HDU_4902.cpp
 * @brief   线段树区间更新问题
 * @hint    区间记录两个值：区间数值（不一致则记-1）和区间最大值
 *	    对于第一种更新，直接区间替换为新数值，并同时更新最大值；
 *	    对于第二种更新，则更新匹配并且数值一致的区间；否则就继续PushDown。
 *	    这样操作之后，最后完成一整遍询问即可。
 * @feeling 一般难度的题目
 * @author FinalTheory
 * @version 0.1
 * @date 2014-07-31
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

#define MAX 100010
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1

int gcd(int a, int b)
{
    if ( a < b ) swap(a, b);
    if ( b == 0 ) return a;
    else return gcd(b, a % b);
}

int nVal[MAX<<2], nMax[MAX<<2];

inline void PushUp( int root )
{
    if ( nVal[L_son] == nVal[R_son] ) {
        nVal[root] = nVal[L_son];
    } else {
        nVal[root] = -1;
    }
    nMax[root] = max(nMax[L_son], nMax[R_son]);
}

inline void PushDown( int root )
{
	if ( nVal[root] != -1 )
	{
		nVal[L_son] = nVal[R_son] = nVal[root];
		nMax[L_son] = nMax[R_son] = nMax[root];
	}
}

void CreateTree( int root, int L, int R )
{
	if (L == R) {
        scanf("%d", &nVal[root]);
        nMax[root] = nVal[root];
        return;
	}
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
	PushUp(root);
}

void Update( int root, int L, int R, int l, int r, int x )
{
    if ( L == l && R == r && nVal[root] != -1 ) {
        if ( nVal[root] > x ) {
            nVal[root] = gcd(nVal[root], x);
            nMax[root] = nVal[root];
            return;
        }
    }
    PushDown(root);
    int M = ( L + R ) >> 1;
    if ( l > M )
	{
		if ( nMax[R_son] > x ) Update( R_son, M + 1, R, l, r, x );
	}
	else if ( r <= M )
	{
		if ( nMax[L_son] > x ) Update( L_son, L, M, l, r, x );
	}
	else
	{
		if ( nMax[L_son] > x ) Update( L_son, L, M, l, M, x );
		if ( nMax[R_son] > x ) Update( R_son, M + 1, R, M + 1, r, x );
	}
	PushUp(root);
}

void Replace( int root, int L, int R, int l, int r, int Z )
{
	if ( l == L && r == R )
	{
		nVal[root] = nMax[root] = Z;
		return;
	}
	PushDown( root );
	int M = ( L + R ) >> 1;
	if ( l > M )
	{
		Replace( R_son, M + 1, R, l, r, Z );
	}
	else if ( r <= M )
	{
		Replace( L_son, L, M, l, r, Z );
	}
	else
	{
		Replace( L_son, L, M, l, M, Z );
		Replace( R_son, M + 1, R, M + 1, r, Z );
	}
	PushUp(root);
}

int Query( int root, int L, int R, int pos )
{
    if ( L == pos && R == pos ) {
        return nVal[root];
    }
    PushDown(root);
    int M = ( L + R ) >> 1;
    if ( pos <= M ) {
        return Query(L_son, L, M, pos);
    } else {
        return Query(R_son, M + 1, R, pos);
    }
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int T, Q;
    scanf("%d", &T);
    while ( T-- )
    {
        int n;
        scanf("%d", &n);
        CreateTree(1, 1, n);
        scanf("%d", &Q);
        while ( Q-- )
        {
            int t, l, r, x;
            scanf("%d %d %d %d", &t, &l, &r, &x);
            if ( t == 1 ) {
                Replace(1, 1, n, l, r, x);
            } else {
                Update(1, 1, n, l, r, x);
            }
        }
        rep(i, n) {
            printf("%d ", Query(1, 1, n, i + 1));
        }
        puts("");
    }
}
