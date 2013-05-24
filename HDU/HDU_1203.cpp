/**
 * @file HDU_1203.cpp
 * @brief   简单的01背包问题，加法改成乘法而已。所以注意要初始化为1哦！
 * 另外数据好弱！本来那个规模很有可能超时的！
 * @author FinalTheory
 * @version 0.1
 * @date 2013-05-21
 */
#include <algorithm>
#include <cstdio>
using namespace std;
double DP[10010];
int main()
{
	int n, m, i, v, j;
	double w;
	while ( scanf("%d %d", &n, &m) && m + n )
	{
		for ( i = 0; i <= n; ++i )
			DP[i] = 1.;
		for ( i = 0; i < m; ++i )
		{
			scanf("%d %lf", &v, &w);
			w = 1. - w;
			for ( j = n; j >= v; j-- )
				DP[j] = min( DP[j - v] * w, DP[j] );
		}
		printf("%.1lf%%\n", (1 - DP[n]) * 100.);
	}
}
