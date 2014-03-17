/**
 * @file POJ_1961.cpp
 * @brief   2406的加强版
 * @hint    循环一下就得了，没什么好说的
 * @feeling 居然PE一发，不长眼！
 * @author FinalTheory
 * @version 0.1
 * @date 2014-02-02
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

void get_next( char * TAR, int * next, int len )
{
	int i, j;
	i = 0; next[0] = -1; j = -1;
	while ( i < len )
	{
		if ( j == -1 || TAR[i] == TAR[j] )
		{
			++i, ++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

#define MAX 1000010

char buffer[MAX];
int next[MAX];

int main()
{
	//std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int idx = 1;
	while (1)
	{
		int len = INT();
		if ( !len ) break;
		printf("Test case #%d\n", idx++);
		scanf("%s", buffer);
		get_next(buffer, next, len);
		REP(i, 2, len + 1)
		{
			int num = i - next[i];
			if ( i % num == 0 && i / num > 1 )
				printf("%d %d\n", i, i / num);
		}
		puts("");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
