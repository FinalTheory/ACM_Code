/**
 * @file HDU_1501.cpp
 * @brief   求前两个字符串能否组成第三个字符串，要求是前两个字符串中的字符按照顺序出现
 * @hint    记忆化搜索，但是需要记录扩展过的状态：这里使用i、j、k记录三个指针的指向；
 *	    但是需要注意的是，由于i + j = k，所以其实i、j已经能够表示所有的状态，
 *	    所以开个二维dp数组做记忆化搜索就可以了。一直尝试搜索到结果串终点。
 * @feeling 算是初步认识一下记忆化搜索吧，以前一直是把这个当作剪枝的。
 * @author FinalTheory
 * @version 1.0
 * @date 2014-03-18
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

char a[210], b[210], res[420];
bool dp[210][210];
int len_a, len_b, len_c;
bool flag;

void DFS( int i, int j, int k )
{
    if ( flag ) return;
    if ( k == len_c )
    {
        flag = true;
        return;
    }
    if ( dp[i][j] ) return;
    dp[i][j] = true;
    if ( i < len_a && a[i] == res[k] )
        DFS(i + 1, j, k + 1);
    if ( j < len_b && b[j] == res[k] )
        DFS(i, j + 1, k + 1);
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
    int n = INT(), idx = 1;
    while ( n-- )
    {
        scanf("%s %s %s", a, b, res);
        len_a = strlen(a);
        len_b = strlen(b);
        len_c = strlen(res);
        flag = false;
        CLR(dp, 0);
        DFS(0, 0, 0);
        if ( flag ) printf("Data set %d: yes\n", idx++);
        else printf("Data set %d: no\n", idx++);
    }
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
