/**
 * @file CF_245D.cpp
 * @brief   简单的矩阵运算，水题
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-16
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
using namespace std;
const int INF = 0x3f3f3f3f;
int mat[110][110];
int a[110];
int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int n;
	while ( scanf("%d", &n) != EOF )
	{
		CLR(a, 0);
		for ( int i = 1; i <= n; ++i )
			for ( int j = 1; j <= n; ++j )
			{
				scanf("%d", &mat[i][j]);
			}
		for ( int i = 1; i <= n; ++i )
			for ( int j = 1; j <= n; ++j ) if ( i != j )
			{
				a[i] |= mat[i][j];
				a[j] |= mat[i][j];
			}
		printf("%d", a[1]);
		for ( int i = 2; i <= n; ++i )
			printf(" %d", a[i]);
		puts("");
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
