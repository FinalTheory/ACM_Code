/**
 * @file ZOJ_3811.cpp
 * @brief   ���鼯��ͼ����ͨ������
 * @hint    ��Ŀ��Ŀ�ľ��Ǹ���һ��������У��ʰ�����������Ƿ���ڱ���ȫͼ��·����
 *	    ���ȣ����ǰ�����ͼ���˹ؼ���֮����Ϊһ�����ϣ�����һ�����鼯��
 *	    Ȼ�󣬶��ڰ���˳���ÿ���ؼ��㣬���ǰ������벢�鼯��Ȼ����������ǰһ���ܷ���ͨ��
 *	    ����ķ�ʽ�ǣ�����֮�����ķǹؼ��㶼���벢�鼯�����Ҽ������֮�������Ϊ�ǹؼ��㡣
 *	    ������������һ�������������ǹؼ��������ӡ�
 *	    ���ǰ����������Դ���ͬһ�������У�˵������һ����������Ч�ġ�
 * @feeling �����Լ����ģ��������ˣ����˹�Ȼ�������⡭�����ֱ������ǳ�ʼ������
 * @author FinalTheory
 * @version 0.1
 * @date 2014-09-08
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

const int nMAX = 100010;
const int eMAX = 200010;

int nodes[nMAX];
bool hasMon[nMAX], vis[nMAX];
vector<int> Adja[nMAX];

int Tree[nMAX];

int find_root( int node )
{
    if ( Tree[node] == node )
        return node;
    else
        return Tree[node] = find_root(Tree[node]);
}

void Connect( int u )
{
    rep(i, Adja[u].size()) {
        int v = Adja[u][i];
        if ( hasMon[v] ) continue;
        int root_u = find_root(u), root_v = find_root(v);
        if ( root_u != root_v ) {
            Tree[root_v] = root_u;
        }
    }
    hasMon[u] = false;
}

bool Solve()
{
    int n, m, k, tmp, root;
    scanf("%d %d %d", &n, &m, &k);
    CLR(hasMon, 0);
    CLR(vis, 0);
    rep(i, n + 1) Adja[i].clear();
    rep(i, n + 1) Tree[i] = i;
    rep(i, k) {
        scanf("%d", &tmp);
        hasMon[tmp] = true;
    }
    int a, b;
    rep(i, m) {
        scanf("%d %d", &a, &b);
        Adja[a].PB(b);
        Adja[b].PB(a);
        // ���ڲ���������Ľڵ㣬���벢�鼯
        if ( !hasMon[a] && !hasMon[b] ) {
            int root_a = find_root(a);
            int root_b = find_root(b);
            if ( root_a != root_b ) Tree[root_a] = root_b;
        }
    }
    int L;
    scanf("%d", &L);
    rep(i, L) scanf("%d", &nodes[i]);
    if ( k == 0 ) return true;
    if ( L < k ) return false;
    Connect(nodes[0]);
    REP(i, 1, L) {
        Connect(nodes[i]);
        int root_u = find_root(nodes[i - 1]), root_v = find_root(nodes[i]);
        if ( root_u != root_v ) {
            return false;
        }
    }
    root = find_root(1);
    REP(i, 2, n + 1) if ( find_root(i) != root ) return false;
    //REP(i, 1, n + 1) if ( !vis[i] ) return false;
    return true;
}

int main()
{
	//std::ios::sync_with_stdio(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int T;
    scanf("%d", &T);
    while ( T-- )
    {
        if ( !Solve() ) {
            puts("No");
        } else {
            puts("Yes");
        }
    }
}
