/**
 * @file POJ_1436.cpp
 * @brief   线段树区间覆盖问题
 * @hint    核心思想还是一样的，不过区别在于增加了一个Query函数
 *	    用于询问每次插入线段之后，都有哪些边被覆盖掉了；
 *	    然后建立一个邻接表一样的结构来记录这些覆盖；
 *	    注意建立时添加关系的有序性，这样查询的时候可以减小循环次数。
 * @feeling 一个小地方写错了，跪了至少两个小时，尼玛……
 * @author FinalTheory
 * @version 0.1
 * @date 2014-04-17
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

const int MAX = 8010 * 2;
#define L_son root << 1
#define R_son root << 1 | 1
#define Father root >> 1

struct TMD
{
    int x, y1, y2;
} dat[MAX];

bool fuck( const TMD & a, const TMD & b )
{
    return a.x < b.x;
}

vector<int> Adja[MAX];
int Cur[MAX<<2], nNew[MAX<<2], _hash[MAX];

void CreateTree( int root, int L, int R )
{
	nNew[root]= 0;
	Cur[root] = 0;
	if (L == R) return;
	int M = ( L + R ) >> 1;
	CreateTree( L_son, L, M );
	CreateTree( R_son, M + 1, R );
}

inline void PushUp( int root )
{
    if ( Cur[L_son] == Cur[R_son] ) {
        Cur[root] = Cur[L_son];
    } else {
        Cur[root] = 0;
    }
}

inline void PushDown( int root )
{
	if ( nNew[root] )
	{
		nNew[L_son] = nNew[R_son] = nNew[root];
		Cur[L_son] = Cur[R_son] = nNew[root];
		nNew[root] = 0;
	}
}

void Update( int root, int L, int R, int l, int r, int Z )
{
	if ( l == L && r == R ) {
		Cur[root] = nNew[root] = Z;
		return;
	}
	PushDown( root );
	int M = ( L + R ) >> 1;
	if ( l > M )
	{
		Update( R_son, M + 1, R, l, r, Z );
	}
	else if ( r <= M )
	{
		Update( L_son, L, M, l, r, Z );
	}
	else
	{
		Update( L_son, L, M, l, M, Z );
		Update( R_son, M + 1, R, M + 1, r, Z );
	}
	PushUp(root);
}

void Query( int root, int L, int R, int l, int r, int Z )
{
    if ( Cur[root] ) {
        if ( _hash[Cur[root]] != Z ) {
            Adja[Z].PB(Cur[root]);
            _hash[Cur[root]] = Z;
        }
        return;
    }
    if ( L == R ) return;
    PushDown(root);
    int M = ( L + R ) >> 1;
	if ( l > M )
	{
		Query( R_son, M + 1, R, l, r, Z );
	}
	else if ( r <= M )
	{
		Query( L_son, L, M, l, r, Z );
	}
	else
	{
		Query( L_son, L, M, l, M, Z );
		Query( R_son, M + 1, R, M + 1, r, Z );
	}
	PushUp(root);
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
    int T;
    scanf("%d", &T);
    while ( T-- )
    {
        int n;
        scanf("%d", &n);
        CLR(_hash, 0);
        rep(i, n + 1) Adja[i].clear();
        int max_y = 0, min_y = INF;
        rep(i, n) {
            scanf("%d %d %d", &dat[i].y1, &dat[i].y2, &dat[i].x);
            max_y = max(dat[i].y2, max_y);
            min_y = min(dat[i].y1, min_y);
        }
        sort(dat, dat + n, fuck);
        int num = max_y - min_y + 1;
        rep(i, n) {
            dat[i].y1 = dat[i].y1 - min_y + 1;
            dat[i].y2 = dat[i].y2 - min_y + 1;
            dat[i].y1 <<= 1;
            dat[i].y2 <<= 1;
        }
        CreateTree(1, 1, num * 2);
        rep(i, n)
        {
            Query(1, 1, num * 2, dat[i].y1, dat[i].y2, i + 1);
            Update(1, 1, num * 2, dat[i].y1, dat[i].y2, i + 1);
        }
        int a, b, res = 0;
        REP(k, 1, n + 1) {
            rep(i, Adja[k].size()) {
                REP(j, i + 1, Adja[k].size()) {
                    a = Adja[k][i];
                    b = Adja[k][j];
                    if ( a < b ) swap(a, b);
                    rep(sss, Adja[a].size()) if ( Adja[a][sss] == b ) {
                        res++;
                    }
                }
            }
        }
        printf("%d\n", res);
    }
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
