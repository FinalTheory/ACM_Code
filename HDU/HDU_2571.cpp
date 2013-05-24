/**
 * @file HDU_2571.cpp
 * @brief   简单DP，这道题已经不只是状态转移方程很清楚了，简直就是直接告诉你所有状态，走一遍就是了。
 * 0MS，1A无压力！哈哈哈~~~
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-22
 */
#include <algorithm>
#include <cstdio>
#define INF -100000000
using namespace std;
int DP[22][1010], map[22][1010];
int main()
{
	int C, n, m, i, j, k;
	scanf("%d", &C);
	while ( C-- )
	{
		scanf("%d %d", &n, &m);
		for ( i = 1;  i <= n; ++i )
			for ( j = 1; j <= m; ++j )
			{
				scanf("%d", &map[i][j]);
				DP[i][j] = INF;
			}
		DP[1][1] = map[1][1];
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= m; ++j )
				if ( DP[i][j] != INF )
				{
					if ( i < n && DP[i][j] + map[i+1][j] > DP[i+1][j] )
						DP[i+1][j] = DP[i][j] + map[i+1][j];
					if ( j + 1 <= m && DP[i][j] + map[i][j+1] > DP[i][j+1] )
						DP[i][j+1] = DP[i][j] + map[i][j+1];
					for ( k = 2 * j; k <= m; k += j )
						if ( DP[i][j] + map[i][k] > DP[i][k] )
							DP[i][k] = DP[i][j] + map[i][k];
				}
		printf("%d\n", DP[n][m]);
	}
}
