/**
 * @file ZOJ_3814.cpp
 * @brief   模拟+状态压缩搜索
 * @hint    首先，一共九个格子，每个格子有四种状态，因此总的状态数量就是4^9=2^18个，显然不大。
 *	    因此，只要找出到达所有状态所需要的步数即可，应该应用BFS来搜索状态空间。
 *	    对于每一个格局，状态被两种因素所表示：格子的朝向，以及边缘锯齿的分布；
 *	    由于状态数很少，因此这些状态可以被压缩为一个整数，利用的是进制转换的思想。
 *	    这样，初始状态为全零，每一步BFS首先从队列中取出一个状态并将其解码；
 *	    然后对于这个状态，进行一下旋转操作，得到一个新的状态，包含朝向和锯齿分布两个部分。
 *	    对于这个新的状态，如果已经被搜索过，那么就抛弃它，不然就记录并加入队列。
 *	    这里的问题在于，合法的目标状态可能有许多种，因此，我们应该先利用一个DFS，搜索所有的合法状态。
 *	    此外，在每次旋转格子的时候，也需要利用DFS来进行旋转。
 * @feeling 网络赛卡出翔，怒跪……
 * @author FinalTheory
 * @version 0.1
 * @date 2014-09-07
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

char src[3][3][8][9], dst[3][3][8][9];

void Output( char buf[3][3][8][9] )
{
    rep(i, 3) {
        rep(k, 8) {
            rep(j, 3) {
                rep(l, 8) putchar(buf[i][j][k][l]);
                putchar(' ');
            }
            puts("");
        }
        puts("");
    }
}

void PutStat( int mat[3][3] )
{
    rep(i, 3) {
        rep(j, 3) printf("%d ", mat[i][j]);
        puts("");
    }
    puts("");
}

void PutMat( char buf[8][9] ) {
    rep(i, 8) {
        rep(j, 8) putchar(buf[i][j]);
        puts("");
    }
}

inline void Input( char buf[3][3][8][9] )
{
    rep(i, 3)
    rep(k, 8)
    rep(j, 3) scanf("%s", buf[i][j][k]);
}

bool cmp( char buf1[8][9], char buf2[8][9] )
{
    rep(i, 8)
    rep(j, 8) if ( buf1[i][j] != buf2[i][j] ) return false;
    return true;
}

inline void RotateRight( char buf[8][9] )
{
    char tmp[8][9];
    int dst = 8 - 1;
    for ( int i = 0; i < 8; i++, dst-- )
    rep(j, 8) tmp[j][dst] = buf[i][j];
    memcpy(buf, tmp, sizeof(tmp));
}

inline void RotateEdgeRight( int buf[4] )
{
    int bak = buf[3];
    rev(i, 3) buf[i + 1] = buf[i];
    buf[0] = bak;
}

inline void RotateEdgeLeft( int buf[4] )
{
    int bak = buf[0];
    rep(i, 3) buf[i] = buf[i + 1];
    buf[3] = bak;
}

bool target[3][3][4];

inline void Init()
{
    CLR(target, 0);
    rep(i, 3)
    rep(j, 3)
    rep(k, 4) {
        if ( cmp( src[i][j], dst[i][j] ) ) target[i][j][k] = true;
        RotateRight(src[i][j]);
    }
}

int mov[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
int mp[4][2] = { {2, 0}, {0, 2}, {3, 1}, {1, 3} };
bool vis[3][3];

inline bool check( int row, int col )
{
    if ( row < 0 || row >= 3 || col < 0 || col >= 3 ) return false;
    return true;
}

void DFS_Rotate( int cur[3][3], int edge[3][3][4], int row, int col, bool direct )
{
    vis[row][col] = true;
    if (direct) {
        cur[row][col] += 1;
        cur[row][col] %= 4;
    } else {
        cur[row][col] -= 1;
        if ( cur[row][col] < 0 ) cur[row][col] += 4;
    }
    rep(i, 4) {
        int new_row = row + mov[i][0];
        int new_col = col + mov[i][1];
        if ( check(new_row, new_col) && !vis[new_row][new_col] ) {
            if ( edge[row][col][mp[i][0]] && edge[new_row][new_col][mp[i][1]] ) {
                DFS_Rotate(cur, edge, new_row, new_col, !direct);
            }
        }
    }
    if ( direct ) {
        RotateEdgeRight(edge[row][col]);
    } else {
        RotateEdgeLeft(edge[row][col]);
    }
}

inline void stat_decode( int mat[3][3], int val )
{
    rep(i, 3)
    rep(j, 3) {
        mat[i][j] = val % 4;
        val /= 4;
    }
}

inline int stat_encode( int mat[3][3] )
{
    int stat = 0;
    rev(i, 3)
    rev(j, 3) stat = stat * 4 + mat[i][j];
    return stat;
}

inline void edge_decode( int edge[3][3][4], LL val )
{
    int tmp;
    rep(i, 3)
    rep(j, 3) {
        tmp = val % 16;
        val /= 16;
        rep(k, 4) {
            edge[i][j][k] = tmp % 2;
            tmp /= 2;
        }
    }
}

inline LL edge_encode( int edge[3][3][4] )
{
    LL res = 0;
    rev(i, 3)
    rev(j, 3) {
        int tmp = 0;
        rev(k, 4) tmp = tmp * 2 + edge[i][j][k];
        res = res * 16 + tmp;
    }
    return res;
}

int dp[(1<<18) + 10];
bool isLegal[(1<<18) + 10];

void GetLegalAns( int num, int val )
{
    if ( num < 0 ) {
        isLegal[val] = true;
        return;
    }
    int row = num / 3, col = num % 3;
    rep(k, 4) if ( target[row][col][k] ) {
        GetLegalAns(num - 1, val * 4 + k);
    }
}

bool found;

void BFS( int edge_start[3][3][4] )
{
    int mat[3][3], bak[3][3];
    int edge[3][3][4], edge_bak[3][3][4];
    CLR(dp, -1);
    queue<pair<int, LL> > que;
    que.push(make_pair(0, edge_encode(edge_start)));
    dp[0] = 0;
    while ( !que.empty() )
    {
        pair<int, LL> now = que.front(); que.pop();
        if ( isLegal[now.first] ) {
            printf("%d\n", dp[now.first]);
            found = true;
            return;
        }
        stat_decode(mat, now.first);
        edge_decode(edge, now.second);
        memcpy(bak, mat, sizeof(bak));
        memcpy(edge_bak, edge, sizeof(edge_bak));
        rep(i, 3)
        rep(j, 3) {
            CLR(vis, 0);
            memcpy(mat, bak, sizeof(mat));
            memcpy(edge, edge_bak, sizeof(edge));
            DFS_Rotate(mat, edge, i, j, true);
            int stat = stat_encode(mat);
            if ( dp[stat] == -1 ) {
                dp[stat] = dp[now.first] + 1;
                LL edge_stat = edge_encode(edge);
                que.push(make_pair(stat, edge_stat));
            }
        }
    }
}

int main()
{
	//std::ios::sync_with_stdiint _min;o(false);
#ifdef FUCK
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
#endif
    int T;
    scanf("%d", &T);
    while ( T-- ) {
        int edge[3][3][4];
        Input(src);
        Input(dst);
        rep(i, 3)
        rep(j, 3) scanf("%d %d %d %d", edge[i][j], edge[i][j] + 1, edge[i][j] + 2, edge[i][j] + 3);
        Init();
        CLR(isLegal, 0);
        GetLegalAns(8, 0);
        found = false;
        BFS(edge);
        if ( !found ) puts("-1");
    }
}
