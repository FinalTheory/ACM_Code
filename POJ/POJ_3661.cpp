/**
 * @file POJ_3661.cpp
 * @brief   DP问题，注意状态转移方程！
 * 这里面每一个合法的DP[i][j]可以影响到后面的DP[i+j][0]！
 * 而不是说仅仅影响到下一分钟的DP[i+1][j-1]！
 * 因为一旦开始休息，就要一直休息到疲劳度为零才能停下！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-04
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
#define INF 100000100
#define CLR(arr,val) memset(arr,val,sizeof(arr))

using namespace std;

int DP[10800][510];
int D[10010];

inline int _max( int a, int b )
{
	return a > b ? a : b;
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
	int N, M, i, j, max;
	while ( scanf("%d %d", &N, &M) != EOF )
	{
		CLR( D, 0 );
		for ( i = 0; i <= N + 1; ++i )
			for ( j = 0; j <= M; ++j )
				DP[i][j] = -INF;
		DP[1][0] = 0;
		for ( i = 1; i <= N; ++i )
			scanf("%d", &D[i]);
		for ( i = 1; i <= N; ++i )
			for ( j = 0; j <= M; ++j )
			{
				if ( DP[i][j] >= 0 )
				{
					//就是这里，注意是如何影响后面的！
					DP[i+j][0] = _max( DP[i+j][0], DP[i][j] );
					if ( j < M )
						DP[i+1][j+1] = _max( DP[i+1][j+1], DP[i][j] + D[i] );
					if ( j == 0 )
						DP[i+1][0] = _max( DP[i+1][0], DP[i][0] );
				}
			}
		printf("%d\n", DP[N+1][0]);
	}

#ifndef ONLINE_JUDGE
	program_end = clock();
	cerr << "Time consumed: " << endl << ( program_end - program_start ) << " MS" << endl;
#endif
}
