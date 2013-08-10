/**
 * @file POJ_1159.cpp
 * @brief   最长公共子序列，滚动数组优化版
 * @author FinalTheory
 * @version 0.1
 * @date 2013-08-09
 */
#if defined(__GNUC__)
#pragma GCC optimize ("O2")
#endif
#if defined(_MSC_VER)
#pragma comment(linker, "/STACK:36777216")
#endif

#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <queue>
#include <iomanip>
#define MAX 5010
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

char str1[MAX], str2[MAX];
int DP[2][MAX];

int LCS( int len )
{
	DP[0][0] = 0;
	for ( int i = 1; i <= len; ++i )
		for ( int j = 1; j <= len; ++j )
			DP[i%2][j] = max( max( DP[(i-1)%2][j], DP[i%2][j - 1] ), DP[(i-1)%2][j - 1] + ( str1[i] == str2[j] ? 1 : 0 ) );
	return DP[len%2][len];
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	clock_t program_start, program_end;
	program_start = clock();
#endif
	int len;
	while ( scanf("%d", &len) != EOF )
	{
		scanf("%s", str1 + 1);
		str2[len + 1] = 0;
		for ( int i = len; i >= 1; --i )
			str2[len - i + 1] = str1[i];
		printf( "%d\n", len - LCS( len ) );
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
