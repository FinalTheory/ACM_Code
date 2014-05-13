/**
 * @file HDU_3333.cpp
 * @brief   树状数组，在线转离线
 * @hint    这是一种特殊的询问“区间不同”的问题，但是求的不是元素种类而是元素的和。
 *	    这样就不能用常规的线段树来做，而是采用在线询问转离线询问的做法。
 *	    首先读入所有询问，按照右边界排序；然后按照序号遍历所有元素。
 *	    如果某个元素之前出现过，就把它先前出现的位置的数值清空，然后把这个元素放到当前位置；
 *	    如果之前没有出现过，就把它加到当前位置上去；而如果当前的序号等于某次询问的右边界，就记录答案；
 *	    这种操作方式保证了不管左边界情况如何，在记录答案时所有元素都只被求和了一次。
 *	    假设当前位置i == r，则r + 1以后的元素不管怎样都不影响这次询问；
 *	    而对于pos <= r的元素，由于上述策略的操作，都保证了尽量出现在它小于等于r且最靠右的位置；
 *	    并且最重要的是，保证了只出现了一次。这样利用树状数组做的区间求和就能够确保是正确答案了。
 * @feeling 1A
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-06
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

const int MAX = 30010;

int nums[MAX], _hash[MAX];
bool vis[MAX];
int prev[MAX];

LL Tree[MAX];

inline int Lowbit( int x )
{
	return x & (-x);
}

int N;
LL Query( int pos )
{
	LL sum = 0;
	//注意这里，不能为零，否则死循环
	while ( pos > 0 )
	{
		sum += Tree[pos];
		pos -= Lowbit(pos);
	}
	return sum;
}

void Add( int pos, int num )
{
	while ( pos <= N )
	{
		Tree[pos] += num;
		pos += Lowbit( pos );
	}
}

struct TMD
{
    int l, r, idx;
    LL ans;
} Queries[100010];

bool cmp1( const TMD & a, const TMD & b )
{
    return a.r < b.r;
}

bool cmp2( const TMD & a, const TMD & b )
{
    return a.idx < b.idx;
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
    int T;
    scanf("%d", &T);
    while ( T-- )
    {
        CLR(vis, 0);
        CLR(prev, -1);
        CLR(Tree, 0);
        int n;
        scanf("%d", &n);
        N = n;
        REP(i, 1, n + 1) {
            scanf("%d", &nums[i]);
        }
        memcpy(_hash, nums, sizeof(_hash));
        int q;
        scanf("%d", &q);
        rep(i, q) {
            scanf("%d %d", &Queries[i].l, &Queries[i].r);
            Queries[i].idx = i;
            Queries[i].ans = 0;
        }
        sort(Queries, Queries + q, cmp1);
        sort(_hash + 1, _hash + n + 1);
        int nn = unique(_hash + 1, _hash + n + 1) - _hash - 1;
        int p = 0;
        REP(i, 1, n + 1) {
            int num = nums[i];
            int val = lower_bound(_hash + 1, _hash + nn + 1, num) - _hash;
            if ( !vis[val] ) {
                vis[val] = true;
            } else {
                Add(prev[val], -num);
            }
            Add(i, num);
            prev[val] = i;
            while ( i == Queries[p].r ) {
                Queries[p].ans = Query(Queries[p].r) - Query(Queries[p].l - 1);
                p++;
            }
        }
        sort(Queries, Queries + q, cmp2);
        rep(i, q) printf("%I64d\n", Queries[i].ans);
    }
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
