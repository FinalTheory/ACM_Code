/**
 * @file HDU_3333.cpp
 * @brief   ��״���飬����ת����
 * @hint    ����һ�������ѯ�ʡ����䲻ͬ�������⣬������Ĳ���Ԫ���������Ԫ�صĺ͡�
 *	    �����Ͳ����ó�����߶������������ǲ�������ѯ��ת����ѯ�ʵ�������
 *	    ���ȶ�������ѯ�ʣ������ұ߽�����Ȼ������ű�������Ԫ�ء�
 *	    ���ĳ��Ԫ��֮ǰ���ֹ����Ͱ�����ǰ���ֵ�λ�õ���ֵ��գ�Ȼ������Ԫ�طŵ���ǰλ�ã�
 *	    ���֮ǰû�г��ֹ����Ͱ����ӵ���ǰλ����ȥ���������ǰ����ŵ���ĳ��ѯ�ʵ��ұ߽磬�ͼ�¼�𰸣�
 *	    ���ֲ�����ʽ��֤�˲�����߽������Σ��ڼ�¼��ʱ����Ԫ�ض�ֻ�������һ�Ρ�
 *	    ���赱ǰλ��i == r����r + 1�Ժ��Ԫ�ز�����������Ӱ�����ѯ�ʣ�
 *	    ������pos <= r��Ԫ�أ������������ԵĲ���������֤�˾�����������С�ڵ���r����ҵ�λ�ã�
 *	    ��������Ҫ���ǣ���֤��ֻ������һ�Ρ�����������״��������������;��ܹ�ȷ������ȷ���ˡ�
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
	//ע���������Ϊ�㣬������ѭ��
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
