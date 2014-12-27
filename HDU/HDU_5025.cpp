/**
 * @file HDU_5025.cpp
 * @brief   优先队列优化的状态压缩搜索
 * @hint    首先要注意记录状态，这个题目可能卡的比较松，不需要记录蛇的状态。
 *	    然后就是一个小的地方，标记状态的时候，应该先标记，再入队。
 *	    因为这个题目比较特殊，为了使得每次处理的是最短时间，使用了优先队列，
 *	    这就导致如果每次等出队的时候再标记状态，那么这个状态可能很难出队，
 *	    最终导致的结果就是一个状态会多次入队，因为它没有出队过，也就没有被标记到。
 * @feeling TLE了N多次，不爽！不过想明白这个trick还是有价值的。
 * @author FinalTheory
 * @version 0.1
 * @date 2014-09-22
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

int n, m;
int row_start, col_start, row_end, col_end;
char mp[105][105];
int snakes[105][105];
int p;
bool vis[105][105][10];

inline bool check( int row, int col )
{
    if ( mp[row][col] == '#' ) return false;
    if ( row < 0 || row >= n || col < 0 || col >= n ) return false;
    return true;
}

int mov[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct Stat
{
    int row, col, snake, key, time;
    Stat( int _row = 0, int _col = 0, int _snake = 0, int _key = 0, int _time = 0 )
    : row(_row), col(_col), snake(_snake), key(_key), time(_time) {};
};

bool operator < ( const Stat & a, const Stat & b )
{
    return a.time > b.time;
}

inline bool has_snake( int row, int col, int snake )
{
    if ( mp[row][col] != 'S' ) return false;
    if ( snake & snakes[row][col] ) return false;
    return true;
}

bool BFS()
{
    CLR(vis, 0);
    priority_queue<Stat> que;
    que.push(Stat(row_start, col_start, 0, 0, 0));
    vis[row_start][col_start][0] = true;
    while ( !que.empty() )
    {
        Stat cur = que.top(); que.pop();
        if ( cur.key >= m && cur.row == row_end && cur.col == col_end ) {
            printf("%d\n", cur.time);
            return true;
        }
        rep(i, 4) {
            int row = cur.row + mov[i][0];
            int col = cur.col + mov[i][1];
            if ( check(row, col) ) {
                int time = cur.time + 1;
                int snake = cur.snake;
                int key = cur.key;
                //处理蛇的状态
                if ( has_snake(row, col, snake) ) {
                    time++;
                    snake |= snakes[row][col];
                }
                //处理钥匙的状态
                if ( mp[row][col] >= '1' && mp[row][col] <= '9' ) {
                    if ( key == mp[row][col] - '0' - 1 ) {
                        key++;
                    }
                }
                if ( !vis[row][col][key] ) {
                    que.push(Stat(row, col, snake, key, time));
                    vis[row][col][key] = true;
                }
            }
        }
    }
    return false;
}

int main()
{
    //std::ios::sync_with_stdio(false);
#ifdef FUCK
    freopen( "in.txt", "r", stdin );
    //freopen( "out.txt", "w", stdout );
#endif
    while ( scanf("%d %d", &n, &m) != EOF && m + n )
    {
        rep(i, n) scanf("%s", mp[i]);
        p = 0;
        int idx = 0;
        CLR(snakes, 0);
        rep(i, n)
        rep(j, n) {
            if ( mp[i][j] == 'K' ) {
                row_start = i;
                col_start = j;
            } else if ( mp[i][j] == 'T' ) {
                row_end = i;
                col_end = j;
            } else if ( mp[i][j] == 'S' ) {
                snakes[i][j] = (1 << (idx++));
            }
        }
        if ( !BFS() ) puts("impossible");
    }
}
