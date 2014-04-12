/**
 * @file HDU_1829.cpp
 * @brief   种类并查集，POJ1182的简化版
 * @hint    思路差不多，还是用rnk数组记录关系，并查集记录哪些元素可以被确定。
 *	    要注意的是，路径压缩之后，每个元素的父亲就是所在树的根节点！
 *	    这样如果两个节点的根相同，说明他们的关系可以被唯一确定；
 *	    这个时候就看他们之间是否异性了，利用的是两者与根节点的相对关系来判断。
 *	    如果根不同，说明关系不存在，需要把两者合并。
 *	    这时已经进行了路径压缩，a、b的父亲就是根节点。
 *	    现在要合并的是俩父亲，比如我们把b的根连接到a的根上，即b的根和a为兄弟。
 *	    这时就需要更新b的根的rnk，于是列表做一下推导：
 *	    如果a和其根异性，b和其根异性，则显然为了有a和b异性，则a的根与b的根异性；
 *	    若a和其根同性，b和其根同性，则应有a的根与b的根异性；
 *	    显然其他的情况需要a的根和b的根同性。
 *	    所以依赖上述关系，就可以进行集合合并了。
 * @feeling 学完POJ1182之后拿这个练练手，推导合并更新的时候弄错了一个关系，WA了一发。
 * @author FinalTheory
 * @version 0.1
 * @date 2014-04-12
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

#define MAX 2010
int Tree[MAX], rnk[MAX];

int Find( int x )
{
    if ( x != Tree[x] )
    {
        int t = Tree[x];
        Tree[x] = Find(Tree[x]);
        rnk[x] = ( rnk[x] + rnk[t] ) % 2;
    }
    return Tree[x];
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
    int T, idx = 1;
    scanf("%d", &T);
    while ( T-- )
    {
        int n, m, a, b;
        bool flag = false;
        scanf("%d %d", &n, &m);
        rep(i, n + 1)
        {
            Tree[i] = i;
            rnk[i] = 0;
        }
        rep(kkk, m)
        {
            scanf("%d %d", &a, &b);
            if ( flag ) continue;
            int r_a = Find(a);
            int r_b = Find(b);
            if ( r_a == r_b ) {
                if ( rnk[a] == rnk[b] ) flag = true;
            } else {
                Tree[r_b] = r_a;
                rnk[r_b] = ( rnk[a] == rnk[b] ? 1:0 );
            }
        }
        if ( flag )
            printf("Scenario #%d:\nSuspicious bugs found!\n\n", idx++);
        else
            printf("Scenario #%d:\nNo suspicious bugs found!\n\n", idx++);
    }
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
