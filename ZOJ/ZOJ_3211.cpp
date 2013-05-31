/**
 * @file ZOJ_3211.cpp
 * @brief   DP水题，卡死我了……
 * DP[i][j]记录的状态是前i棵树在前j天的最大收益。
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-30
 */
#include <iostream>
#include <algorithm>
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
#include <iomanip>
#define MAX 300
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int DP[300][300];
struct TMD
{
	int a, b;
} Trees[200];
bool fuck( const TMD & A, const TMD & B )
{
	return A.b < B.b;
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
	int T, n, m, i, j;
	scanf("%d", &T);
	while ( T-- )
	{
		scanf("%d %d", &n, &m);
		for ( i = 1; i <= n; ++i )
			scanf("%d", &Trees[i].a);
		for ( i = 1; i <= n; ++i )
			scanf("%d", &Trees[i].b);
		sort( Trees + 1, Trees + n + 1, fuck );
		CLR(DP, 0);
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= m; ++j )
				DP[i][j] = max( DP[i-1][j], DP[i-1][j-1] + Trees[i].a + Trees[i].b * (j-1) );
		printf("%d\n", DP[n][m]);
	}
#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}

