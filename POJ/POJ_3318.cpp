/**
 * @file POJ_3318_1.cpp
 * @brief   随机化硬搞
 * @hint    注意现在POJ支持srand了
 * @feeling 这种题纯粹靠人品
 * @author FinalTheory
 * @version 0.1
 * @date 2013-10-25
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
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define MAX 510
#define Times 100000
using namespace std;
int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
bool _hash[MAX][MAX];
int n;
inline int mul( int i, int j )
{
	int ret = 0;
	for ( int k = 0; k < n; ++k )
		ret += a[i][k] * b[k][j];
	return ret;
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
	srand((unsigned)time(NULL));
	while ( scanf("%d", &n) != EOF )
	{
		CLR( _hash, 0 );
		for ( int i = 0; i < n; ++i )
			for ( int j = 0; j < n; ++j )
				scanf("%d", &a[i][j]);
		for ( int i = 0; i < n; ++i )
			for ( int j = 0; j < n; ++j )
				scanf("%d", &b[i][j]);
		for ( int i = 0; i < n; ++i )
			for ( int j = 0; j < n; ++j )
				scanf("%d", &c[i][j]);
		bool fail = false;
		for ( int k = 0; k < Times; ++k ) {
			int a = rand() % n;
			int b = rand() % n;
			if ( _hash[a][b] ) {++k; continue;}
			_hash[a][b] = true;
			if ( mul(a, b) != c[a][b] ) {
				fail = true;
				break;
			}
		}
		if ( fail )
			puts("NO");
		else
			puts("YES");
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

