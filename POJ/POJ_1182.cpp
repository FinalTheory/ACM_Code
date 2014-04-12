/**
 * @file POJ_1182.cpp
 * @brief   经典的种类并查集题目
 * @hint    这里需要特别注意的是并查集所代表的意义，不是指简单的集合关系，
 *	    而是说放在同一个集合里的元素之间的关系是可以相互确定的。
 *	    这样我们记录每个元素属于哪个集合，并且记录它的一个特征值（rnk数组）。
 *	    这个特征值表征的是当前元素与父亲节点的关系。
 *	    比如我们可以记录：0表示与父亲节点同种，1表示被吃，2表示吃。
 *	    这样就用并查集配合rnk数组记录下了所有节点之间的对应关系。
 *	    但是在路径压缩的时候需要注意了，同时也需要更新元素的特征值。
 *	    所以就有了这个稍微复杂点的Find函数写法，它所表示的含义是：
 *	    如果我们知道了孙子与儿子的关系，以及儿子与根的关系，就可以更新孙子与根的关系。
 *	    这样回溯下去即可。而当两个元素相对关系无法确定，即不在一个集合时，我们这样考虑：
 *	    将其中一个集合的根并到另一个集合中，并更新这个根的rnk特征。
 * @feeling 真是好烦人的题目，为什么POJ单组数据的题目就不能while读入？！
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

#define MAX 50010
int Tree[MAX], rnk[MAX];

int Find( int x )
{
    if ( x != Tree[x] )
    {
        int t = Tree[x];
        Tree[x] = Find(Tree[x]);
        rnk[x] = ( rnk[x] + rnk[t] ) % 3;
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
    int n, k, d, x, y;
    scanf("%d %d", &n, &k);
    REP(i, 1, n + 1) {
        Tree[i] = i;
        rnk[i] = 0;
    }
    int res = 0;
    rep(i, k)
    {
        //scanf("%d %d %d", &d, &x, &y);
        d = INT();
        x = INT();
        y = INT();
        if ( x > n || y > n || ( d == 2 && x == y ) ) {
            res++;
            continue;
        }
        int r_x = Find(x);
        int r_y = Find(y);
        if ( r_x == r_y ) {
            if ( d == 1 ) {
                if ( rnk[x] != rnk[y] ) res++;
            } else {
                if ( ( rnk[x] + 1 ) % 3 != rnk[y] ) res++;
            }
        } else {
            Tree[r_y] = r_x;
            rnk[r_y] = ( rnk[x] - rnk[y] + 3 + d - 1 ) % 3;
        }
    }
    printf("%d\n", res);
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
