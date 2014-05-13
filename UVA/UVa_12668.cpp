/**
 * @file UVa_12668.cpp
 * @brief   八皇后的经典扩展问题，可以转化为二分图的最大匹配。
 * @hint    首先明确二分图的定义，如果可以将图中节点分为两个集合，
 *	    图中每一条边的两个定点一定分属两个集合，那么这个图就是二分图。
 *	    如果将分属两个集合中的顶点用边对应起来，并且每个顶点只连一条边，那么边集就是二分图的匹配。
 *	    也就相当于将两个点集中的点“匹配”了起来，其中边数最多的匹配称为二分图的最大匹配。
 *	    题目要求是同行或者同列不能放置一个皇后。
 *	    如果没有这些“墙”，那么放置一个皇后的位置，同行同列都不能再放置。
 *	    也就相当于任何一个行与列只能有一个对应，这个位置只能放一个皇后。
 *	    这样我们以行和列为节点来建图，棋盘上每一个点对应一条(行, 列)的边，显然这个图是二分图。
 *	    发现最多皇后的摆放方式就对应着一个图的最大匹配：
 *	    因为已经匹配了的列和行就不能再与其他相交的列或者行匹配，否则会冲突。例如如果这个图有n行n列：
 *	    那么1-1,2-2...n-n就是一个最大匹配，对应了一种沿着主对角线的摆放方式。
 *	    同理，1-n,2-n-1...n-1也是一个最大匹配，对应于沿着副对角线的方式。
 *	    再考虑摆放了墙的情况，如果不是贴边，每个墙相当于将一个“行”节点或者一个“列”节点拆成了两个。
 *	    原本，对于NxN的棋盘，我们有N个行节点和N个列节点；
 *	    如果在第N-1个位置放一个墙，那么就相当于第一个行节点被拆成了两个节点（或者说两段）：
 *	    其中一段是1~N-2，另外一段就是N，这样图中共有N+1个行节点和N个列节点。
 *	    根据上述的思想，同样求二分图的最大匹配，得出的就是摆放的最大数量。
 * @feeling 思路给跪，学习了！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-05-02
 */
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

char _map[110][110];
int e1[110][110], e2[110][110];
vector<int> Adja[21000];

int match[21000];
bool visited[21000];

bool DFS( int u )
{
	rep(i, Adja[u].size())
	{
		//枚举与点u相邻的所有点（邻接表存储）
		int v = Adja[u][i];
		if ( !visited[v] )
		{
			visited[v] = true;
			if ( match[v] == -1 || DFS( match[v] ) )
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungary( int N )
{
	int res = 0;
	CLR( match, -1 );
	for ( int u = 1; u <= N; ++u )
	{
		CLR(visited, 0);
		if ( DFS(u) ) res++;
	}
	return res;
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
    int n;
    while ( scanf("%d", &n) != EOF )
    {
        CLR(e1, 0); CLR(e2, 0);
        rep(i, n) scanf("%s", _map[i]);
        int idx = 0;
        rep(i, n)
        rep(j, n) if ( _map[i][j] == '.' ) {
            if ( j == 0 || _map[i][j] != _map[i][j - 1] ) e1[i][j] = ++idx;
            else e1[i][j] = e1[i][j - 1];
        }
        rep(j, n)
        rep(i, n) if ( _map[i][j] == '.' ) {
            if ( i == 0 || _map[i][j] != _map[i - 1][j] ) e2[i][j] = ++idx;
            else e2[i][j] = e2[i - 1][j];
        }
        rep(i, idx + 1) Adja[i].clear();
        rep(i, n)
        rep(j, n) if ( _map[i][j] == '.' ) {
            Adja[e1[i][j]].PB(e2[i][j]);
        }
        printf("%d\n", Hungary(idx));
    }
#ifdef FUCK
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
