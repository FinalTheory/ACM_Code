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

const int MAX = 200010;
int nMin[MAX<<2];
int M;

void Create(int n)
{
    M = 1;
    while ( M < n + 2 ) M <<= 1;
    REP(i, 1, n + 1) scanf("%d", &nMin[M + i]);
    rev(i, M) nMin[i] = max(nMin[i<<1], nMin[i<<1|1]);
}

int Query( int l, int r )
{
    int res = 0;
    for ( l=l+M-1, r=r+M+1; (l^r)!=1; l>>=1, r>>=1 ) {
        if ( (l & 1) == 0 ) res = max(res, nMin[l^1]);
        if ( (r & 1) == 1 ) res = max(res, nMin[r^1]);
    }
    return res;
}

void Update( int pos, int val )
{
    pos += M;
    nMin[pos] = val;
    while ( pos >= 1 ) {
        pos >>= 1;
        nMin[pos] = max(nMin[pos<<1], nMin[pos<<1|1]);
    }
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int N, Q;
    while ( scanf("%d %d", &N, &Q) != EOF )
    {
        Create(N);
        int a, b;
        char t[3];
        rep(i, Q) {
            scanf("%s %d %d", t, &a, &b);
            if ( t[0] == 'U' ) {
                Update(a, b);
            } else {
                printf("%d\n", Query(a, b));
            }
        }
    }
}
